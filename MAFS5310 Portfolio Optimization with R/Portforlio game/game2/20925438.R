library(portfolioBacktest)
library(riskParityPortfolio)
library(CVXR)

# RPP
portfolio_fun <- function(dataset, ...) {
    prices <- dataset$adjusted
    log_returns <- diff(log(prices))[-1]
    return(riskParityPortfolio(cov(log_returns))$w)
}