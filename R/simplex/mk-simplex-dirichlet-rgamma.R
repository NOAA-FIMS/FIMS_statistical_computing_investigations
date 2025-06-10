# Load required package
if (!requireNamespace("ggtern", quietly = TRUE)) {
  install.packages("ggtern")
}
library(ggtern)  # for ternary plot

# Prompt user for number of categories (K), number of samples (n), and alpha parameters
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

# Manually sample from Dirichlet using gamma distributions
set.seed(123)
gamma_samples <- matrix(0, nrow = n, ncol = K)
for (i in 1:K) {
  gamma_samples[, i] <- rgamma(n, shape = alpha[i], rate = 1)
}
row_sums <- rowSums(gamma_samples)
dirichlet_samples <- gamma_samples / row_sums

# Convert to data frame
samples_df <- as.data.frame(dirichlet_samples)
colnames(samples_df) <- c("A", "B", "C")

# Save to CSV
write.csv(samples_df, file = "dirichlet_samples.csv", row.names = FALSE)
cat("Saved samples to 'dirichlet_samples.csv'\n")

# Plot with ggtern
ggtern(data = samples_df, aes(x = A, y = B, z = C)) +
  geom_point(alpha = 0.5, size = 0.5) +
  theme_bw() +
  labs(title = "Dirichlet Samples on 2D Simplex", T = "A", L = "B", R = "C")
