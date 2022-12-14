library(CVXR)
library(portfolioBacktest)

# load the embedded dataset
data("dataset10")

# show dataset class
class(dataset10) 
#> [1] "list"

# show names of a few datasets
names(dataset10[1:3])  
#> [1] "dataset 1" "dataset 2" "dataset 3"

# structure of one dataset
names(dataset10$`dataset 1`)  
#> [1] "adjusted" "index"

head(dataset10$`dataset 1`$adjusted[, 1:3]) 


###################Equally Weighted Portfolio################################
EWP_portfolio <- function(dataset, ...) {
    prices <- dataset$adjusted
    N <- ncol(prices)
    return(rep(1/N, N))
}
################### #mean-variance portfolio#################################
Markowitz_portfolio_fun <- function(dataset, ...) {
    
    # compute log returns
    X <- as.matrix(diff(log(dataset$adjusted))[-1])
    
    # compute mean vector
    mu <- colMeans(X)  
    
    # compute the SCM
    Sigma <- cov(X)
    
    # design mean-variance portfolio
    w <- Variable(nrow(Sigma))
    prob <- Problem(Maximize(t(mu) %*% w - 0.5*quad_form(w, Sigma)),
                    constraints = list(w >= 0, sum(w) == 1))
    
    result <- solve(prob)
    
    return(as.vector(result$getValue(w)))
}
#####################GMVP####################################################
GMVP_portfolio_fun <- function(dataset, ...) {
    
    # compute log returns
    X <- diff(log(dataset$adjusted))[-1]
    
    # compute SCM
    Sigma <- cov(X)  
    
    # design GMVP todo
    w <- solve(Sigma, rep(1, nrow(Sigma)))
    
    w <- abs(w)/sum(abs(w))
    
    return(w)
}
#####################quintile################################################
quintile_portfolio_fun <- function(dataset, ...) {
    
    # compute log returns
    X <- diff(log(dataset$adjusted))[-1]  
    
    # compute sigma
    N <- ncol(X)
    
    # design quintile portfolio
    ranking <- sort(
        colMeans(X), 
        decreasing = TRUE, 
        index.return = TRUE
    )$ix
    
    w <- rep(0, N)
    
    w[ranking[1:round(N/5)]] <- 1/round(N/5)
    
    return(w)
}


#####################backtest################################################
portfolios <- list(
    "Quintile" = quintile_portfolio_fun,
    "GMVP" = GMVP_portfolio_fun,
    "Markowitz" = Markowitz_portfolio_fun
)

bt <- portfolioBacktest(
    portfolios, 
    dataset10, 
    benchmark = c("IVP","1/N", "index")
)

names(bt)

# ?????????????????????????????????????????????
backtestSelector(
    bt,
    portfolio_name = "GMVP", 
    measures = c(
        "Sharpe ratio", 
        "max drawdown",
        "annual return",
        "annual volatility",
        "Sterling ratio", 
        "Omega ratio"
    )
)

# ????????????????????????????????????????????????
backtestTable(
    bt, 
    measures = c("Sharpe ratio", "max drawdown")
)

# ???????????????????????????
res_sum <- backtestSummary(bt)
names(res_sum)
res_sum$performance_summary

# ??????????????????????????????
summaryTable(
    res_sum,
    type = "DT", 
    order_col = "Sharpe ratio", 
    order_dir = "desc"
)

# ?????????
summaryBarPlot(
    res_sum, 
    measures = c("Sharpe ratio", "max drawdown")
)

# ?????????
backtestBoxPlot(
    bt, 
    measure = "Sharpe ratio"
)

# ?????????????????????
backtestChartCumReturn(
    bt, 
    c("Quintile", "GMVP", "index","1/N")
)

# ??????????????????????????????
dataset10_5stocks <- lapply(
    dataset10, 
    function(x) {
        x$adjusted <- x$adjusted[, 1:5]; 
        return(x)
    }
)
bt_5 <- portfolioBacktest(
    list("GMVP" = GMVP_portfolio_fun), 
    dataset10_5stocks, 
    rebalance_every = 20
)
backtestChartStackedBar(
    bt_5, 
    "GMVP", 
    legend = TRUE
)


###############################?????????########################################
# define a portfolio with parameters:
# "lookback", "quintile", and "average_type"
quintile_portfolio_fun <- function(dataset, ...) {
    
    prices <- tail(dataset$adjusted, lookback)
    
    X <- diff(log(prices))[-1]
    
    mu <- switch(
        average_type,
        "mean" = colMeans(X),
        "median" = apply(X, MARGIN = 2, FUN = median)
    )
    
    idx <- sort(
        mu, 
        decreasing = TRUE, 
        index.return = TRUE
    )$ix
    
    w <- rep(0, ncol(X))
    
    w[idx[1:ceiling(quintile*ncol(X))]] <- 1/ceiling(quintile*ncol(X))
    
    return(w)
}

# ????????????:lookback,quintile,average_type,???????????????40???
portfolio_list <- genRandomFuns(
    portfolio_fun = quintile_portfolio_fun, 
    params_grid = list(
        lookback = c(100, 120, 140, 160),
        quintile = 1:5 / 10,
        average_type = c("mean", "median")
    ),
    name = "Quintile",
    N_funs = 40
)

# ????????????
names(portfolio_list[1:5])
# ?????????????????????
portfolio_list[[1]]
# ??????40?????????
bt <- portfolioBacktest(
    portfolio_list, 
    dataset10
)
# ????????????
plotPerformanceVsParams(bt)


##################################????????????###################################
# ??????????????????
portfun <- Markowitz_portfolio_fun
system.time(
    bt_parallel_funs <- portfolioBacktest(
        list(portfun, portfun), 
        dataset10,
        #paral_portfolios = 2
    )
)

# ???????????????
system.time(
    bt_parallel_funs <- portfolioBacktest(
        portfun, 
        dataset10,
        #paral_portfolios = 5
    )
)

################################??????error####################################

# ????????????????????????
sub_function2 <- function(x) {
    "a" + x  # an error will happen here
}
sub_function1 <- function(x) {
    return(sub_function2(x))
}

# ?????????bug?????????
wrong_portfolio_fun <- function(data, ...) {
    N <- ncol(data$adjusted)
    uni_port <- rep(1/N, N)
    return(sub_function1(uni_port))
}

bt <- portfolioBacktest(wrong_portfolio_fun, dataset10)
res <- backtestSelector(bt, portfolio_index = 1)
error1 <- res$error_message[[1]]
str(error1)
# the exact location of error happening
cat(attr(error1, "error_stack")$at)
# the call stack of error happening
cat(attr(error1, "error_stack")$stack)
#> sub_function1(uni_port)
#> sub_function2(x)


# ????????????
library(gridExtra)
leaderboard <- backtestLeaderboard(
    bt_all_students, 
    weights = list("Sharpe ratio"  = 7, 
    "max drawdown"  = 1, 
    "annual return" = 1, 
    "ROT (bps)"     = 1)
)
grid.table(leaderboard$leaderboard_scores)
