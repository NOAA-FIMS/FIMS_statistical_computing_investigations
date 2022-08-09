library(TMB)
compile('src/transform_sigma.cpp')
dyn.load(dynlib('src/transform_sigma'))

#Simulate data for sig = 1

sim.dat <- function(sig, n, seed = NA){
  if(!is.na(seed)) set.seed(seed)
  beta <- c(0.5,2)
  X <- cbind(rep(1,n), 1:n)
  mu <- X%*%beta
  return(rnorm(n, mu, sig))
}

y <- sim.dat(sig = 1, n = 100, seed = 123)

#Fit using constrained optimization
Data <- list(y = y, 
             X = cbind(rep(1,n), 1:n),
             transform = 0)
Pars <- list(beta = c(0,0), theta = 1)
obj <- MakeADFun(data = Data, 
                  parameters = Pars, 
                  DLL = "transform_sigma")
opt <- nlminb(obj$par, obj$fn, obj$gr, 
               lower = c(-Inf, -Inf, 0.0001),
               upper = c(Inf, Inf, Inf),
              control = list(trace = 1))
opt$par 
sdr1 <- sdreport(obj)
summary(sdr1, "report")

#Fit using parameter transformation
Data$transform = 1
Pars$theta = 0
obj <- MakeADFun(data = Data, 
                 parameters = Pars, 
                 DLL = "transform_sigma")
opt <- nlminb(obj$par, obj$fn, obj$gr, 
              control = list(trace = 1))
opt$par
sdr2 <- sdreport(obj)
#similar output
summary(sdr2, "report")
summary(sdr1, "report")

#repeat using small sig
y <- sim.dat(sig = 0.001, n = 100, seed = 123)

#Fit using constrained optimization
Data <- list(y = y, 
             X = cbind(rep(1,n), 1:n),
             transform = 0)
Pars <- list(beta = c(0,0), theta = 1)
obj <- MakeADFun(data = Data, 
                 parameters = Pars, 
                 DLL = "transform_sigma")
opt <- nlminb(obj$par, obj$fn, obj$gr, 
              lower = c(-Inf, -Inf, 0.0001),
              upper = c(Inf, Inf, Inf),
              control = list(trace = 1))
opt$par 
sdr1 <- sdreport(obj)
summary(sdr1, "report")

#Fit using parameter transformation
Data$transform = 1
Pars$theta = 0
obj <- MakeADFun(data = Data, 
                 parameters = Pars, 
                 DLL = "transform_sigma")
opt <- nlminb(obj$par, obj$fn, obj$gr, 
              control = list(trace = 1))
opt$par
sdr2 <- sdreport(obj)
#similar output but SE Nan for constrained optimization
summary(sdr2, "report")
summary(sdr1, "report")

#Run simulation study
n.sim <- 1000
sig.out <- matrix(0, n.sim, 4)
iter.out <- matrix(0, n.sim, 2)
sig.sim <- 0.001
for(i in 1:n.sim){
  #repeat using small sig
  y <- sim.dat(sig = sig.sim, n = 100)
  
  #Fit using constrained optimization
  Data <- list(y = y, 
               X = cbind(rep(1,n), 1:n),
               transform = 0)
  Pars <- list(beta = c(0,0), theta = 1)
  obj <- MakeADFun(data = Data, 
                   parameters = Pars, 
                   DLL = "transform_sigma",
                   silent = TRUE)
  opt <- nlminb(obj$par, obj$fn, obj$gr, 
                lower = c(-Inf, -Inf, 0.0001),
                upper = c(Inf, Inf, Inf))

  sdr1 <- sdreport(obj)
  sig.out[i, 1:2] <- summary(sdr1, "report")
  iter.out[i,1] <- opt$iterations
  
  #Fit using parameter transformation
  Data$transform = 1
  Pars$theta = 0
  obj <- MakeADFun(data = Data, 
                   parameters = Pars, 
                   DLL = "transform_sigma",
                   silent = TRUE)
  opt <- nlminb(obj$par, obj$fn, obj$gr)
  sdr2 <- sdreport(obj)
  sig.out[i, 3:4] <- summary(sdr2, "report")
  iter.out[i,2] <- opt$iterations
  print(i)
}
apply(sig.out, 2, mean, na.rm = TRUE)
#around half constrained optimization result in NA SE for sig
apply(sig.out, 2, function(x) sum(is.na(x)))
#number of iterations for constrained optimization
hist(iter.out[,1])
#number of iterations for parameter transformation
hist(iter.out[,2])
