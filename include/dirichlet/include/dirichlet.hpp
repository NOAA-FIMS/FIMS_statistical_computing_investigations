#ifndef DIRCHLET_HPP
#define DIRCHLET_HPP

#include <vector>
#include <numeric>
#include <cmath>

namespace fims_math
{

    template <typename T>
    T lgamma_lanczos(const T &X)
    {
        // A & S eq. 6.1.48 (continuing fraction)
        T a0 = 1.0 / 12;
        T a1 = 1.0 / 30;
        T a2 = 53.0 / 210;
        T a3 = 195.0 / 371;
        T a4 = 22999.0 / 22737;
        T a5 = 29944523.0 / 19733142;
        T a6 = 109535241009.0 / 48264275462;

        T t6 = a6 / X;
        T t5 = a5 / (X + t6);
        T t4 = a4 / (X + t5);
        T t3 = a3 / (X + t4);
        T t2 = a2 / (X + t3);
        T t1 = a1 / (X + t2);
        T t0 = a0 / (X + t1);

        T result = t0 - X + ((X - 0.5) * atl::log(X)) +
                   (0.5 * std::log(2.0 * M_PI));

        return result;
    }

    enum class DirichletType
    {
        THORSON = 0,
        FISCHER,
        LINEAR,
        SATURATED,
        DEFAULT
    };

    template <typename T>
    inline T log_dirichlet_multinom(const std::vector<int> &x, const std::vector<T> &alpha)
    {
        int N = std::accumulate(x.begin(), x.end(), 0);
        T sum_alpha = std::accumulate(alpha.begin(), alpha.end(), T(0));

        T log_prob = lgamma_lanczos(T(N + 1.0)) + lgamma_lanczos(T(sum_alpha)) - lgamma_lanczos(T(N + sum_alpha));

        for (size_t k = 0; k < x.size(); ++k)
        {
            log_prob += lgamma_lanczos(T(x[k] + alpha[k])) - lgamma_lanczos(T(alpha[k])) - lgamma_lanczos(T(x[k] + 1.0));
        }

        return log_prob;
    }

    template <typename T>
    inline T log_dirichlet_multinom_thorson(const std::vector<int> &x, const std::vector<T> &p, T theta)
    {
        std::vector<T> alpha(p.size());
        for (size_t k = 0; k < p.size(); ++k)
            alpha[k] = p[k] * theta;
        return log_dirichlet_multinom(x, alpha);
    }

    template <typename T>
    inline T log_dirichlet_multinom_fisch(const std::vector<int> &x, const std::vector<T> &p, T theta)
    {
        int N = std::accumulate(x.begin(), x.end(), 0);
        T neff = ((T(1.0) + theta) * static_cast<T>(N)) / (T(1.0) + theta * static_cast<T>(N));

        std::vector<T> alpha(p.size());
        for (size_t k = 0; k < p.size(); ++k)
            alpha[k] = p[k] * neff;

        return log_dirichlet_multinom(x, alpha);
    }

    template <typename T>
    inline T log_dirichlet_multinom_linear(const std::vector<int> &x, const std::vector<T> &p, T theta)
    {
         return 0.0;//silence compiler warning
    }

    template <typename T>
    inline T log_dirichlet_multinom_saturated(const std::vector<int> &x, const std::vector<T> &p, T beta)
    {
        return 0.0;//silence compiler warning
    }

    template <typename T, DirichletType type = DirichletType::DEFAULT>
    T ddirichlet_multinom(const std::vector<int> &x,
                          const std::vector<T> &p,
                          T theta,
                          bool give_log = true)
    {
        T log_prob = 0.0;

        switch (type)
        {
        case DirichletType::THORSON:
            log_prob = log_dirichlet_multinom_thorson(x, p, theta);
            break;
        case DirichletType::FISCHER:
            log_prob = log_dirichlet_multinom_fisch(x, p, theta);
            break;
            case DirichletType::LINEAR:
            log_prob = log_dirichlet_multinom_linear(x, p, theta);
            break;
        case DirichletType::SATURATED:
            log_prob = log_dirichlet_multinom_saturated(x, p, theta);
            break;
        default:
            log_prob = log_dirichlet_multinom(x, p);
            break;
        }

        if (give_log)
        {
            return log_prob;
        }
        else
        {
            return std::exp(log_prob);
        }
    }

}

#endif