library(tidyverse)

simplex2D <- nexcom(100,3)

simplex2D <- simplex2D/100.0

simplex2D

Chook <- simplex2D

Chook <- mutate(Chook, score = P.2*0.334+P.3*0.426-0.516)
# FWIW The score is the predicted reduction in fishing
# mortality by switching the proportion of tuna hooks (P.2)
# and the proportion of Japanese hooks (P.3) to circle hooks
# (P.1) and -0.516 is the target fishing mortality reduction.
# Given we do not know the proportions of hook types
# across the WCPFC tuna longline fleets, the proportion
# simplex is used to gather information on the score across
# all possible combinations of hook proportions.

Chook <- mutate(Chook, rebuild = score>=0)

write_csv(Chook,"3-parts-example.csv")

