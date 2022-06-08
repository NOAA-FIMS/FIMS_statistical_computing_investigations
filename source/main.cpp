#include <iostream>
#include "../include/logistic/logistic_1.hpp"
#include "../include/logistic/double_logistic_max.hpp"
#include "../include/ATL/ATL.hpp"

int main(int argc, char** argv) {
//
    Logistic_1<double > logistic;
    logistic.Initialize();
    logistic.Analyze();
    logistic.Finalize();

    DoubleLogisticMax<double> double_logistic;
    double_logistic.Initialize();
    double_logistic.Analyze();
    double_logistic.Finalize();
    return 0;
}



