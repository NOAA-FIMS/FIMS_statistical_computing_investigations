#ifndef DOUBLE_LOGISTIC_HPP
#define DOUBLE_LOGISTIC_HPP


#include "../ATL/ATL.hpp"
#include "../functional_analysis.hpp"

template<typename T>
class DoubleLogistic : public FunctionalAnalysis<T> {
public:
   typedef typename FunctionalAnalysis<double>::Variable Variable;

    Variable median_asc;
    Variable slope_asc;
    Variable median_desc;
    Variable slope_desc;
    std::vector<T> x = {0.1,2,3,4,5,6,7,8,9,10};

    DoubleLogistic() {

    }

    virtual void Initialize() {
        this->name = "double logistic";
        this->description = "Functional analysis of the double logistic function.";
        this->median_asc.SetName("median_asc");
        this->parameters.push_back(&(this->median_asc));
        this->slope_asc.SetName("slope_asc");
        this->parameters.push_back(&(this->slope_asc));
        this->median_desc.SetName("median_desc");
        this->parameters.push_back(&(this->median_desc));
        this->slope_desc.SetName("slope_desc");
        this->parameters.push_back(&(this->slope_desc));

    }

/**
 * @brief The general double logistic function
 *
 * \f$ \frac{1.0}{ 1.0 + exp(-1.0 * slope_{asc} (x - median_{asc}))}
 * \left(1-\frac{1.0}{ 1.0 + exp(-1.0 * slope_{desc} (x - median_{desc}))}
 * \right)\f$
 *
 * @param median_asc the median (inflection point) of the ascending limb of the
 * double logistic function
 * @param slope_asc the slope of the ascending limb of the double logistic
 * function
 * @param median_desc the median (inflection point) of the descending limb of
 * the double logistic function, where median_desc > median_asc
 * @param slope_desc the slope of the descending limb of the double logistic
 * function
 * @param x the index the logistic function should be evaluated at
 * @return
 */
    virtual Variable Evaluate() {
       return (1.0) / (1.0 + exp(-1.0 * slope_asc * (x - median_asc))) *
         (1.0 - (1.0) / (1.0 + exp(-1.0 * slope_desc * (x - median_desc))));
    }


};

#endif