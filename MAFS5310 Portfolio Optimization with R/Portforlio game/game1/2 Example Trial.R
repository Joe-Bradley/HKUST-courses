library(portfolioBacktest)
library(CVXR)

# load the SP500 assets
data("SP500_symbols")
SP500_YAHOO <- stockDataDownload(
    stock_symbols = SP500_symbols, 
    from = "2010-12-01", 
    to = "2018-12-01"
)

# generate 100 random samples each containing 50 random assets over a random window of two years
N_datasets <- 100
mydataset <- financialDataResample(
    SP500_YAHOO, 
    N = 50, 
    T = 252*2, 
    num_datasets = N_datasets
)

# define strategy
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



portfolio_list <- list("QuintP" = QuintP,
                       "GMVP"   = GMVP,
                       "MVP"    = MVP)

# backtesting based on 100 datasets randomly chosen
bt_all_port <- portfolioBacktest(
    portfolio_funs = portfolio_list,
    dataset = mydataset,
    benchmark = c("IVP","uniform", "index"),
    lookback = 252*2/3, 
    optimize_every = 20, 
    rebalance_every = 1, 
    show_progress_bar = FALSE,
    paral_datasets = 5
)

res_summary_median <- backtestSummary(bt_all_port)

# leaderboard
summaryTable(
    res_summary_median, 
    type = "DT", 
    order_col = 2, 
    order_dir = "desc"
)

# bar plot
summaryBarPlot(
    res_summary_median, 
    measures = c("Sharpe ratio", "max drawdown")
)

# box plot
backtestBoxPlot(
    bt_all_port, 
    "Sharpe ratio"
)