// Simple linear regression
#include <TMB.hpp>


template <class Type>
Type objective_function<Type>::operator()()
{
  DATA_VECTOR(y);
  DATA_MATRIX(X);
  DATA_INTEGER(transform);
  
  PARAMETER_VECTOR(beta);
  PARAMETER(theta);
  
  Type sigma;
  if(transform == 0){
    sigma = theta;
  }
  if(transform == 1){
    sigma = exp(theta);
  }
  
  Type nll = 0;
  vector<Type> mu = X*beta;

  for(int i=0; i<y.size(); i++){
    nll -= dnorm(y(i), mu(i), sigma, true);
  }
  
  REPORT(sigma);
  ADREPORT(sigma);
  
  
  return nll;
}
