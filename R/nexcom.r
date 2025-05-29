#
# nexcom.r
# nexcom script that produces the next composition of the integer N into K parts.
#
# function nexcom.alg
# Description: Returns the next composition vector
# 			   of the integer N into K parts.
#
#	Derived from the NEXKSB algorithm and FORTRAN subroutine written 
#   in "Combinational Algorithms for Computers and Calculators, Second 
#   Edition" by Albert Nijenhuis and Herbert S. Wilf.
#
# function arguments:
#	N	The input integer to partition into K parts.
#	K	Number of parts in a calculated composition. 
#	P	The input composition vector of N into K parts and the returned output composition.
#	MTC	Logical flag for whether the composition calculation is complete.
#       If MTC = TRUE, then the current composition is not the last composition.
#		If MTC=FALSE, the current composition is the last composition.
#	I	index variable.
#	J	index variable.
#
#Return:
#	A list containing (P, MTC, I, J).
#
nexcom.alg <- function (N, K, P, MTC, I, J) {

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

#FUNCTION nexcom
#Description: 
#     Wrapper function for function nexcom.alg. Allows user to 
#	  automate NEXKSB for all k-part compositions of n.
#
#Arguments:
#	N	Number whose compositions are desired.
#	K	Number of parts of desired composition. 
#
#Return:
#	A data frame containing all possible K-part compositions of N.
#
nexcom <- function (N, K) {

	rn.comp <- nexcom.alg(N, K, P = integer(K), MTC = FALSE, I = 0, J = 0)
	dt.comp <- data.frame(P = rbind(rn.comp$P)) 
	
	ii <- 0
	while(rn.comp$MTC == TRUE) {
		rn.comp <- nexcom.alg(N, K, P = rn.comp$P, MTC = rn.comp$MTC, I = rn.comp$I, J = rn.comp$J)
		dt.comp <- rbind(dt.comp, data.frame(P = rbind(rn.comp$P)))
		ii <- ii + 1
	}
	return(dt.comp)
}