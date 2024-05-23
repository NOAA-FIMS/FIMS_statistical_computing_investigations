#ifndef ALPHA_BETA_HPP
#define ALPHA_BETA_HPP


#include "../ATL/ATL.hpp"
#include "../functional_analysis.hpp"

template<typename T>
class BevertonHoltAlphaBeta : public FunctionalAnalysis<T> {
public:
    typedef typename FunctionalAnalysis<double>::Variable Variable;
    
    
    //parameter set
    Variable alpha;
    Variable beta;
    
    //fixed
    Variable phi = 1.06;
    Variable S = 7049.0;
    
    BevertonHoltAlphaBeta(){
        
    }
    
    virtual void Initialize() {
        this->name = "bh_alpha_beta_recruitment";
        this->description = "Functional analysis of the alpha beta formulation for Beverton-Holt recruitment.";
        
        this->alpha.SetName("alpha");
        this->alpha.SetBounds(1.0, 10.0);
        this->RegisterParameter(this->alpha, 0.01);
        
        this->beta.SetName("beta");
        this->beta.SetBounds(1.0, 10.0);
        this->RegisterParameter(this->beta, 0.01);
        
        this->phi.SetName("phi");
        this->phi.SetBounds(0.5, 1.0);
        this->RegisterParameter(this->phi, 0.1);
        
        this->S.SetName("S");
        this->S.SetBounds(6000.0, 10000.0);
        this->RegisterParameter(this->S, 500);
        
    }
    
    
    virtual Variable Evaluate() {
        Variable h = (this->alpha*this->phi)/(4.0 + this->alpha*this->phi);
        
        Variable R0 = (1.0/this->beta)*(this->alpha - (1.0/this->phi));
        
        Variable R = (4.0*R0*h*this->S)/((1.0-h) * R0*this->phi + (5.0*h -1.0)*this->S);
        
        return R;
        
    }
    
};




#endif
