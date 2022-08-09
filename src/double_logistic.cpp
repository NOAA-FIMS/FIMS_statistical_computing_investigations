#include <TMB.hpp>

template<class Type>
Type double_logistic(Type x, Type median_asc, Type median_desc,
                     Type slope_asc, Type slope_desc){
  Type ans = (1.0) / (1.0 + exp(-1.0 * slope_asc * (x - median_asc))) *
    (1.0 - (1.0) / (1.0 + exp(-1.0 * slope_desc * (x - median_desc))));
  
  return ans;
}

template<class Type>
Type objective_function<Type>::operator()(){
    
  DATA_VECTOR(y);
  DATA_VECTOR(N);
  DATA_VECTOR(age);
  DATA_INTEGER(doMax);
  PARAMETER(ln_median_asc);
  PARAMETER(ln_median_desc);
  PARAMETER(ln_slope_asc);
  PARAMETER(ln_slope_desc);
  
  Type median_asc = exp(ln_median_asc);
  Type median_desc = exp(ln_median_desc);
  Type slope_asc = exp(ln_slope_asc);
  Type slope_desc = exp(ln_slope_desc);
  
  int n = y.size(); 
  vector<Type> dl(n);
  
  //calculate double logistic
  for(int i=0; i<n; i++){
    dl(i) = double_logistic(age(i), median_asc, median_desc,
                            slope_asc, slope_desc);
  }
  if(doMax){
    dl = dl/max(dl);
  }
  
  Type nll = 0;
  
  for(int i=0; i<n; i++){
    Type l = dbinom(y(i), N(i), dl(i));
    nll -= log(squeeze(l));
  }
  
  return nll;
  
        
}
