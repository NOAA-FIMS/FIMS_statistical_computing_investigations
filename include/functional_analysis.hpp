#ifndef FUNCTIONAL_ANALYSIS_HPP
#define FUNCTIONAL_ANALYSIS_HPP
#include "ATL/ATL.hpp"
#include <vector>
#include <limits>
#include <chrono>
#include <complex>
//#include <stxxl.h>

#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

template<typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<std::vector<T> >& m) {

    out << std::scientific;

    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m[i].size(); j++) {
            out << m[i][j] << "    ";
        }
        out << "\n";
    }
    return out;
}

template<typename T>
class FunctionalAnalysis {
public:
    typedef typename atl::Variable<T> Variable;
    //parameter list
    std::vector<Variable*> parameters;
    std::vector<T> deltas;



    std::string name;
    std::string description;



    T delta = 1e-3;


    //all possible input values
    std::vector<std::vector<T> > input_values;

    //parameter set
    std::vector<std::vector<T> > parameter_sets;

    //function values from each evaluation
    std::vector<T> values;

    //derivatives from each evaluation
    std::map<uint32_t, std::vector<T> > derivatives;



    std::map<uint32_t, T > stochasticity_of_derivatives;

    //Covariance indicates the direction of the linear relationship between variables.
    //values are standardized
    std::vector<std::vector<T> > covariance;

    //Correlation measures both the strength and direction of the linear relationship between two variables.
    //values are not standardized
    std::vector<std::vector<T> > correlation;

    bool is_continuous = true;

    //parameter sets that lead to NaN
    std::vector<std::vector<T> > discontinuity_sets;


    //min evaluated function value
    T min_value = std::numeric_limits<T>::min();

    //max evaluated function value
    T max_value = std::numeric_limits<T>::max();

    //parameter set for the min evaluated function value
    std::vector<T> parameter_set_min;

    //parameter set for the max evaluated function value
    std::vector<T> parameter_set_max;

    //analysis start time
    std::chrono::time_point<std::chrono::system_clock> start_time;

    //analysis end time
    std::chrono::time_point<std::chrono::system_clock> end_time;

    //total time to do the function analysis
    double runtime;

    double stochasticity;


    std::vector<std::vector<T> > lower_bound_covariance;
    std::vector<std::vector<T> > upper_bound_covariance;
    std::vector<std::vector<T> > central_bound_covariance;

    std::vector<std::vector<T> > lower_bound_correlation;
    std::vector<std::vector<T> > upper_bound_correlation;
    std::vector<std::vector<T> > central_bound_correlation;

    std::vector<T> mean_parameter_values;

    bool write_values = false;
    bool write_derivatives = false;

    FunctionalAnalysis() {

    }

    void ClearData() {
        this->values.clear();
        this->parameter_sets.clear();
        this->derivatives.clear();
        this->correlation.clear();
        this->covariance.clear();
    }

    /**
     * Initialize parameter set. Must be overloaded.
     * 
     */
    virtual void Initialize() = 0;

    /**
     * The function to analyze. Must be overloaded.
     * 
     * @return 
     */
    virtual Variable Evaluate() = 0;

    void RegisterParameter(Variable& x, T infinitesimal_step = 1e-3) {
        x.SetValue(x.GetMinBoundary());
        this->parameters.push_back(&(x));
        this->deltas.push_back(infinitesimal_step);
    }

    /**
     * Analyzes computational properties of a child function.
     */
    void Analyze() {

        Variable::tape.recording = false;
        std::cout << "Running functional analysis for " << this->name << "...\n";
        double progress = 0;
        this->start_time = std::chrono::system_clock::now();

        //initialize all parameter values
        this->input_values.resize(this->parameters.size());
        for (int i = 0; i < this->parameters.size(); i++) {
            for (T v = this->parameters[i]->GetMinBoundary(); v <= this->parameters[i]->GetMaxBoundary(); v += this->deltas[i]) {
                input_values[i].push_back(v);
            }
        }

        //create argument list. Combination of input_values size(input_values) choose size(parameters)
        std::cout << "\nBuilding argument set..." << std::flush;
        std::vector<T> working(this->parameters.size());
        int count = 0;
        int current = 0;

        if (this->parameters.size() > 1) {
            this->ParameterSetsBuilder(count, current, working, input_values, parameter_sets);
        } else {
            parameter_sets.resize(input_values[0].size());
            for (int i = 0; i < input_values[0].size(); i++) {
                this->parameter_sets[i].push_back(input_values[0][i]);
            }
        }
        std::cout << "done.\n";
        std::cout << "Number of parameter sets: " << parameter_sets.size() << "\n";
        std::cout << "Number of parameters per set: " << parameters.size() << "\n";

        mean_parameter_values.resize(this->parameters.size());

        for (int i = 0; i < parameter_sets.size(); i++) {
            for (int j = 0; j < parameter_sets[i].size(); j++) {
                this->mean_parameter_values[j] += parameter_sets[i][j];
            }
        }

        for (int i = 0; i < this->mean_parameter_values.size(); i++) {
            this->mean_parameter_values[i] /= static_cast<T> (this->parameter_sets.size());
        }

        Variable::tape.recording = true;
        std::cout << "Running Infinitesimal Analysis..." << std::endl;
        //Run Infinitesimal step - Riemann
        for (int i = 0; i < parameter_sets.size(); i++) {

            progress = ((double) i / (double) parameter_sets.size());

            if ((i % 10) == 0) {
                //show progress
                this->Progress(progress);
            }
            //update parameter set
            this->UpdateParameterSet(parameter_sets[i]);

            //reset the tape
            Variable::tape.Reset();

            //evaluate the test function
            Variable v = this->Evaluate();

            //store values
            this->values.push_back(v.GetValue());

            //check min and max value
            if (v < this->min_value) {
                this->min_value = v.GetValue();
                this->parameter_set_min = parameter_sets[i];
            }

            if (v > this->max_value) {
                this->max_value = v.GetValue();
                this->parameter_set_max = parameter_sets[i];
            }

            //compute derivatives
            Variable::tape.AccumulateFirstOrder();

            //store derivatives
            for (int p = 0; p< this->parameters.size(); p++) {

                this->derivatives[this->parameters[p]->info->id].push_back(Variable::tape.Value(this->parameters[p]->info->id));
            }

        }
        this->Progress(1.0);
        std::cout << "\ndone.\nComputing Stochasticity..." << std::endl;

        //quantify smoothness
        std::vector<T> diff = Diff(this->values);
        this->stochasticity = StandardDeviation(diff) / std::fabs(Mean(diff));

        double progress_2 = 0;
        //quantify derivative smoothness and continuity
        //        for (int i = 0; i < this->values.size(); i++) {
        //            progress_2 = ((double) i / (double) this->values.size())*.5;
        //
        //            if ((i % 10) == 0) {
        //                //show progress
        //                this->Progress(progress + progress_2);
        //            }
        for (int j = 0; j < this->parameters.size(); j++) {
            progress = ((double) j / (double) parameter_sets.size());
            std::vector<T>& derivatives = this->derivatives[this->parameters[j]->info->id];

            std::vector<T> diff = Diff(derivatives);
            this->stochasticity_of_derivatives[this->parameters[j]->info->id] =
                    StandardDeviation(diff) / std::fabs(Mean(diff));

            for (int k = 0; k < derivatives.size(); k++) {
                if (derivatives[k] != derivatives[k]) {//NaN
                    this->is_continuous = false;
                    this->discontinuity_sets.push_back(this->parameter_sets[k]);
                }
            }
            this->Progress(progress);
        }
        this->Progress(1.0);
        //        }
        std::cout << "\ndone.\nComputing Covariance..." << std::flush;

        //covariance
        this->lower_bound_covariance = this->CovarianceMatrix(this->parameter_sets[0]);
        this->central_bound_covariance = this->CovarianceMatrix(this->parameter_sets[static_cast<size_t> (this->parameter_sets.size() / 2.0)]);
        this->upper_bound_covariance = this->CovarianceMatrix(this->parameter_sets[static_cast<size_t> (this->parameter_sets.size() - 1)]);

        std::cout << "done.\nComputing Correlation..." << std::flush;
        //correlations
        this->lower_bound_correlation = this->CorrelationMatrix(this->lower_bound_covariance);
        this->central_bound_correlation = this->CorrelationMatrix(this->central_bound_covariance);
        this->upper_bound_correlation = this->CorrelationMatrix(this->upper_bound_covariance);

        this->end_time = std::chrono::system_clock::now();
        this->runtime = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();
        std::cout << "done.\n";
    }

    std::pair<T, T> FindMinMax(const std::vector<T>& v) {

        T min_ = v[0]; //-1.0*std::numeric_limits<T>::infinity();
        T max_ = v[0]; //std::numeric_limits<T>::infinity();

        for (size_t i = 0; i < v.size(); i++) {
            min_ = std::min(min_, v[i]);
            max_ = std::max(max_, v[i]);
        }

        return std::pair<T, T>(min_, max_);
    }

    void Finalize() {

        std::stringstream ss;
        ss << this->name << "_functional_analysis.txt";
        std::ofstream out(ss.str());

        out << "Name: " << this->name << std::endl;
        out << "Description:\n" << this->description << "\n\n";
        out << "Run time(seconds): " << this->runtime << "\n";
        out << "Number of parameter sets: " << parameter_sets.size() << "\n";
        out << "Parameter Range: \n";
        for (int i = 0; i < this->parameters.size(); i++) {
            out << std::setw(15) << std::left << this->parameters[i]->GetName() <<
                    std::setw(4) << std::left << this->parameters[i]->GetMinBoundary() << "  -   "
                    << std::setw(4) << std::left << this->parameters[i]->GetMaxBoundary() << "\n";
        }
        out << "Infinitesimal Step: \n";

        for (int i = 0; i < this->parameters.size(); i++) {
            out << this->parameters[i]->GetName() << "\t" << this->deltas[i] << "\n";
        }
        std::string tf = "TRUE";
        if(!this->is_continuous){
            tf = "FALSE";
        }
        
        out << "Function is Continuous: " << tf << "\n";
        out << "Function Stochasticity: " << stochasticity << "\n";

        for (int i = 0; i < this->parameters.size(); i++) {
            std::vector<T>& dx = this->derivatives[this->parameters[i]->info->id];

            std::pair<T, T> temp;
            temp.first = *std::min_element(std::begin(dx), std::end(dx));
            temp.second = *std::max_element(std::begin(dx), std::end(dx));
            
            out << "Derivative Stochasticity of \"" << this->parameters[i]->GetName()
                    << "\": " << stochasticity_of_derivatives[this->parameters[i]->info->id] << ",\t[ " << temp.first << " : " << temp.second << " ]\n";
        }

        out << "\nCovariance:\n";
        out << "lower bounds:\n";
        out << this->lower_bound_covariance;

        out << "\ncentral bounds:\n";
        out << this->central_bound_covariance;

        out << "\nupper bounds:\n";
        out << this->upper_bound_covariance;

        out << "\n\nCorrelation:\n";
        out << "lower bounds:\n";
        out << this->lower_bound_correlation;

        out << "\ncentral bounds:\n";
        out << this->central_bound_correlation;

        out << "\nupper bounds:\n";
        out << this->upper_bound_correlation;

        out.close();
        //        this->Progress(1.0);
        std::cout << "\n";
        if (this->write_derivatives) {
            this->WriteDerivatives();
        }

        if (this->write_values) {
            this->WriteValues();
        }

        this->ClearData();
    }

    void WriteValues() {
        std::ofstream out;
        std::stringstream ss;
        ss << this->name << "_values.csv";
        out.open(ss.str().c_str());
        for (int i = 0; i < this->values.size() - 1; i++) {
            out << this->values[i] << ", ";
        }
        out << this->values[this->values.size() - 1];
    }

    void WriteDerivatives() {
        std::ofstream out;
        std::stringstream ss;
        ss << this->name << "_derivatives.csv";
        out.open(ss.str().c_str());


        for (int i = 0; i < this->parameters.size(); i++) {

            if (i == this->parameters.size() - 1) {
                out << this->parameters[i]->GetName() << "\n";
            } else {
                out << this->parameters[i]->GetName() << ", ";
            }
        }


        for (int i = 0; i < this->values.size(); i++) {
            for (int j = 0; j < this->parameters.size(); j++) {
                std::vector<T>& derivatives = this->derivatives[this->parameters[j]->info->id];
                if (j == this->parameters.size() - 1) {
                    out << derivatives[i] << "\n";
                } else {
                    out << derivatives[i] << ", ";
                }

            }
        }
        out.close();
    }

    /**
     * Creates parameter sets based on combination of 
     * input_values size(input_values) choose size(parameters).
     * 
     * @param count
     * @param current
     * @param working
     * @param source
     * @param combos
     */
    void ParameterSetsBuilder(int& count,
            int current,
            std::vector<T>& working,
            std::vector<std::vector<T> >& source,
            std::vector<std::vector<T> >& combos) {


        if (current == 0) {
            for (int i = 0; i < source[0].size(); i++) {
                std::vector<T> v;
                v.push_back(source[0][i]);
                ParameterSetsBuilder(count, current + 1, v, source, combos);
            }
        } else if (current < source.size() - 1) {
            std::vector<T> v = working;
            //            v.push_back(0);
            for (int i = 0; i < source[current].size(); i++) {
                v[v.size() - 1] = source[current][i];
                ParameterSetsBuilder(count, current + 1, v, source, combos);
            }
        } else {

            std::vector<T> v = working;
            v.push_back(0);
            for (int i = 0; i < source[current].size(); i++) {
                v[v.size() - 1] = source[current][i];
                combos.push_back(v);
                count++;
            }

        }
    }

    /**
     * Updates the parameter set.
     * 
     * @param v
     */
    void UpdateParameterSet(std::vector<T>& v) {
        for (int i = 0; i < v.size(); i++) {
            this->parameters[i]->SetValue(v[i]);
        }
    }

    /**
     * Prints the progress of the analysis.
     *  
     * @param percentage
     */
    void Progress(double progress) {
        int barWidth = 70;
        std::cout << "\r";
        std::cout << "[";
        int pos = barWidth * progress;
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos) std::cout << "=";
            else if (i == pos) std::cout << ">";
            else std::cout << " ";
        }
        std::cout << "] " << int(progress * 100.0) << " %\r";
        std::cout.flush();
    }

    const std::vector<T> Diff(const std::vector<T>& v, int lag = 1) {

        std::vector<T> difference;

        for (int i = lag; i < v.size(); i += lag) {
            if (i < v.size() - 1) {
                difference.push_back(v[i - lag] - v[lag]);
            }
        }

        return difference;
    }

    //    const stxxl::vector<T> Diff(const stxxl::vector<T>& v, int lag = 1) {
    //
    //        stxxl::vector<T> difference;
    //
    //        for (int i = lag; i < v.size(); i += lag) {
    //            if (i < v.size() - 1) {
    //                difference.push_back(v[i - lag] - v[lag]);
    //            }
    //        }
    //
    //        return difference;
    //    }

    T Mean(const std::vector<T>& v) {
        T sum = std::accumulate(v.begin(), v.end(), 0.0);
        T mean = sum / v.size();

        return mean;
    }
    //
    //    T Mean(const stxxl::vector<T>& v) {
    //        T sum = std::accumulate(v.begin(), v.end(), 0.0);
    //        T mean = sum / v.size();
    //
    //        return mean;
    //    }

    T StandardDeviation(const std::vector<T>& v) {
        T sum = std::accumulate(v.begin(), v.end(), 0.0);
        T mean = sum / v.size();

        T sq_sum = std::inner_product(v.begin(), v.end(), v.begin(), 0.0);
        T stdev = std::sqrt(sq_sum / v.size() - mean * mean);

        return stdev;
    }

    //    T StandardDeviation(const stxxl::vector<T>& v) {
    //        T sum = std::accumulate(v.begin(), v.end(), 0.0);
    //        T mean = sum / v.size();
    //
    //        T sq_sum = std::inner_product(v.begin(), v.end(), v.begin(), 0.0);
    //        T stdev = std::sqrt(sq_sum / v.size() - mean * mean);
    //
    //        return stdev;
    //    }

    T StandardDeviation(const std::vector<T>& v, const T& mean) {
        T sq_sum = std::inner_product(v.begin(), v.end(), v.begin(), 0.0);
        T stdev = std::sqrt(sq_sum / v.size() - mean * mean);

        return stdev;
    }

    const std::vector<T> MeanOfParameterSet(const std::vector<std::vector<T> >& parameter_set) {
        std::vector<T> mean(this->parameters.size());

        for (int i = 0; i < parameter_set.size(); i++) {
            for (int j = 0; j < parameter_set[i].size(); j++) {
                mean[j] += parameter_set[i][j];
            }
        }

        for (int j = 0; j < parameter_set.size(); j++) {
            mean[j] /= parameter_set.size();
        }
        return mean;
    }

    const T Covariance(const std::vector<T>& x, const std::vector<T>& y) {
        T sum = 0;
        int n = x.size();
        T mean_x = Mean(x);
        T mean_y = Mean(y);
        for (int i = 0; i < n; i++) {
            sum = sum + (x[i] - mean_x) * (y[i] - mean_y);
        }
        return sum / (static_cast<T> (n) - 1);
    }

    /**
     * \f$\ cov = H^-1 \f$
     * @param x
     * @return 
     */
    const std::vector<std::vector<T> > CovarianceMatrix(const std::vector<T>& x) {

        //
        //        std::vector<std::vector<T> > cov(this->parameters.size(), std::vector<T>(this->parameters.size()));
        //
        //        for (int i = 0; i < parameter_set.size(); i++) {
        //            for (int j = 0; j < parameter_set[i].size(); j++) {
        //                for (int k = 0; k < parameter_set[i].size(); k++) {
        //                    cov[j][k] += (parameter_set[j] - this->mean_parameter_values[j])*
        //                            (parameter_set[k] - this->mean_parameter_values[k]);
        //                }
        //            }
        //        }
        //
        //        for (int i = 0; i < cov.size(); i++) {
        //            for (int j = 0; j < cov[i].size(); j++) {
        //                cov[i][j] /= (this->parameter_sets.size());
        //            }
        //        }
        //
        //        return cov;

        atl::Variable<T>::tape.Reset();
        Variable::tape.derivative_trace_level = atl::SECOND_ORDER_REVERSE;

        for (int i = 0; i < x.size(); i++) {
            this->parameters[i]->SetValue(x[i]);
        }

        Variable f = this->Evaluate();

        Variable::tape.AccumulateSecondOrder();
        atl::RealMatrix<T> inverse_hessian(this->parameters.size(), this->parameters.size());

        for (int i = 0; i < this->parameters.size(); i++) {
            for (int j = 0; j < this->parameters.size(); j++) {
                T dxx = atl::Variable<T>::tape.Value(this->parameters[i]->info->id,
                        this->parameters[j]->info->id);
                if (dxx != dxx) {//this is a big hack
                    dxx = std::numeric_limits<T>::min();
                }
                inverse_hessian(i, j) = dxx;
            }
        }
        inverse_hessian.Invert();

        std::vector<std::vector<T> > inverse_hessian_ret(this->parameters.size(), std::vector<T>(this->parameters.size()));
        for (int i = 0; i < this->parameters.size(); i++) {
            for (int j = 0; j < this->parameters.size(); j++) {
                inverse_hessian_ret[i][j] = inverse_hessian(i, j);
            }
        }

        return inverse_hessian_ret;
    }

    /**
     * \f$\ corr(x,y) = cov(x,y)/(sigma_x*sigma_y) \f$
     * 
     * @param covariance matrix
     * @return 
     */
    const std::vector<std::vector<T> > CorrelationMatrix(const std::vector<std::vector<T> >& covariance) {

        std::vector<std::vector<T> > correlation(this->parameters.size(), std::vector<T>(this->parameters.size()));
        for (int i = 0; i < this->parameters.size(); i++) {
            for (int j = 0; j < this->parameters.size(); j++) {
                //corr(x,y) = cov(x,y)/stdev_x*stdev_y
                correlation[i][j] = covariance[i][j] / (covariance[i][i] * covariance[j][j]);
            }
        }
        return correlation;
    }

};

#endif