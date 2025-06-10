library(tidyverse)

simplex5D <- nexcom(10,6)

simplex5D <- simplex5D/10.0

simplex5D

parts6 <- simplex5D

parts6 <- mutate(parts6, score = 1.618*P.1 - P.2^2 + exp(P.3) - 4*P.4 + P.5 + 3*P.6 - 0.50)

parts6 <- mutate(parts6, positive = score>0)

write_csv(parts6,"6-parts-example.csv")

