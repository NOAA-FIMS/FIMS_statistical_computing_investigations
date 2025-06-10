# Load required packages
if (!requireNamespace("MCMCpack", quietly = TRUE)) {
  install.packages("MCMCpack")
}
if (!requireNamespace("ggtern", quietly = TRUE)) {
  install.packages("ggtern")
}
library(MCMCpack)  # for rdirichlet()
library(ggtern)    # for ternary plots

# Prompt user for number of categories (K), number of samples (n), and Dirichlet parameters
K <- as.integer(readline(prompt = "Enter the number of categories K (must be 3 for plotting): "))
if (K != 3) stop("ggtern visualization only works for K = 3.")

n <- as.integer(readline(prompt = "Enter the number of Dirichlet samples to draw: "))

# Ask for Dirichlet alpha parameters
cat("Enter 3 Dirichlet alpha parameters separated by space (default = 1 1 1): ")
alpha_input <- scan(what = numeric(), nmax = 3, quiet = TRUE)

# Use default alpha = 1 if user enters nothing
if (length(alpha_input) == 0) {
  alpha <- rep(1, 3)
} else {
  alpha <- alpha_input
}

# Sample from Dirichlet distribution
set.seed(123)
samples <- rdirichlet(n, alpha)
samples_df <- as.data.frame(samples)
colnames(samples_df) <- c("A", "B", "C")

# Save samples to CSV
write.csv(samples_df, file = "dirichlet_samples.csv", row.names = FALSE)
cat("Saved samples to 'dirichlet_samples.csv'\n")

# Plot samples on ternary diagram
ggtern(data = samples_df, aes(x = A, y = B, z = C)) +
  geom_point(alpha = 0.5, size = 0.5) +
  theme_bw() +
  labs(title = "Dirichlet Samples on 2D Simplex", T = "A", L = "B", R = "C")