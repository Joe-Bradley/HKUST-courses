library(portfolioBacktest)
library(riskParityPortfolio)
library(CVXR)
#data("dataset10")
load("MAFS5310 Portfolio Optimization with R/Portforlio game/game0/stockdata_from_2008-12-01_to_2018-12-01.RData")

# show dataset class
# class(dataset10)

# show names of a few datasets
# names(dataset10[1:3])

# structure of one dataset
# names(dataset10$`dataset 1`)

# head(dataset10$`dataset 1`$adjusted[, 1:3])

# download the SP500 assets
# data("SP500_symbols")
# SP500_YAHOO <- stockDataDownload(
#     stock_symbols = SP500_symbols, 
#     from = "2010-12-01", 
#     to = "2018-12-01"
# )

#generate 100 random samples each containing 50 random assets over a random window of two years
N_datasets <- 10
#N_datasets <- 100
mydataset <- financialDataResample(
    stockdata,
    N = 50,
    T = 252*2,
    num_datasets = N_datasets
)
Markowitz_portfolio_fun <- function(dataset, ...) {
    X <- as.matrix(diff(log(dataset$adjusted))[-1])
    mu <- colMeans(X)  
    Sigma <- cov(X)
    w <- Variable(nrow(Sigma))
    prob <- Problem(
        Maximize(t(mu) %*% w - lambda*quad_form(w, Sigma)),
        constraints = list(w >= 0, sum(w) == 1)
    )
    result <- solve(prob)
    return(as.vector(result$getValue(w)))
}

portfolio_list <- genRandomFuns(
    portfolio_fun = Markowitz_portfolio_fun, 
    params_grid = list(lambda = c(0,10^-4,2*10^-4,3*10^-4,4*10^-4,5*10^-4,6*10^-4,7*10^-4,8*10^-4,9*10^-4,10^-3)
),
    name = "Quintile",
    N_funs = 11
)

bt1 <- portfolioBacktest(
    portfolio_list, 
    mydataset
)

# leaderboard2
leaderboard2 <- backtestLeaderboard(
    bt1, 
    weights = list(
        "Sharpe ratio"  = 1.5, 
        "max drawdown"  = 1.5, 
        "failure rate"  = 7)
)

plotPerformanceVsParams(bt1)

# show leaderboard
library(gridExtra)
grid.table(leaderboard2$leaderboard_scores)


