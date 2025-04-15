#ifndef DIRICHLET_FA_HPP
#define DIRICHLET_FA_HPP
#include <vector>
#include "../functional_analysis.hpp"
#include "include/dirichlet.hpp"

template <typename T>
class Dirichlet_Default : public FunctionalAnalysis<T>
{
public:
    typedef typename FunctionalAnalysis<double>::Variable Variable;

    std::vector<int> x = {10, 15, 5};
    std::vector<Variable> p = {0.4, 0.4, 0.2};
    Variable theta = 0.01;

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
class Dirichlet_Thorson : public FunctionalAnalysis<T>
{

public:
    typedef typename FunctionalAnalysis<double>::Variable Variable;

    std::vector<int> x = {10, 15, 5};
    std::vector<Variable> p = {0.4, 0.4, 0.2};
    Variable theta = 0.01;

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
class Dirichlet_Fischer : public FunctionalAnalysis<T>
{
public:
    typedef typename FunctionalAnalysis<double>::Variable Variable;
    std::vector<int> x = {10, 15, 5};
    std::vector<Variable> p = {0.4, 0.4, 0.2};
    Variable theta = 0.01;

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

#endif