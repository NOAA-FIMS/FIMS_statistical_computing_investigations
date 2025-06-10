# script mk-simplex-normalized-uniform.r

# Load required package
if (!requireNamespace("ggtern", quietly = TRUE)) {
  install.packages("ggtern")
}
library(ggtern)

# Prompt for simplex type
choice <- readline(prompt = "Type 'open' for open simplex or 'closed' for closed simplex: ")

# Validate simplex type
if (!choice %in% c("open", "closed")) {
  stop("Invalid choice. Please type 'open' or 'closed'.")
}

# Prompt for number of points
n_input <- readline(prompt = "Enter the number of points to simulate in the simplex: ")
n <- as.numeric(n_input)

# Validate number
if (is.na(n) || n <= 0) {
  stop("Invalid number of points. Please enter a positive integer.")
}

# Generate random proportions
set.seed(42)
A <- runif(n)
B <- runif(n)
C <- runif(n)
total <- A + B + C
A <- A / total
B <- B / total
C <- C / total

# Apply open simplex condition
if (choice == "open") {
  epsilon <- 1e-2
  keep <- A > epsilon & B > epsilon & C > epsilon
  A <- A[keep]
  B <- B[keep]
  C <- C[keep]
}

# Create data frame
df <- data.frame(A = A, B = B, C = C)

# Plot the simplex
ggtern(data = df, aes(x = A, y = B, z = C)) +
  geom_point(size = 0.5, alpha = 0.5) +
  theme_bw() +
  labs(title = paste("Normalized Uniform on 2D Simplex"))
