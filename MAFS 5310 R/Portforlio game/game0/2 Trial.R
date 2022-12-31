library(portfolioBacktest)
library(riskParityPortfolio)
library(CVXR)


#data("dataset10")
# load("~/Desktop/Working Space/HKUST-courses/MAFS 5310 Portfolio Optimization with R/Portforlio game/game0/stockdata_from_2008-12-01_to_2018-12-01.RData")

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

auxiliary_function <- function(X ,verbose = FALSE) {
    # here whatever code
    max_iter <- 100
    error_th_Sigma <- 1e-3
    
    #Gaussian initial point
    Sigma <- cov(X)  
    Sigma <- Sigma/sum(diag(Sigma))
    #loop
    obj_value_record <- Sigma_diff_record <- rep(NA, max_iter)
    for (k in 1:max_iter) {
        Sigma_prev <- Sigma
        N<-ncol(X)
        #Tyler update
        weights <- 1/rowSums(X * (X %*% solve(Sigma)))   # 1/diag( X %*% inv(Sigma) %*% t(X) )
        obj_value_record[k] <- - (N/2)*sum(log(weights)) + (T/2)*sum(log(eigen(Sigma)$values))
        Sigma <- (N/T) * crossprod( sqrt(weights)*X )  # (N/T) * t(X) %*% diag(weights) %*% X
        Sigma <- Sigma/sum(diag(Sigma))
        
        #stopping criterion
        Sigma_diff_record[k] <- norm(Sigma - Sigma_prev, "F")/norm(Sigma_prev, "F")
        if (Sigma_diff_record[k] < error_th_Sigma)
            break
    }
    obj_value_record <- obj_value_record[1:k]
    Sigma_diff_record <- Sigma_diff_record[1:k]
    if (verbose)
        plot(obj_value_record, type = "b", col = "blue",
             main = "Convergence of objective value", xlab = "iterations", ylab = "obj value")
    
    #finally, recover missing scaling factor
    sigma2 <- apply(X, 2, var)
    d <- diag(Sigma)
    kappa <- sum(sigma2*d)/sum(d*d)
    Sigma <- kappa*Sigma
    
    return(Sigma)
}

RPP_plus<- function(dataset, ...) {
    X <- diff(log(dataset$adjusted))[-1]
    X <- as.matrix(X)
    mu <- colMeans(X)
    #Sigma<-cov(X)
    Sigma<-auxiliary_function(X)
    rpp_mu <- riskParityPortfolio(Sigma, mu = mu, lmd_mu = 5e-6, formulation = "rc-double-index")
    return(as.vector(rpp_mu$w))
}

CVaR <- function(dataset, lmd = 0.5, alpha = 0.95) {
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


#############################################################################
###########################回测##############################################
#############################################################################

# portfolio_list
portfolio_list <- list(#"QuintP" = QuintP,
                       #"GMVP"   = GMVP,
                       #"MVP"    = MVP,
                       #"IVP"    = IVP,
                       #"MSRP"   = MSRP,
                       "RPP"    = RPP,
                       #"MDP"    = MDP,
                       #"MDCP"   = MDCP,
                       #"HOP"    = HOP,
                       #"RPP_plus" = RPP_plus,
                       "CVaR" = CVaR
)


# backtesting based on 100 datasets randomly chosen
bt <- portfolioBacktest(
    portfolio_funs = portfolio_list,
    dataset = mydataset,
    benchmark = c("1/N", "index"),
    shortselling = FALSE,
    leverage = 1,
    lookback = 200,
    optimize_every = 10,
    rebalance_every = 1,
    show_progress_bar = TRUE,
    # lookback = 252*2/3,
    # optimize_every = 20,
    # rebalance_every = 1,
    
    # paral_datasets = 5,
)




# leaderboard
leaderboard <- backtestLeaderboard(
    bt, 
    weights = list(
        "annual return"  = 2, 
        "VaR (0.95)"  = 1,
        "CVaR (0.95)" = 1,
        "max drawdown" = 1,
        "failure rate"  = 5)
)

# show leaderboard
library(gridExtra)
grid.table(leaderboard$leaderboard_scores)

# 查看全部数据的表现
#res_sum <- backtestSummary(bt)
#names(res_sum)
#res_sum$performance_summary
#
# leaderboard
# summaryTable(
#     res_sum,
#     type = "DT",
#     order_col = 2,
#     order_dir = "desc"
# )

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
