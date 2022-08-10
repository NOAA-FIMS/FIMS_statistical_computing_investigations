/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: mattadmin
 *
 * Created on August 10, 2022, 11:53 AM
 */

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <random>

using namespace std;

template<typename REAL_T>
class LogitParameterTransformation {
public:

    virtual REAL_T External2Internal(REAL_T val, REAL_T min_, REAL_T max_)const {
        if (val == min_) {
            val += static_cast<REAL_T> (1e-8);
        } else if (val == max_) {
            val -= static_cast<REAL_T> (1e-8);
        }

        REAL_T p = ((val) - min_) / (max_ - min_);
        return std::log(p / (1.0 - p));
    }

    virtual REAL_T Internal2External(REAL_T val, REAL_T min_, REAL_T max_) const {
        REAL_T p = std::exp(val) / (1.0 + std::exp(val));
        return p * (max_ - min_) + min_;
    }

    virtual REAL_T DerivativeInternal2External(REAL_T val, REAL_T min_, REAL_T max_)const {
        return (std::exp(val) * std::log(M_E)*(max_ - min_)) / (std::exp(val) + 1.0)-
                (std::exp(static_cast<REAL_T> (2.0 * val)) * std::log(M_E)*(max_ - min_)) / std::pow((std::exp(val) + 1), 2.0);
    }
};

template<typename REAL_T>
class SinParameterTransformation {
public:

    virtual REAL_T External2Internal(REAL_T val, REAL_T min_, REAL_T max_) const {
        if (val < min_ || val > max_)std::cout << "value exceeds bounds....\n";
        //            return std::asin((2.0 * val) / (max_ - min_) - min_ / (max_ - min_) - max_ / (max_ - min_));
        return std::asin((2.0 * (val - min_) / (max_ - min_)) - 1.0);
    }

    virtual REAL_T Internal2External(REAL_T val, REAL_T min_, REAL_T max_) const {
        //            return min_ + (0.5 * (max_ - min_))*(std::sin(val) + 1.);
        return min_ + (std::sin(val) + 1.0)*((max_ - min_) / 2.0);
    }

    virtual REAL_T DerivativeInternal2External(REAL_T val, REAL_T min_, REAL_T max_)const {
        return 0.5 * ((max_ - min_) * std::cos(val));
        //            return ((max_ - min_) * std::cos(val)) / 2.0;
    }
};

template<typename REAL_T>
class ADMBParameterTransformation {
public:

    virtual REAL_T External2Internal(REAL_T val, REAL_T min_, REAL_T max_) const {
        return std::asin(2.0 * (val - min_) / (max_ - min_) - 1.0) / (M_PI / 2.0);
    }

    virtual REAL_T Internal2External(REAL_T val, REAL_T min_, REAL_T max_) const {
        return min_ + (max_ - min_)*(.5 * std::sin(val * M_PI / 2.0) + .5);
    }

    virtual REAL_T DerivativeInternal2External(REAL_T val, REAL_T min_, REAL_T max_)const {
        return (max_ - min_)*.5 * M_PI / 2.0 * std::cos(val * M_PI / 2.0);
    }
};

/*
 *   
 */
int main(int argc, char** argv) {

    SinParameterTransformation<double> lt;

    double step = 0.1;
    double x = 5;
    double ix = 5;
    double dx = 2.0;
    double lb = 0.01;
    double ub = 10.0;
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(5.0, 2.0);


    std::cout << "starting x: " << x << "\n";
    std::cout << "starting transformed x: " << ix << "\n\n";
    for (int i = 0; i < 50; i++) {



        dx= distribution(generator);// += 0.2;
       
        x = x - step*dx;
        std::cout << "****************************************\ndx = " << dx << "\n";
         std::cout<<"x = "<<x<<"\n";
        if (x < lb) {
            std::cout << "Error: x exceeds lower bounds.\n\n";
        }

        if (x > ub) {
            std::cout << "Error: x exceeds upper bounds.\n\n";
        }





        double internal_x = lt.External2Internal(ix, lb, ub);
        std::cout << "internal x:  " << internal_x << "\n";
        double internal_dx = lt.DerivativeInternal2External(ix, lb, ub) * dx;

        double new_internal_x = internal_x - step*internal_dx;
        ix = lt.Internal2External(new_internal_x, lb, ub);

        std::cout << "transformed x: " << ix << "\n";

        if (ix < lb) {
            std::cout << "Error: ix exceeds lower bounds.\n\n";
        }

        if (ix > ub) {
            std::cout << "Error: ix exceeds upper bounds.\n\n";
        }
        std::cout << "****************************************\n\n";
    }
    return 0;
}

