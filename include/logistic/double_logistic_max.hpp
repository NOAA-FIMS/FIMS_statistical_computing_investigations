#ifndef DOUBLE_LOGISTIC_MAX_HPP
#define DOUBLE_LOGISTIC_MAX_HPP


#include "../ATL/ATL.hpp"
#include "../functional_analysis.hpp"

template<typename T>
class DoubleLogisticMax : public FunctionalAnalysis<T> {
public:
    typedef typename FunctionalAnalysis<double>::Variable Variable;

    Variable median_asc;
    Variable slope_asc;
    Variable median_desc;
    Variable slope_desc;
    Variable max_;
    Variable X;
    std::vector<T> x = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    DoubleLogistic() {

    }

    virtual void Initialize() {
        this->name = "double logistic";
        this->description = "Functional analysis of the double logistic function.";

        this->median_asc.SetName("median_asc");
        this->RegisterParameter(this->median_asc);

        this->slope_asc.SetName("slope_asc");
        this->RegisterParameter(this->slope_asc);


        this->median_desc.SetName("median_desc");
        this->RegisterParameter(this->median_desc);


        this->slope_desc.SetName("slope_desc");
        this->RegisterParameter(this->slope_desc);

        this->X.SetBounds(1, 10);
        this->RegisterParameter(this->X, 1.0);


    }

    void updateMax() {
        Variable temp;
        max_ = 0;

        int n = x.size();
        for (int i = 0; i < n; i++) {
            temp = (1.0) / (1.0 + exp(-1.0 * slope_asc * (x[i] - median_asc))) *
                    (1.0 - (1.0) / (1.0 + exp(-1.0 * slope_desc * (x[i] - median_desc))));
            max_ = atl::ad_max(temp, max_)
        }
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
     * @param max_ the maximum logistic value used for standardization
     * @param x the index the logistic function should be evaluated at
     * @return
     */
    virtual Variable Evaluate() {
        updateMax();
        Variable ret;
        ret = (1.0) / (1.0 + exp(-1.0 * slope_asc * (x - median_asc))) *
                (1.0 - (1.0) / (1.0 + exp(-1.0 * slope_desc * (x - median_desc))));
        ret = ret / max_;
        return ret;
    }


};

#endif