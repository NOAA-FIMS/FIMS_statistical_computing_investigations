#
# nexcom.r
# R script that produces the next composition of the integer N into K parts.
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
#	K	Number of parts in a calculated composistion. 
#	R	The input composition vector of N into K parts and the returned output composition.
#	MTC	Logical flag for whether the composition calculation is complete.
#       If MTC = TRUE, then the current composition is not the final Kth composition.
#		If MTC=FALSE, the current composition is the final Kth composition.
#	I	index variable.
#	J	index variable.
#
#Return:
#	A list containing (R, MTC, I, J).
#
nexcom.alg <- function (N, K, R, MTC, I, J) {

	if (MTC == FALSE) {
		R[1] <- N
		I <- N
		J <- 0	
		if (K != 1) {
			for (ii in 2:K) {
				R[ii] <- 0
			}
			MTC <- (R[K] != N)
			return(list(R = R, MTC = MTC, I = I, J = J))
		}
	}
	if (I > 1) J <- 0
	J <- J + 1
	I <- R[J]
	R[J] <- 0
	R[1] <- I - 1
	R[J + 1] <- R[J + 1] + 1
	MTC <- (R[K] != N)
	return(list(R = R, MTC = MTC, I = I, J = J))
}

#FUNCTION nexcom
#Description: 
#     Wrapper function for function nexcom.alg. Allows user to 
#	  automate NEXKSB for all k-part compositions of n.
#
#Arguments:
#	N	Number whose composistions are desired.
#	K	Number of parts of desired composistion. 
#
#Return:
#	A data frame containing all possible K-part compositions of N.
#
nexcom <- function (N, K) {

	rn.comp <- nexcom.alg(N, K, R = integer(K), MTC = FALSE, I = 0, J = 0)
	dt.comp <- data.frame(R = rbind(rn.comp$R)) 
	
	ii <- 0
	while(rn.comp$MTC == TRUE) {
		rn.comp <- nexcom.alg(N, K, R = rn.comp$R, MTC = rn.comp$MTC, I = rn.comp$I, J = rn.comp$J)
		dt.comp <- rbind(dt.comp, data.frame(R = rbind(rn.comp$R)))
		ii <- ii + 1
	}
	return(dt.comp)
}