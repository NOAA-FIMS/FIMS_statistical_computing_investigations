library(TMB)
compile('src/double_logistic.cpp')
dyn.load(dynlib('src/double_logistic'))

double_logistic <- function(x, median_asc, median_desc, slope_asc, slope_desc){
  (1.0) / (1.0 + exp(-1.0 * slope_asc * (x - median_asc))) *
    (1.0 - (1.0) / (1.0 + exp(-1.0 * slope_desc * (x - median_desc))))
}
# 
# median_asc     1     -   5   
# slope_asc      0.1   -   0.3 
# median_desc    5     -   10  
# slope_desc     0.1   -   0.3 
# X              1     -   10  
foo = double_logistic(1:10, 1, .1, 5, .1)
plot(1:10, foo)
foo = double_logistic(1:10, 5, .3, 10, .3)
plot(1:10, foo)


median_asc <- seq(1,5,1)
slope_asc <- seq(0.1,0.3,0.1)
median_desc <- seq(5,10,1)
slope_desc <- seq(0.1, 0.3, 0.1)
age_vec <- 1:10

pars <- expand.grid(true_median_asc = median_asc,
                    true_median_desc = median_desc,
                    true_slope_asc = slope_asc,
                    true_slope_desc = slope_desc)
pars$est_median_asc = 0
pars$est_median_desc = 0
pars$est_slope_asc = 0
pars$est_slope_desc = 0
pars$gr_median_asc = 0
pars$gr_median_desc = 0
pars$gr_slope_asc = 0
pars$gr_slope_desc = 0
pars$max_grad = 0
pars$convergence = 0

pars$est_median_asc_std = 0
pars$est_median_desc_std = 0
pars$est_slope_asc_std = 0
pars$est_slope_desc_std = 0
pars$gr_median_asc_std = 0
pars$gr_median_desc_std = 0
pars$gr_slope_asc_std = 0
pars$gr_slope_desc_std = 0
pars$max_grad_std = 0
pars$convergence_std = 0

for(i in 1:nrow(pars)){
  set.seed(i)
  dl.pars <- pars[i,]
  dl <- double_logistic(age_vec, dl.pars$true_median_asc, 
                        dl.pars$true_median_desc,
                        dl.pars$true_slope_asc, 
                        dl.pars$true_slope_desc)
  dl.stand <- dl/max(dl)
  
  #simulate number selected per age
  n.obs <- 50
  N <- y <- age <- matrix(0, n.obs, length(age_vec))
  for(j in 1:n.obs){
    N[j,] <- sample(5:10, length(age_vec), replace = TRUE)
    y[j,] <- rbinom(length(age_vec), N[j,], dl)
    age[j,] <- age_vec
  }
  
  Data <- list(y = as.vector(y),
               N = as.vector(N),
               age = as.vector(age),
               doMax = FALSE)
  Pars <- list(ln_median_asc = 0,
               ln_median_desc = 0,
               ln_slope_asc = 0,
               ln_slope_desc = 0)
  obj <- MakeADFun(Data, Pars, DLL = "double_logistic")
  opt <- nlminb(obj$par, obj$fn, obj$gr, 
                lower = rep(-10, 4),
                upper = rep(10, 4),
                control = list(eval.max = 1000, iter.max = 1000))
  nms <- c("est_median_asc", "est_median_desc", 
           "est_slope_asc", "est_slope_desc")
  pars[i, nms] <- exp(opt$par)
  nms <- c("gr_median_asc", "gr_median_desc", 
           "gr_slope_asc", "gr_slope_desc")
  pars[i, nms] <- obj$gr()[1,]
  pars[i,"max_grad"] <- max(obj$gr())
  pars[i,"convergence"] <- opt$convergence
  
  #Now fit with max implemented
  Data <- list(y = as.vector(y),
               N = as.vector(N),
               age = as.vector(age),
               doMax = TRUE)
  Pars <- list(ln_median_asc = 0,
               ln_median_desc = 0,
               ln_slope_asc = 0,
               ln_slope_desc = 0)
  obj <- MakeADFun(Data, Pars, DLL = "double_logistic")
  opt <- try(nlminb(obj$par, obj$fn, obj$gr, 
                lower = rep(-10, 4),
                upper = rep(10, 4),
                control = list(eval.max = 1000, iter.max = 1000)))
  par.nms <- c("est_median_asc_std", "est_median_desc_std", 
           "est_slope_asc_std", "est_slope_desc_std")
  gr.nms <- c("gr_median_asc_std", "gr_median_desc_std", 
              "gr_slope_asc_std", "gr_slope_desc_std")
  if(class(opt)!= 'try-error'){
    pars[i, par.nms] <- exp(opt$par)
    pars[i, gr.nms] <- obj$gr()[1,]
    pars[i,"max_grad_std"] <- max(obj$gr())
    pars[i,"convergence_std"] <- opt$convergence
  } else {
    pars[i, par.nms] <- NA
    pars[i, gr.nms] <- NA
    pars[i,"max_grad_std"] <- NA
    pars[i,"convergence_std"] <- NA
  }
  
  
  
}
#number of models that failed to converged (n = 270)
sum(pars$convergence)
sum(is.na(pars$convergence_std))
sum(pars$convergence_std)
#convergence failure
pars[which(pars$convergence == 1),1:4]

pars$bias_median_asc <- pars$true_median_asc - pars$est_median_asc
pars$bias_median_desc <- pars$true_median_desc - pars$est_median_desc
pars$bias_slope_asc <- pars$true_slope_asc - pars$est_slope_asc
pars$bias_slope_desc <- pars$true_slope_desc - pars$est_slope_desc

pars$bias_median_asc_std <- pars$true_median_asc - pars$est_median_asc_std
pars$bias_median_desc_std <- pars$true_median_desc - pars$est_median_desc_std
pars$bias_slope_asc_std <- pars$true_slope_asc - pars$est_slope_asc_std
pars$bias_slope_desc_std <- pars$true_slope_desc - pars$est_slope_desc_std

library(magrittr)
library(ggplot2)
pars %>% dplyr::select(., bias_median_asc | bias_median_asc_std |
                         convergence | true_median_asc) %>%
  tidyr::pivot_longer(., 1:2, names_to = "type", values_to = "bias") %>%
  ggplot(., aes(x = bias, fill = factor(convergence))) + geom_histogram() + 
  facet_grid(factor(true_median_asc)~type)

pars %>% dplyr::select(., bias_median_desc | bias_median_desc_std  |
                         convergence) %>%
  tidyr::pivot_longer(., 1:2, names_to = "type", values_to = "bias") %>%
  ggplot(., aes(x = bias, fill = factor(convergence))) + geom_histogram() + 
  facet_wrap(~type)

pars %>% dplyr::select(., bias_slope_asc | bias_slope_asc_std  |
                         convergence) %>%
  tidyr::pivot_longer(., 1:2, names_to = "type", values_to = "bias") %>%
  ggplot(., aes(x = bias, fill = factor(convergence))) + geom_histogram() + 
  facet_wrap(~type)

pars %>% dplyr::select(., bias_slope_desc | bias_slope_desc_std  |
                         convergence) %>%
  tidyr::pivot_longer(., 1:2, names_to = "type", values_to = "bias") %>%
  ggplot(., aes(x = bias, fill = factor(convergence))) + geom_histogram() + 
  facet_wrap(~type)
