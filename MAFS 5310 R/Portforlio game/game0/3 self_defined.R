library(riskParityPortfolio)
library(portfolioBacktest)
library(riskParityPortfolio)
library(CVXR)
data("dataset10")



portolioCVaR <- function(dataset, lmd = 0.5, alpha = 0.95) {
    prices <- dataset$adjusted
    X <- diff(log(prices))[-1] 
    T <- nrow(X)
    N <- ncol(X)
    X <- as.matrix(X)
    mu <- colMeans(X)
    
    # variables
    w <- Variable(N)
    z <- Variable(T)
    zeta <- Variable(1)
    
    # problem
    prob <- Problem(
        Maximize(t(w) %*% mu - lmd*zeta - (lmd/(T*(1-alpha))) * sum(z)),
        constraints = list(z >= 0, 
                           z >= -X %*% w - zeta,
                           w >= 0, 
                           sum(w) == 1)
    )
    result <- solve(prob)
    return(as.vector(result$getValue(w)))
}

# MVP
MVP <- function(dataset, ...) {
    prices <- dataset$adjusted
    N <- ncol(prices)
    X <- diff(log(prices))[-1]  # returns
    mu <- colMeans(X)
    Sigma <- cov(X)
    
    # portfolio design
    lmd = 0.5
    w <- Variable(N)
    prob <- Problem(Maximize(t(mu) %*% w - lmd*quad_form(w, Sigma)),
                    constraints = list(sum(w) == 1, w >= 0))
    result <- solve(prob)
    return(as.vector(result$getValue(w)))
}

b = portolioCVaR(dataset10$`dataset 10`, lmd = 0.5, alpha = 0.95)
a = MVP(dataset10$`dataset 1`)


# portfolio_list
portfolio_list <- list("portolioCVaR" = portolioCVaR)


# backtesting based on 100 datasets randomly chosen
bt <- portfolioBacktest(
    portfolio_funs = portfolio_list,
    dataset = dataset10,
    benchmark = c("1/N", "index"),
    #shortselling = FALSE,
    # leverage = 1,
    # lookback = 100,
    # optimize_every = 10,
    # rebalance_every = 1,
    show_progress_bar = TRUE,
    # lookback = 252*2/3,
    # optimize_every = 20,
    # rebalance_every = 1,
    # paral_datasets = 5,
)

# 查看全部数据的表现
res_sum <- backtestSummary(bt)
names(res_sum)
res_sum$performance_summary

# leaderboard
leaderboard <- backtestLeaderboard(
    bt, 
    weights = list(
        "annual return"  = 1, 
        "annual volatility"  = 1,
        "Sharpe ratio" = 1,
        "max drawdown" = 1,
        "failure rate"  = 6)
)

# show leaderboard
library(gridExtra)
grid.table(leaderboard$leaderboard_scores)