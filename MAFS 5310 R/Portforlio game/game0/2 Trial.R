library(portfolioBacktest)
library(riskParityPortfolio)
library(CVXR)


#data("dataset10")
load("~/Desktop/Working Space/HKUST-courses/MAFS 5310 Portfolio Optimization with R/Portforlio game/game0/stockdata_from_2008-12-01_to_2018-12-01.RData")

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


#############################################################################
#######################define strategy#######################################
#############################################################################
QuintP <- function(dataset, ...) {
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

IVP <- function(dataset, ...) {
    prices <- dataset$adjusted
    N <- ncol(prices)
    X <- diff(log(prices))[-1]  # returns
    Sigma <- cov(X)
    
    # portfolio design
    sigma <- sqrt(diag(Sigma))
    w <- 1/sigma
    w <- w/sum(w)
    return(w)
}

GMVP <- function(dataset, ...) {
    prices <- dataset$adjusted
    N <- ncol(prices)
    X <- diff(log(prices))[-1]  # returns
    Sigma <- cov(X)
    
    # portfolio design
    w <- Variable(N)
    prob <- Problem(Minimize(quad_form(w, Sigma)),
                    constraints = list(sum(w) == 1, w >= 0))
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

# MSRP
MSRP <- function(dataset, ...) {
    prices <- dataset$adjusted
    X <- diff(log(prices))[-1]  # returns
    mu <- colMeans(X)
    Sigma <- cov(X)
    
    w_ <- Variable(nrow(Sigma))
    prob <- Problem(Minimize(quad_form(w_, Sigma)),
                    constraints = list(w_ >= 0, t(mu) %*% w_ == 1))
    result <- CVXR::solve(prob)
    w <- as.vector(result$getValue(w_)/sum(result$getValue(w_)))
    names(w) <- colnames(Sigma)
    return(w)
}

# Most diversified portfolio (MDP)
MDP <- function(dataset, ...) {
    prices <- dataset$adjusted
    X <- diff(log(prices))[-1]  # returns
    Sigma <- cov(X)
    mu <- sqrt(diag(Sigma))
    
    w_ <- Variable(nrow(Sigma))
    prob <- Problem(Minimize(quad_form(w_, Sigma)),
                    constraints = list(w_ >= 0, t(mu) %*% w_ == 1))
    result <- CVXR::solve(prob)
    w <- as.vector(result$getValue(w_)/sum(result$getValue(w_)))
    names(w) <- colnames(Sigma)
    return(w)
}

# RPP 
RPP <- function(dataset, ...) {
    prices <- dataset$adjusted
    log_returns <- diff(log(prices))[-1]
    return(riskParityPortfolio(cov(log_returns))$w)
}

MDCP <- function(dataset) {
    prices <- dataset$adjusted
    X <- diff(log(prices))[-1]  # returns
    Sigma <- cov(X)
    C <- diag(1/sqrt(diag(Sigma))) %*% Sigma %*% diag(1/sqrt(diag(Sigma)))
    colnames(C) <- colnames(Sigma)
    return(GMVP(Sigma = C))
}

HOP<- function(dataset,...){
    C <- dataset$adjusted
    X <- diff(log(C))[-1]
    N <- ncol(C)
    # estimate parameters
    X_skew_t_params <- estimate_skew_t(X)
    xi <- 10
    lmd <- c(1, xi/2, xi*(xi+1)/6, xi*(xi+1)*(xi+2)/24)
    # portfolio optimization
    sol <- design_MVSK_portfolio_via_skew_t(lmd, X_skew_t_params)
    w = sol$w
    return(w)
}


#############################################################################
###########################回测##############################################
#############################################################################

# portfolio_list
portfolio_list <- list("QuintP" = QuintP,
                       "GMVP"   = GMVP,
                       "MVP"    = MVP,
                       "IVP"    = IVP,
                       "MSRP"   = MSRP,
                       "RPP"    = RPP,
                       "MDP"    = MDP,
                       "MDCP"   = MDCP,
                       "HOP"    = HOP
)


# backtesting based on 100 datasets randomly chosen
bt <- portfolioBacktest(
    portfolio_funs = portfolio_list,
    dataset = mydataset,
    benchmark = c("1/N", "index"),
    shortselling = FALSE,
    leverage = 1,
    lookback = 100,
    optimize_every = 10,
    rebalance_every = 1,
    show_progress_bar = TRUE,
    # lookback = 252*2/3,
    # optimize_every = 20,
    # rebalance_every = 1,
    
    # paral_datasets = 5,
)

# 查看全部数据的表现
#res_sum <- backtestSummary(bt)
#names(res_sum)
#res_sum$performance_summary

# # leaderboard
# summaryTable(
#     res_sum, 
#     type = "DT",    
#     order_col = 2, 
#     order_dir = "desc"
# )

# leaderboard2
leaderboard2 <- backtestLeaderboard(
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
grid.table(leaderboard2$leaderboard_scores)

# # bar plot
# summaryBarPlot(
#     res_sum, 
#     measures = c("Sharpe ratio", "max drawdown")
# )
# 
# # box plot
# backtestBoxPlot(
#     bt, 
#     "Sharpe ratio"
# )
# 
# # 查看某个组合在某个数据集的表现
# backtestSelector(
#     bt,
#     portfolio_name = "GMVP", 
#     measures = c(
#         "Sharpe ratio", 
#         "max drawdown",
#         "annual return",
#         "annual volatility",
#         "Sterling ratio", 
#         "Omega ratio"
#     )
# )
# 
# # 查看全部的组合在某个数据集的表现
# backtestTable(
#     bt, 
#     measures = c("Sharpe ratio", "max drawdown")
# )
# 
# # 全部数据的表现的画图
# summaryTable(
#     res_sum,
#     type = "DT", 
#     order_col = "Sharpe ratio", 
#     order_dir = "desc"
# )
# 
# # 柱状图
# summaryBarPlot(
#     res_sum, 
#     measures = c("Sharpe ratio", "max drawdown")
# )
# 
# # 箱形图
# backtestBoxPlot(
#     bt, 
#     measure = "Sharpe ratio"
# )
# 
# # 累计收益分布图
# backtestChartCumReturn(
#     bt, 
#     c("Quintile", "GMVP", "index","1/N")
# )
