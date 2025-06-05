# script mk-simplex-closed.r

# Prompt user for N and K
N <- as.integer(readline(prompt = "Enter the integer N: "))
K <- as.integer(readline(prompt = "Enter the number of parts K: "))

# Check inputs
if (is.na(N) || is.na(K) || N < 1 || K < 1) {
  stop("Invalid input. N must be a positive integer, K must be a positive integer.")
}

# Load nexcom function safely
if (!file.exists("nexcom.r")) {
  stop("Required file 'nexcom.r' not found in the working directory.")
}
source("nexcom.r")

# Generate K-compositions of N
compositions <- nexcom(N, K)
comp_df <- as.data.frame(compositions)
colnames(comp_df) <- paste0("P.", 1:K)

# Report number of compositions generated
cat("Generated", nrow(comp_df), "K-compositions of", N, "\n")

# Convert to proportions by dividing each element by N
prop_df <- comp_df / N

# Output to CSV file with error handling
output_file <- sprintf("kcompositions_N%d_K%d_proportions.csv", N, K)
tryCatch({
  write.csv(prop_df, file = output_file, row.names = FALSE)
  cat("Proportion data frame saved to:", output_file, "\n")
}, error = function(e) {
  cat("Failed to write CSV file:", e$message, "\n")
})
