#ifndef FUNCTIONAL_ANALYSIS_HPP
#define FUNCTIONAL_ANALYSIS_HPP
#include "ATL/ATL.hpp"
#include <vector>

template<typename T>
class FunctionalAnalysis {
public:
    typedef typename atl::Variable<T> Variable;
    T delta = 1e-4;
    std::vector<Variable*> parameters;
    std::vector<T> values;
    std::vector<std::vector<T> > input_values;
    std::vector<std::vector<T> > argument_values;
    std::map<uint32_t, std::vector<T> > derivatives;
    std::vector<std::vector<T> > covariance;
    std::vector<std::vector<T> > correlation;

    FunctionalAnalysis() {

    }

    virtual void Initialize() {

    }

    virtual Variable Evaluate()  = 0;

    void Analyze() {

        this->input_values.resize(this->parameters.size());
        for (int i = 0; i < this->parameters.size(); i++) {
            for (T v = this->parameters[i]->GetMinBoundary(); v <= this->parameters[i]->GetMaxBoundary(); v += delta) {
                input_values[i].push_back(v);
            }
        }

        std::cout<<"building argument set..."<<std::flush;
        std::vector<T> working(this->parameters.size());

        int count = 0;
        int current = 0;
        this->argument_builder(count, current, working, input_values, argument_values);
        std::cout<<"done.\n";


        //infentesimal step
        for (int i = 0; i < argument_values.size(); i++) {
            this->UpdateParameterSet(argument_values[i]);

            Variable::tape.Reset();
            Variable v = this->Evaluate();
            Variable::tape.AccumulateFirstOrder();
            std::cout<<"Function value: "<<v<<"\nGradient:\n";
            for(int p =0; p< this->parameters.size(); p++){
                std::cout<<Variable::tape.Value(this->parameters[p]->info->id)<<"  ";
            }
            std::cout<<"\n\n"<<std::flush;

        }






        //values

        //derivatives


    }

private:

    void argument_builder(int& count, int current, std::vector<T>& working, std::vector<std::vector<T> >& source, std::vector<std::vector<T> >& combos) {


        if (current == 0) {
            for (int i = 0; i < source[0].size(); i++) {
                std::vector<T> v;
                v.push_back(source[0][i]);
                argument_builder(count, current + 1, v, source, combos);
            }
        } else if (current < source.size() - 1) {
            std::vector<T> v = working;
            //            v.push_back(0);
            for (int i = 0; i < source[current].size(); i++) {
                v[v.size() - 1] = source[current][i];
                argument_builder(count, current + 1, v, source, combos);
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


};

#endif