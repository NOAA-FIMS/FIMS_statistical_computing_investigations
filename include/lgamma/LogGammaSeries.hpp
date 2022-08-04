#ifndef LOGAMMASERIES_HPP
#define LOGAMMASERIES_HPP



#include "../ATL/ATL.hpp"
#include "../functional_analysis.hpp"

template<typename T>
class LogGammaSeries : public FunctionalAnalysis<T> {
public:
    typedef typename FunctionalAnalysis<double>::Variable Variable;

    Variable X;
    //    std::vector<Variable> x = {0.1,2,3,4,5,6,7,8,9,10};

    LogGammaSeries() {

    }

    virtual void Initialize() {
        this->name = "LogGammaSeries";
        this->description = "Functional analysis of the log gamma series function using Stirling's approximation.";


        this->X.SetName("x");
        this->X.SetBounds(.001, 10);
        this->RegisterParameter(X, 0.0005);


    }

    /**
     * @brief The general logistic function
     * @param median the median (inflection point) of the logistic function
     * @param slope the slope of the logistic function
     * @param x the index the logistic function should be evaluated at
     * @return
     */
    virtual Variable Evaluate() {
        // A & S 6.1.41 (Stirling's approximation)
        Variable x1 = (X - 0.5) * atl::log(X);
        Variable x3 = 0.5 * std::log(2 * M_PI);

        Variable x4 = 1.0 / (12 * X);
        Variable x5 = 1.0 / (360 * X * X * X);
        Variable x6 = 1.0 / (1260 * X * X * X * X * X);
        Variable x7 = 1.0 / (1680 * X * X * X * X * X * X * X);
        // more terms possible
        return x1 - X + x3 + x4 - x5 + x6 - x7;
    }



};


#endif