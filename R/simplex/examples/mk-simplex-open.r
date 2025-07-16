# script mk-simplex-open.r

# Prompt user for number of categories (K) and simplex mesh (d)
K <- as.integer(readline(prompt = "Enter the number of categories K: "))
h <- as.numeric(readline(prompt = "Enter the simplex mesh h: "))

# Check inputs
if (is.na(K) || is.na(h) || K < 1 || h >= 1) {
  stop("Invalid input. K must be a positive integer, h must be in (0,1).")
}

# Calculate integer N to make K compositions with mesh h
N <- as.integer(1/h) - K

# Check that N is feasible
if (is.na(N) || N <= 0 ) {
  stop("Invalid input. Mesh is too large for K. Set h < 1/K.")
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

# Convert to proportions by adding 1 to each category
# and dividing each category by (N + K)
comp_df <- comp_df + 1
prop_df <- comp_df / (N + K)

# Output to CSV file with error handling
output_file <- sprintf("kcompositions_N%d_K%d_proportions.csv", N, K)
tryCatch({
  write.csv(prop_df, file = output_file, row.names = FALSE)
  cat("Proportion data frame saved to:", output_file, "\n")
}, error = function(e) {
  cat("Failed to write CSV file:", e$message, "\n")
})
