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

    Dirichlet_Linear<double> dirichlet_linear;
    if (write_values)
    {
        dirichlet_linear.write_values = true;
    }
    if (write_derivatives)
    {
        dirichlet_linear.write_derivatives = true;
    }
    dirichlet_linear.Initialize();
    dirichlet_linear.Analyze();
    dirichlet_linear.Finalize();
    
    Dirichlet_Saturated<double> dirichlet_saturated;
    if (write_values)
    {
        dirichlet_saturated.write_values = true;
    }
    if (write_derivatives)
    {
        dirichlet_saturated.write_derivatives = true;
    }
    dirichlet_saturated.Initialize();
    dirichlet_saturated.Analyze();  
    dirichlet_saturated.Finalize();

    return 0;
}
