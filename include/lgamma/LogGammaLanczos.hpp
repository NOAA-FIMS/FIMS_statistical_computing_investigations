#ifndef LOGAMMALANZOS_HPP
#define LOGAMMALANZOS_HPP



#include "../ATL/ATL.hpp"
#include "../functional_analysis.hpp"

template<typename T>
class LogGammaLanzos : public FunctionalAnalysis<T> {
public:
    typedef typename FunctionalAnalysis<double>::Variable Variable;

    Variable X;
    //    std::vector<Variable> x = {0.1,2,3,4,5,6,7,8,9,10};

    LogGammaLanzos() {

    }

    virtual void Initialize() {
        this->name = "LogGammaLanzos";
        this->description = "Functional analysis of the log gamma series function using Stirling's approximation.";


        this->X.SetName("x");
        this->X.SetBounds(.001, 10);
        this->RegisterParameter(X, 0.005);


    }

    /**
     * @brief The general logistic function
     * @param median the median (inflection point) of the logistic function
     * @param slope the slope of the logistic function
     * @param x the index the logistic function should be evaluated at
     * @return
     */
    virtual Variable Evaluate() {
        // A & S eq. 6.1.48 (continuing fraction)
        Variable a0 = 1.0 / 12;
        Variable a1 = 1.0 / 30;
        Variable a2 = 53.0 / 210;
        Variable a3 = 195.0 / 371;
        Variable a4 = 22999.0 / 22737;
        Variable a5 = 29944523.0 / 19733142;
        Variable a6 = 109535241009.0 / 48264275462;

        Variable t6 = a6 / X;
        Variable t5 = a5 / (X + t6);
        Variable t4 = a4 / (X + t5);
        Variable t3 = a3 / (X + t4);
        Variable t2 = a2 / (X + t3);
        Variable t1 = a1 / (X + t2);
        Variable t0 = a0 / (X + t1);

        Variable result = t0 - X + ((X - 0.5) *
                atl::log(X)) +
                (0.5 * std::log(2 * M_PI));

        return result;
    }

#endif


};
