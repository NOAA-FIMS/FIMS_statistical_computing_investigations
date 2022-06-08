#ifndef LOGISTIC_1_HPP
#define LOGISTIC_1_HPP


#include "../ATL/ATL.hpp"
#include "../functional_analysis.hpp"

template<typename T>
class Logistic_1 : public FunctionalAnalysis<T> {
public:
   typedef typename FunctionalAnalysis<double>::Variable Variable;

    Variable median;
    Variable slope;
    Variable X;
//    std::vector<Variable> x = {0.1,2,3,4,5,6,7,8,9,10};

    Logistic_1() {

    }

    virtual void Initialize() {
        this->name = "logistic";
        this->description = "Functional analysis of the logistic function.";
        this->median.SetName("median");
        this->median = 0.4;
        this->median.SetBounds(0.3, 0.7);
        this->RegisterParameter(median);
        
        
        this->slope.SetName("slope");
        this->slope=0.5;
        this->slope.SetBounds(0.1, 0.9);
        this->RegisterParameter(slope);
        
        this->X.SetName("x");   
        this->X.SetBounds(1,10);
        this->RegisterParameter(X,1.0);
        

    }

        /**
     * @brief The general logistic function
     * @param median the median (inflection point) of the logistic function
     * @param slope the slope of the logistic function
     * @param x the index the logistic function should be evaluated at
     * @return
     */
    virtual Variable Evaluate() {
        Variable ret;

        ret = (1.0) / (1.0 + atl::exp(-1.0 * slope * (X - median)));
        
        return ret;
    }



};

#endif
