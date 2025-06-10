# mk-simplex.r: Create open (0<Pj<1) or closed (0<=Pj<=1) proportion simplex from K-part compositions of N

# Load required package
if (!requireNamespace("ggtern", quietly = TRUE)) install.packages("ggtern")
library(ggtern)

# Load nexcom function
nexcom_path <- "nexcom.r"
if (!file.exists(nexcom_path)) stop("Required file 'nexcom.r' not found.")
source(nexcom_path)

# Prompt for simplex type and validate
choice <- tolower(readline("Type 'open' or 'closed' for simplex type: "))
if (!choice %in% c("open", "closed")) stop("Invalid choice. Must be 'open' or 'closed'.")

if (choice == "open") {
  K <- as.integer(readline("Enter number of categories (K): "))
  h <- as.numeric(readline("Enter simplex mesh (h in (0,1)): "))
  if (is.na(K) || is.na(h) || K < 1 || h <= 0 || h >= 1) stop("Invalid input. K > 0, 0 < h < 1.")
  
  N <- as.integer(1 / h) - K
  if (N <= 0) stop("Invalid mesh. Must have h < 1/K.")
  
} else {
  N <- as.integer(readline("Enter integer N: "))
  K <- as.integer(readline("Enter number of parts K: "))
  if (is.na(N) || is.na(K) || N < 1 || K < 1) stop("N and K must be positive integers.")
}

# Generate compositions
compositions <- nexcom(N, K)
comp_df <- as.data.frame(compositions)
colnames(comp_df) <- paste0("P.", seq_len(K))
cat(sprintf("Generated %d K-compositions of %d\n", nrow(comp_df), N))

# Normalize to proportions
if (choice == "open") {
  comp_df <- comp_df + 1
  prop_df <- comp_df / (N + K)
  filename <- sprintf("simplex-open_N%d_K%d.csv", N + K, K)
} else {
  prop_df <- comp_df / N
  filename <- sprintf("simplex-closed_N%d_K%d.csv", N, K)
}

# Output to CSV
tryCatch({
  write.csv(prop_df, filename, row.names = FALSE)
  cat("Saved to:", filename, "\n")
}, error = function(e) {
  cat("Error writing file:", e$message, "\n")
})
