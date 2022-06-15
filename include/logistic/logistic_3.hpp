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
    Variable X;
    //    std::vector<T> x = {0.1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    Logistic_3() {

    }

    virtual void Initialize() {
        //        this->name = "logistic";
        //        this->description = "Functional analysis of the logistic function.";
        //        this->median.SetName("median");
        //        this->parameters.push_back(&(this->median));
        //        this->invslope.SetName("invslope");
        //        this->parameters.push_back(&(this->invslope));

        this->name = "logistic_3";
        this->description = "Functional analysis of the logistic function.";
        this->median.SetName("median");
        this->median = 0.4;
        this->median.SetBounds(3.0, 7.0);
        this->RegisterParameter(median, 0.001);


        this->invslope.SetName("inverse_slope");
        this->invslope = 0.5;
        this->invslope.SetBounds(0.5, 0.7);
        this->RegisterParameter(invslope);

        this->X.SetName("x");
        this->X.SetBounds(1, 10);
        this->RegisterParameter(X, 1.0);

    }

    /**
     * @brief The general logistic function
     * @param median the median (inflection point) of the logistic function
     * @param invslope the inverse slope of the logistic function
     * @param x the index the logistic function should be evaluated at
     * @return
     */
    virtual Variable Evaluate() {
//        Variable ret = (1.0) / (1.0 + atl::exp(-1.0*std::log(19.0) * (X - median) / invslope));

        return (1.0) / (1.0 + atl::exp(-1.0*std::log(19.0) * (X - median) / invslope));
    }



};

#endif