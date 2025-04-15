#include <iostream>
#include "../include/logistic/logistic_1.hpp"
#include "../include/logistic/logistic_2.hpp"
#include "../include/logistic/logistic_3.hpp"
#include "../include/logistic/double_logistic.hpp"
#include "../include/logistic/double_logistic_max.hpp"
#include "../include/lgamma/LogGammaLanczos.hpp"
#include "../include/lgamma/LogGammaSeries.hpp"
#include "../include/recruitment/alpha_beta.hpp"
#include "../include/ATL/ATL.hpp"
#include "../include/dirichlet/dirichlet_fa.hpp"
int main(int argc, char **argv)
{
    bool write_values = false;
    bool write_derivatives = false;
    std::vector<std::string> args;

    for (int i = 1; i < argc; ++i)
        args.push_back(std::string(argv[i]));

    for (int i = 0; i < args.size(); i++)
    {
        if (args[i] == "-write_values")
        {
            write_values = true;
        }

        if (args[i] == "-write_derivatives")
        {
            write_derivatives = true;
        }
    }

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

    // BevertonHoltAlphaBeta<double> bh_alpha_beta;
    // if (write_values) {
    //     bh_alpha_beta.write_values = true;
    // }
    // if (write_derivatives) {
    //     bh_alpha_beta.write_derivatives = true;
    // }
    // bh_alpha_beta.Initialize();
    // bh_alpha_beta.Analyze();
    // bh_alpha_beta.Finalize();
    //
    //    LogGammaSeries<double> lgamma_series;
    //    if (write_values) {
    //        lgamma_series.write_values = true;
    //    }
    //    if (write_derivatives) {
    //        lgamma_series.write_derivatives = true;
    //    }
    //    lgamma_series.Initialize();
    //    lgamma_series.Analyze();
    //    lgamma_series.Finalize();

    Dirichlet_Default<double> dirichlet_default;
    if (write_values)
    {
        dirichlet_default.write_values = true;
    }
    if (write_derivatives)
    {
        dirichlet_default.write_derivatives = true;
    }
    dirichlet_default.Initialize();
    dirichlet_default.Analyze();
    dirichlet_default.Finalize();

    Dirichlet_Thorson<double> dirichlet_thorson;
    if (write_values)
    {
        dirichlet_thorson.write_values = true;
    }
    if (write_derivatives)
    {
        dirichlet_thorson.write_derivatives = true;
    }
    dirichlet_thorson.Initialize();
    dirichlet_thorson.Analyze();
    dirichlet_thorson.Finalize();
    
    Dirichlet_Fischer<double> dirichlet_fischer;
    if (write_values)
    {
        dirichlet_fischer.write_values = true;
    }
    if (write_derivatives)
    {
        dirichlet_fischer.write_derivatives = true;
    }
    dirichlet_fischer.Initialize();
    dirichlet_fischer.Analyze();
    dirichlet_fischer.Finalize();

    return 0;
}
