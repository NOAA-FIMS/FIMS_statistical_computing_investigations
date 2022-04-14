#ifndef FUNCTIONAL_ANALYSIS_HPP
#define FUNCTIONAL_ANALYSIS_HPP
#include "ATL/ATL.hpp"
#include <vector>
#include <limits>

#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

template<typename T>
class FunctionalAnalysis {
public:
    typedef typename atl::Variable<T> Variable;
    T delta = 1e-4;
    std::vector<Variable*> parameters;
    std::vector<std::vector<T> > input_values;
    std::vector<std::vector<T> > argument_values;
    std::vector<T> values;
    std::map<uint32_t, std::vector<T> > derivatives;
    std::vector<std::vector<T> > covariance;
    std::vector<std::vector<T> > correlation;
    bool is_continuous = false;
    T min_value = std::numeric_limits<T>::max();
    T max_value = std::numeric_limits<T>::max();
    std::vector<T> argument_min;
    std::vector<T> argument_max;

    FunctionalAnalysis() {

    }

    virtual void Initialize() {

    }

    virtual Variable Evaluate() = 0;

    void Analyze() {

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
        this->ArgumentBuilder(count, current, working, input_values, argument_values);
        std::cout << "done.\n";


        //Run Infinitesimal step - Riemann
        for (int i = 0; i < argument_values.size(); i++) {

//            std::cout << (i + 1) << " of " << argument_values.size() << " (" << (((double) i / (double) argument_values.size())*100) << "%)" << std::endl;
            this->UpdateParameterSet(argument_values[i]);

            this->Progress(((double) i / (double) argument_values.size()));
            //reset the tape
            Variable::tape.Reset();

            Variable v = this->Evaluate();
            //store values
            this->values.push_back(v.GetValue());

            //check min and max value
            if (v < this->min_value) {
                this->min_value = v.GetValue();
                this->argument_min = argument_values[i];
            }

            if (v > this->max_value) {
                this->max_value = v.GetValue();
                this->argument_max = argument_values[i];
            }


            //compute derivatives
            Variable::tape.AccumulateFirstOrder();


//            std::cout << "Function value: " << v << "\nGradient:\n";
            for (int p = 0; p< this->parameters.size(); p++) {
//                std::cout << Variable::tape.Value(this->parameters[p]->info->id) << "  ";
                //store derivatives
                this->derivatives[this->parameters[p]->info->id].push_back(Variable::tape.Value(this->parameters[p]->info->id));
            }
//            std::cout << "\n\n" << std::flush;

        }

        //quantify continuity

        //quantify smoothness

        //quantify correlations

    }

    void Finalize() {

    }

private:

    void ArgumentBuilder(int& count, int current, std::vector<T>& working, std::vector<std::vector<T> >& source, std::vector<std::vector<T> >& combos) {


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

    void UpdateParameterSet(std::vector<T>& v) {
        for (int i = 0; i < v.size(); i++) {
            this->parameters[i]->SetValue(v[i]);
        }
    }

    void Progress(double percentage) {
        int val = (int) (percentage * 100);
        int lpad = (int) (percentage * PBWIDTH);
        int rpad = PBWIDTH - lpad;
        printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
        fflush(stdout);
    }

};

#endif