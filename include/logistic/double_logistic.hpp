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
    Variable X;

    DoubleLogistic() {

    }

    virtual void Initialize() {
        this->name = "double_logistic";
        this->description = "Functional analysis of the double logistic function.";

        this->median_asc.SetName("median_asc");
        this->median_asc.SetBounds(1.0, 5.0);
        this->RegisterParameter(this->median_asc, 0.1);

        this->slope_asc.SetName("slope_asc");
        this->slope_asc.SetBounds(0.1, 0.3);
        this->RegisterParameter(this->slope_asc, 0.01);


        this->median_desc.SetName("median_desc");
        this->median_desc.SetBounds(5.0, 10.0);
        this->RegisterParameter(this->median_desc, 0.1);


        this->slope_desc.SetName("slope_desc");
        this->slope_desc.SetBounds(0.1, 0.3);
        this->RegisterParameter(this->slope_desc, 0.01);

        this->X.SetBounds(1, 10);
        this->X.SetName("X");
        this->RegisterParameter(this->X, 1.0);

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
        return (1.0) / (1.0 + exp(-1.0 * slope_asc * (X - median_asc))) *
                (1.0 - (1.0) / (1.0 + exp(-1.0 * slope_desc * (X - median_desc))));
    }


};

#endif