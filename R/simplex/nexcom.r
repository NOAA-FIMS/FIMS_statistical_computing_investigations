# script nexcom.r
# nexcom(N, K) outputs a list containing the set of compositions
#              of the integer N into K parts. The composition list
#              is ordered lexicographically from the first composition
#              of P[first] = (N, 0, 0, ..., 0) to the last composition
#              of P[last] = (0, 0, 0, ..., N)
#
# function nexcom.step
# nexcom.step(N, K, P, MTC, I, J) returns the next K-dimensional composition 
#                                 vector of N, P[next], given the current 
#                                 composition vector of N, P[current].
# function arguments are:
#	N - The positive integer to compose into K parts.
#	K - The positive  integer number of parts, or categories in a composition vector. 
#	P - The current composition vector in the lexicographic set of all vectors.
#	MTC	- The logical flag indicating if the set of compositions of N is not complete
#       as in an acronym for "More To Come".
#   If MTC = TRUE, then the current composition is not the last composition
#                  in the lexicographic set of all vectors.
#		If MTC = FALSE, then the current composition is the last composition.
#	I - An index variable.
#	J - An index variable.
#
# returns - A list containing (P, MTC, I, J).
#
nexcom.step <- function (N, K, P, MTC, I, J) {

	if (MTC == FALSE) {
		P[1] <- N
		I <- N
		J <- 0	
		if (K != 1) {
			for (ii in 2:K) {
				P[ii] <- 0
			}
			MTC <- (P[K] != N)
			return(list(P = P, MTC = MTC, I = I, J = J))
		}
	}
	if (I > 1) J <- 0
	J <- J + 1
	I <- P[J]
	P[J] <- 0
	P[1] <- I - 1
	P[J + 1] <- P[J + 1] + 1
	MTC <- (P[K] != N)
	return(list(P = P, MTC = MTC, I = I, J = J))
}

# function nexcom
# nexcom() is a wrapper function that calls nexcom.step to step through
# the set of lexicographically-ordered K-compositions of N.
#
# function arguments are:
#	N - The positive integer to compose into K parts.
#	K - The number of parts of N, or categories in the composition. 
#
# returns - A data frame containing all possible K-part compositions of N.
#
nexcom <- function (N, K) {

	rn.comp <- nexcom.step(N, K, P = integer(K), MTC = FALSE, I = 0, J = 0)
	df.comp <- data.frame(P = rbind(rn.comp$P)) 
	
	ii <- 0
	while(rn.comp$MTC == TRUE) {
		rn.comp <- nexcom.step(N, K, P = rn.comp$P, MTC = rn.comp$MTC, I = rn.comp$I, J = rn.comp$J)
		df.comp <- rbind(df.comp, data.frame(P = rbind(rn.comp$P)))
		ii <- ii + 1
	}
	return(df.comp)
}