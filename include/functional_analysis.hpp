#ifndef FUNCTIONAL_ANALYSIS_HPP
#define FUNCTIONAL_ANALYSIS_HPP
#include "ATL/ATL.hpp"
#include <vector>
#include <limits>
#include <chrono>

#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

template<typename T>
class FunctionalAnalysis {
public:
    typedef typename atl::Variable<T> Variable;

    T delta = 1e-4;

    //parameter list
    std::vector<Variable*> parameters;

    //all possible input values
    std::vector<std::vector<T> > input_values;

    //parameter set
    std::vector<std::vector<T> > parameter_sets;

    //function values from each evaluation
    std::vector<T> values;

    //derivatives from each evaluation
    std::map<uint32_t, std::vector<T> > derivatives;

    //Covariance indicates the direction of the linear relationship between variables.
    //values are standardized
    std::vector<std::vector<T> > covariance;

    //Correlation measures both the strength and direction of the linear relationship between two variables.
    //values are not standardized
    std::vector<std::vector<T> > correlation;

    bool is_continuous = false;

    //min evaluated function value
    T min_value = std::numeric_limits<T>::max();

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

    FunctionalAnalysis() {

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

    /**
     * Analyzes computational properties of a child function.
     */
    void Analyze() {

        this->start_time = std::chrono::system_clock::now();

        //initialize all parameter values
        this->input_values.resize(this->parameters.size());
        for (int i = 0; i < this->parameters.size(); i++) {
            for (T v = this->parameters[i]->GetMinBoundary(); v <= this->parameters[i]->GetMaxBoundary(); v += delta) {
                input_values[i].push_back(v);
            }
        }

        //create argument list. Combination of input_values size(input_values) choose size(parameters)
        std::cout << "\nBuilding argument set..." << std::flush;
        std::vector<T> working(this->parameters.size());
        int count = 0;
        int current = 0;
        this->ArgumentBuilder(count, current, working, input_values, parameter_sets);
        std::cout << "done.\n";


        //Run Infinitesimal step - Riemann
        for (int i = 0; i < parameter_sets.size(); i++) {

            //show progress
            this->Progress(((double) i / (double) parameter_sets.size()));

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

        //quantify continuity

        //quantify smoothness

        //covariance

        //correlations


        this->end_time = std::chrono::system_clock::now();
        this->runtime = std::chrono::duration_cast<std::chrono::minutes>(end_time - start_time).count();
    }

    void Finalize() {

    }

private:

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
    void ArgumentBuilder(int& count, int current, std::vector<T>& working,
            std::vector<std::vector<T> >& source,
            std::vector<std::vector<T> >& combos) {


        if (current == 0) {
            for (int i = 0; i < source[0].size(); i++) {
                std::vector<T> v;
                v.push_back(source[0][i]);
                ArgumentBuilder(count, current + 1, v, source, combos);
            }
        } else if (current < source.size() - 1) {
            std::vector<T> v = working;
            //            v.push_back(0);
            for (int i = 0; i < source[current].size(); i++) {
                v[v.size() - 1] = source[current][i];
                ArgumentBuilder(count, current + 1, v, source, combos);
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
    void Progress(double percentage) {
        int val = (int) (percentage * 100);
        int lpad = (int) (percentage * PBWIDTH);
        int rpad = PBWIDTH - lpad;
        printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
        std::cout << std::flush;
    }

};

#endif