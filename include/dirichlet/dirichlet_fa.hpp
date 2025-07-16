#ifndef DIRICHLET_FA_HPP
#define DIRICHLET_FA_HPP
#include <vector>
#include <algorithm>
#include <iostream>
#include "../functional_analysis.hpp"
#include "include/dirichlet.hpp"
#include "../util/string_util.hpp"

template <typename T>
struct simplex_data
{
    int nparts;
    std::vector<T> p;
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
std::ostream &operator<<(std::ostream &os, const std::vector<T> &data)
{
    os << "[";
    for (size_t i = 0; i < data.size(); ++i)
    {
        os << data[i];
        if (i < data.size() - 1)
        {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

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
            data.p.resize(nps - 1);
            for (size_t j = 0; j < nps - 1; j++)
            {
                data.p[j] = static_cast<T>(std::stod(row[j]));
            }

            if (row[nps - 1] == "TRUE" || row[nps - 1] == "1")
            {
                data.rebuild = true;
            }
            else
            {
                data.rebuild = false;
            }
            simplex_data.push_back(data);
        }
        this->build_simplex_data();
    }

    void build_simplex_data()
    {
        std::cout << "Building simplex data..." << std::endl;
        // this->input_values.resize(simplex_data.size());
        for (auto &data : simplex_data)
        {
            std::vector<T> p(data.nparts - 2);
            for (size_t j = 0; j < data.nparts - 2; j++)
            {
                p[j] = data.p[j] + 1e-8; // add a small value to avoid zero probabilities
            }
            this->Normalize(p);
            this->input_values.push_back(p);
        }
        std::cout << "input_values size: " << this->input_values.size() << "\n";
    }

    void build_input_values()
    {
        std::cout << "Making input values..." << std::endl;
        this->input_values.clear();
        for (size_t i = 0; i < simplex_data.size(); i++)
        {
            for (size_t j = 0; j < simplex_data.size(); j++)
            {
                std::vector<T> input_row;
                input_row.insert(input_row.end(), simplex_data[i].p.begin(), simplex_data[i].p.end() - 1);
                input_row.insert(input_row.end(), simplex_data[j].p.begin(), simplex_data[j].p.end() - 1);
                this->input_values.push_back(input_row);
            }
        }
        for (size_t i = 0; i < this->input_values.size(); i++)
        {
            std::cout << "Input values: " << this->input_values[i] << "\n";
        }
        std::cout << "input_values size: " << this->input_values.size() << "\n";
    }

    /**
     * @brief Normalize the simplex data to sum to one.
     * @param p The vector of probabilities.
     */
    void Normalize(std::vector<atl::Variable<T>> &p)

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

    void Normalize(std::vector<T> &p)

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
        this->build_input_values();
        exit(0);
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
            // this->p[i].SetBounds(0.00001, 0.9999999);
            this->RegisterParameter(this->p[i], 0.1);
        }
    }

    virtual atl::Variable<T> Evaluate()
    {
        this->Normalize(this->p);
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
            // this->p[i].SetBounds(0.00001, 0.9999999);
            this->RegisterParameter(this->p[i], 0.1);
        }
    }
    virtual atl::Variable<T> Evaluate()
    {
        // this->Normalize(this->p);
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
            // this->p[i].SetBounds(0.00001, 0.999999);
            this->RegisterParameter(this->p[i], 0.1);
        }
    }
    virtual atl::Variable<T> Evaluate()
    {
        this->Normalize(this->p);
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
            // this->p[i].SetBounds(0.00001, 0.999999);
            this->RegisterParameter(this->p[i], 0.1);
        }
    }

    virtual atl::Variable<double> Evaluate()
    {
        this->Normalize(this->p);
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
        // this->beta.SetBounds(0.00001, 5.0);
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
        this->Normalize(this->p);
        return fims_math::ddirichlet_multinom<atl::Variable<double>,
                                              fims_math::DirichletType::SATURATED>(x, p, beta);
    }
};

#endif