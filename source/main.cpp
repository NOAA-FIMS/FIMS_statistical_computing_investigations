#include <iostream>
#include "../include/logistic/logistic_1.hpp"
#include "../include/ATL/ATL.hpp"

int main(int argc, char** argv) {
    
    Logistic_1<double > logistic;
    logistic.Initialize();
    logistic.slope.SetBounds(0, 1.0);
    logistic.median.SetBounds(0.0, 10);
    logistic.delta = 0.005;
    logistic.Analyze();
    logistic.Finalize();
    
    return 0;
}



