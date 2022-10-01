# The parameter setting for portfolioBacktest() is
# shortselling = TRUE
# leverage = 1
# lookback = 252
# optimize_every = 20
# rebalance_every = 1

# The ranking is based on the weighted average of the rank percentiles of the following score quantities:
# Sharpe ratio - 15%
# max drawdown - 15%
# failure rate - 70%

library(portfolioBacktest)
library(riskParityPortfolio)
library(CVXR)

# RPP 
portfolio_fun <- function(dataset, ...) {
    prices <- dataset$adjusted
    log_returns <- diff(log(prices))[-1]
    return(riskParityPortfolio(cov(log_returns))$w)
}