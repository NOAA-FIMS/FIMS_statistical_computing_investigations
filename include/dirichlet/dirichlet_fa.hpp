#ifndef DIRICHLET_FA_HPP
#define DIRICHLET_FA_HPP
#include <vector>
#include "../functional_analysis.hpp"
#include "include/dirichlet.hpp"
#include "../util/string_util.hpp"

template <typename T>
struct simplex_data
{
    int nparts;
    T p_1;
    T p_2;
    T p_3;
    T p_4;
    T p_5;
    T p_6;
    T score;
    bool rebuild;
};

template <typename T>
class Dirichlet_Study_Base : public FunctionalAnalysis<T>
{
public:
    std::vector<std::vector<std::string>> simplex_from_csv;
    std::vector<simplex_data<T>> simplex_data;

    void parse_simplex_data()
    {
        std::cout << "Parsing simplex data from CSV..." << std::endl;
        size_t nps = 0; // number of parts in simplex
        if (!simplex_from_csv.empty())
        {
            nps = simplex_from_csv[0].size();
        }
        else
        {
            return; // no data to parse
        }

        for (size_t i = 1; i < simplex_from_csv.size(); i++)
        {
            auto &row = simplex_from_csv[i];

            ::simplex_data<T> data;
            data.nparts = nps;
            if (nps == 8)
            {
                data.p_1 = static_cast<T>(std::stod(row[0]));
                data.p_2 = static_cast<T>(std::stod(row[1]));
                data.p_3 = static_cast<T>(std::stod(row[2]));
                data.p_4 = static_cast<T>(std::stod(row[3]));
                data.p_5 = static_cast<T>(std::stod(row[4]));
                data.p_6 = static_cast<T>(std::stod(row[5]));
                data.score = static_cast<T>(std::stod(row[6]));
                if (row[7] == "TRUE" || row[7] == "1")
                {
                    data.rebuild = true;
                }
                else
                {
                    data.rebuild = false;
                }
                simplex_data.push_back(data);
            }
            else if (nps == 5)
            {
                data.p_1 = static_cast<T>(std::stod(row[0]));

                data.p_2 = static_cast<T>(std::stod(row[1]));
                data.p_3 = static_cast<T>(std::stod(row[2]));
                data.score = static_cast<T>(std::stod(row[3]));
                if (row[4] == "TRUE" || row[4] == "1")
                {
                    data.rebuild = true;
                }
                else
                {
                    data.rebuild = false;
                }
                simplex_data.push_back(data);
            }
        }
    }
    
    void SumToOne(std::vector<T> &p)

    {
        T sum = 0;
        for (const auto &val : p)
        {
            sum += val;
        }

        if (sum != 0)
        {
            for (auto &val : p)
            {
                val /= sum;
            }
        }
    }

    Dirichlet_Study_Base() {}

    Dirichlet_Study_Base(std::string csv_file)
    {
        this->simplex_from_csv = parseCSV(csv_file);
        this->parse_simplex_data();
    }
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
        this->parse_simplex_data();
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
        this->parse_simplex_data();
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
class Dirichlet_Fisch : public Dirichlet_Study_Base<T>
{
public:
    typedef typename FunctionalAnalysis<T>::Variable Variable;
    std::vector<int> x = {10, 15, 5};
    std::vector<Variable> p = {0.4, 0.4, 0.2};
    Variable theta = 0.01;

    Dirichlet_Fisch() {}

    Dirichlet_Fisch(std::string csv_file)
    {
        this->simplex_from_csv = parseCSV(csv_file);
        this->parse_simplex_data();
    }

    virtual void Initialize()
    {
        this->name = "dirichlet_fisch";
        this->description = "Functional analysis of the Fisch Dirichlet distribution.";

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
        this->parse_simplex_data();
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
        this->parse_simplex_data();
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