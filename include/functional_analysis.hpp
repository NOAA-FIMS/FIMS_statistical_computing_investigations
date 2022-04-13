#ifndef FUNCTIONAL_ANALYSIS_HPP
#define FUNCTIONAL_ANALYSIS_HPP

#include <vector>

template<typename T>
class FunctionalAnalysis {
public:
    T delta = 1e-4;
    std::vector<T> parameters;

    FunctionalAnalysis() {

    }

    virtual void Initialize() {

    }

    virtual T Evaluate() {

    }

    void Analyze() {
    }


};

#endif