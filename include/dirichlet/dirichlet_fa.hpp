#ifndef DIRICHLET_FA_HPP
#define DIRICHLET_FA_HPP
#include <vector>
#include "../functional_analysis.hpp"
#include "include/dirichlet.hpp"
#include "../util/string_util.hpp"

template <typename T>
class Dirichlet_Study_Base : public FunctionalAnalysis<T>
{
public:
    std::vector<std::vector<std::string>> simplex_from_csv;
};

template <typename T>
class Dirichlet_Default : public Dirichlet_Study_Base<T>
{
public:
    typedef typename FunctionalAnalysis<T>::Variable Variable;

    std::vector<int> x = {10, 15, 5};
    std::vector<Variable> p = {0.4, 0.4, 0.2};
    Variable theta = 0.01;

    Dirichlet_Default() {}

    Dirichlet_Default(std::string csv_file)
    {
        this->simplex_from_csv = parseCSV(csv_file);
        std::cout<<"csv size = " <<this->simplex_from_csv.size()<<"\n";
    }

    virtual void Initialize()
    {

        this->name = "dirichlet_default";
        this->description = "Functional analysis of the default Dirichlet distribution.";

        // this->theta.SetName("theta");
        //  this->theta.SetBounds(0.00001, 5.0);
        //   this->RegisterParameter(this->theta, 0.01);

        for (size_t i = 0; i < x.size(); ++i)
        {
            this->p[i].SetName("p" + std::to_string(i));
            this->p[i].SetBounds(0.00001, 0.9999999);
            this->RegisterParameter(this->p[i], 0.1);
        }
    }

    virtual atl::Variable<T> Evaluate()
    {
        return fims_math::ddirichlet_multinom<atl::Variable<T>,
                                              fims_math::DirichletType::DEFAULT>(x, p, theta);
    }
};

template <typename T>
class Dirichlet_Thorson : public Dirichlet_Study_Base<T>
{

public:
    typedef typename FunctionalAnalysis<T>::Variable Variable;

    std::vector<int> x = {10, 15, 5};
    std::vector<Variable> p = {0.4, 0.4, 0.2};
    Variable theta = 0.01;

    Dirichlet_Thorson() {}

    Dirichlet_Thorson(std::string csv_file)
    {
        this->simplex_from_csv = parseCSV(csv_file);
    }

    virtual void Initialize()
    {
        this->name = "dirichlet_thorson";
        this->description = "Functional analysis of the Thorson Dirichlet distribution.";

        this->theta.SetName("theta");
        this->theta.SetBounds(0.00001, 5.0);
        this->RegisterParameter(this->theta, 0.01);

        for (size_t i = 0; i < x.size(); ++i)
        {
            this->p[i].SetName("p" + std::to_string(i));
            this->p[i].SetBounds(0.00001, 0.9999999);
            this->RegisterParameter(this->p[i], 0.1);
        }
    }
    virtual atl::Variable<T> Evaluate()
    {
        return fims_math::ddirichlet_multinom<atl::Variable<T>,
                                              fims_math::DirichletType::THORSON>(x, p, theta);
    }
};

template <typename T>
class Dirichlet_Fischer : public Dirichlet_Study_Base<T>
{
public:
    typedef typename FunctionalAnalysis<T>::Variable Variable;
    std::vector<int> x = {10, 15, 5};
    std::vector<Variable> p = {0.4, 0.4, 0.2};
    Variable theta = 0.01;

    Dirichlet_Fischer() {}

    Dirichlet_Fischer(std::string csv_file)
    {
        this->simplex_from_csv = parseCSV(csv_file);
    }

    virtual void Initialize()
    {
        this->name = "dirichlet_fischer";
        this->description = "Functional analysis of the Fischer Dirichlet distribution.";

        this->theta.SetName("theta");
        this->theta.SetBounds(0.00001, 5.0);
        this->RegisterParameter(this->theta, 0.01);

        for (size_t i = 0; i < x.size(); ++i)
        {
            this->p[i].SetName("p" + std::to_string(i));
            this->p[i].SetBounds(0.00001, 0.999999);
            this->RegisterParameter(this->p[i], 0.1);
        }
    }
    virtual atl::Variable<T> Evaluate()
    {
        return fims_math::ddirichlet_multinom<atl::Variable<T>,
                                              fims_math::DirichletType::FISCHER>(x, p, theta);
    }
};

template <typename T>
class Dirichlet_Linear : public Dirichlet_Study_Base<T>
{
public:
    typedef typename FunctionalAnalysis<T>::Variable Variable;

    std::vector<int> x = {10, 15, 5};
    std::vector<Variable> p = {0.4, 0.4, 0.2};
    Variable theta = 0.01;

    Dirichlet_Linear() {}

    Dirichlet_Linear(std::string csv_file)
    {
        this->simplex_from_csv = parseCSV(csv_file);
    }

    virtual void Initialize()
    {
        this->name = "dirichlet_linear";
        this->description = "Functional analysis of the Linear Dirichlet distribution.";

        this->theta.SetName("theta");
        this->theta.SetBounds(0.00001, 5.0);
        this->RegisterParameter(this->theta, 0.01);

        for (size_t i = 0; i < x.size(); ++i)
        {
            this->p[i].SetName("p" + std::to_string(i));
            this->p[i].SetBounds(0.00001, 0.999999);
            this->RegisterParameter(this->p[i], 0.1);
        }
    }

    virtual atl::Variable<double> Evaluate()
    {
        return fims_math::ddirichlet_multinom<atl::Variable<double>,
                                              fims_math::DirichletType::LINEAR>(x, p, theta);
    }
};

template <typename T>
class Dirichlet_Saturated : public Dirichlet_Study_Base<T>
{
public:
    typedef typename FunctionalAnalysis<T>::Variable Variable;

    std::vector<int> x = {10, 15, 5};
    std::vector<Variable> p = {0.4, 0.4, 0.2};
    Variable beta = 0.01;

    Dirichlet_Saturated() {}

    Dirichlet_Saturated(std::string csv_file)
    {
        this->simplex_from_csv = parseCSV(csv_file);
    }

    virtual void Initialize()
    {
        this->name = "dirichlet_saturated";
        this->description = "Functional analysis of the Saturated Dirichlet distribution.";

        this->beta.SetName("beta");
        this->beta.SetBounds(0.00001, 5.0);
        this->RegisterParameter(this->beta, 0.01);

        for (size_t i = 0; i < x.size(); ++i)
        {
            this->p[i].SetName("p" + std::to_string(i));
            this->p[i].SetBounds(0.00001, 0.999999);
            this->RegisterParameter(this->p[i], 0.1);
        }
    }

    virtual atl::Variable<double> Evaluate()
    {
        return fims_math::ddirichlet_multinom<atl::Variable<double>,
                                              fims_math::DirichletType::SATURATED>(x, p, beta);
    }
};

#endif