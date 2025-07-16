#include <iostream>

// #include "../include/ATL/ATL.hpp"
#include "dirichlet_fa.hpp"
int main(int argc, char **argv)
{

    std::string file = "/Users/matthew.supernaw/Dirichlet-study/5_29/FIMS_statistical_computing_investigations/include/dirichlet/data/3-parts-example.csv";

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

    Dirichlet_Default<double> dirichlet_default(file);
    if (write_values)
    {
        dirichlet_default.write_values = true;
    }
    if (write_derivatives)
    {
        dirichlet_default.write_derivatives = true;
    }
    dirichlet_default.Initialize();
    dirichlet_default.build_parameter_sets = false; // disable building parameter sets for now
    dirichlet_default.Analyze();
    dirichlet_default.Finalize();

    Dirichlet_Thorson<double> dirichlet_thorson(file);
    if (write_values)
    {
        dirichlet_thorson.write_values = true;
    }
    if (write_derivatives)
    {
        dirichlet_thorson.write_derivatives = true;
    }
    dirichlet_thorson.Initialize();
    dirichlet_thorson.build_parameter_sets = false; // disable building parameter sets for now
    dirichlet_thorson.Analyze();
    dirichlet_thorson.Finalize();

    Dirichlet_Fisch<double> dirichlet_fisch(file);
    if (write_values)
    {
        dirichlet_fisch.write_values = true;
    }
    if (write_derivatives)
    {
        dirichlet_fisch.write_derivatives = true;
    }
    dirichlet_fisch.Initialize();
    dirichlet_fisch.build_parameter_sets = false; // disable building parameter sets for now
    dirichlet_fisch.Analyze();
    dirichlet_fisch.Finalize();

    Dirichlet_Linear<double> dirichlet_linear(file);
    if (write_values)
    {
        dirichlet_linear.write_values = true;
    }
    if (write_derivatives)
    {
        dirichlet_linear.write_derivatives = true;
    }
    dirichlet_linear.Initialize();
    dirichlet_linear.build_parameter_sets = false; // disable building parameter sets for now
    dirichlet_linear.Analyze();
    dirichlet_linear.Finalize();

    Dirichlet_Saturated<double> dirichlet_saturated(file);
    if (write_values)
    {
        dirichlet_saturated.write_values = true;
    }
    if (write_derivatives)
    {
        dirichlet_saturated.write_derivatives = true;
    }
    dirichlet_saturated.Initialize();
    dirichlet_saturated.build_parameter_sets = false; // disable building parameter sets for now
    dirichlet_saturated.Analyze();
    dirichlet_saturated.Finalize();

    return 0;
}
