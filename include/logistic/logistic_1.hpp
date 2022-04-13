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
    std::vector<T> x = {0.1,2,3,4,5,6,7,8,9,10};

    Logistic_1() {

    }

    virtual void Initialize() {
        this->parameters.push_back(&(this->median));
        this->parameters.push_back(&(this->slope));

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
        for(int i = 0; i < this->x.size(); i++){
        ret += (1.0) / (1.0 + atl::exp(-1.0 * slope * (x[i] - median)));
        }
        return ret;
    }



};

#endif