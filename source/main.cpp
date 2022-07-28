#include <iostream>
#include "../include/logistic/logistic_1.hpp"
#include "../include/logistic/logistic_2.hpp"
#include "../include/logistic/logistic_3.hpp"
#include "../include/logistic/double_logistic.hpp"
#include "../include/logistic/double_logistic_max.hpp"
#include "../include/lgamma/LogGammaLanczos.hpp"
#include "../include/lgamma/LogGammaSeries.hpp"
#include "../include/ATL/ATL.hpp"

int main(int argc, char** argv) {

    //    Logistic_1<double > logistic1;
    //    logistic1.Initialize();
    //    logistic1.Analyze();
    //    logistic1.Finalize();
    //
    //    Logistic_2<double > logistic2;
    //    logistic2.Initialize();
    //    logistic2.Analyze();
    //    logistic2.Finalize();
    //
    //    Logistic_3<double > logistic3;
    //    logistic3.Initialize();
    //    logistic3.Analyze();
    //    logistic3.Finalize();
    //
    //    DoubleLogistic<double> double_logistic;
    //    double_logistic.Initialize();
    //    double_logistic.Analyze();
    //    double_logistic.Finalize();
    //
    //    DoubleLogisticMax<double> double_logistic_max;
    //    double_logistic_max.Initialize();
    //    double_logistic_max.Analyze();
    //    double_logistic_max.Finalize();

    LogGammaLanzos<double> lgamma_lanczos;
    lgamma_lanczos.Initialize();
    lgamma_lanczos.Analyze();
    lgamma_lanczos.Finalize();

    LogGammaSeries<double> lgamma_series;
    lgamma_series.Initialize();
    lgamma_series.Analyze();
    lgamma_series.Finalize();

    return 0;
}



