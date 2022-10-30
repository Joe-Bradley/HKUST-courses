library(portfolioBacktest)
library(CVXR)

portfolio_fun <- function(dataset, ...) {
    prices <- dataset$adjusted
    N <- ncol(prices)
    X <- diff(log(prices))[-1]  # returns
    mu <- colMeans(X)
    Sigma <- cov(X)
    
    # portfolio design
    idx <- sort(mu/diag(Sigma), decreasing = TRUE, index.return = TRUE)$ix
    w <- rep(0, N)
    w[idx[1:round(N/5)]] <- 1/round(N/5)
    return(w)
}
