#ifndef LOGISTIC_3_HPP
#define LOGISTIC_3_HPP


#include "../ATL/ATL.hpp"
#include "../functional_analysis.hpp"

template<typename T>
class Logistic_3 : public FunctionalAnalysis<T> {
public:
   typedef typename FunctionalAnalysis<double>::Variable Variable;

    Variable median;
    Variable invslope;
    std::vector<T> x = {0.1,2,3,4,5,6,7,8,9,10};

    Logistic_3() {

    }

    virtual void Initialize() {
        this->name = "logistic";
        this->description = "Functional analysis of the logistic function.";
        this->median.SetName("median");
        this->parameters.push_back(&(this->median));
        this->invslope.SetName("invslope");
        this->parameters.push_back(&(this->invslope));

    }

        /**
     * @brief The general logistic function
     * @param median the median (inflection point) of the logistic function
     * @param invslope the inverse slope of the logistic function
     * @param x the index the logistic function should be evaluated at
     * @return
     */
    virtual Variable Evaluate() {
        Variable ret;
        for(int i = 0; i < this->x.size(); i++){
        ret += (1.0) / (1.0 + atl::exp(-log(19) * (x[i] - median)/invslope));
        }
        return ret;
    }



};

#endif