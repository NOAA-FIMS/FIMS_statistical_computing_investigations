#include <iostream>
#include "../include/logistic/logistic_1.hpp"
#include "../include/ATL/ATL.hpp"

int main(int argc, char** argv) {
    
    Logistic_1<double > logistic;
    logistic.Initialize();
    logistic.slope.SetBounds(0, 1.0);
    logistic.median.SetBounds(3.0, 4.0);
    logistic.Analyze();
    
    return 0;
}



