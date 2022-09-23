library(CVXR)

# define quintile portfolio
quintile_portfolio_fun <- function(dataset, w_current) {
    X <- diff(log(dataset$adjusted))[-1]  # compute log returns
    N <- ncol(X)
    # design quintile portfolio
    ranking <- sort(colMeans(X), decreasing = TRUE, index.return = TRUE)$ix
    w <- rep(0, N)
    w[ranking[1:round(N/5)]] <- 1/round(N/5)
    return(w)
}

# define GMVP (with heuristic not to allow shorting)
GMVP_portfolio_fun <- function(dataset, ...) {
    X <- diff(log(dataset$adjusted))[-1]  # compute log returns
    Sigma <- cov(X)  # compute SCM
    # design GMVP
    w <- solve(Sigma, rep(1, nrow(Sigma)))
    w <- abs(w)/sum(abs(w))
    return(w)
}

# define Markowitz mean-variance portfolio
Markowitz_portfolio_fun <- function(dataset, ...) {
    X <- diff(log(dataset$adjusted))[-1]  # compute log returns
    mu    <- colMeans(X)  # compute mean vector
    Sigma <- cov(X)       # compute the SCM
    # design mean-variance portfolio
    w <- Variable(nrow(Sigma))
    prob <- Problem(Maximize(t(mu) %*% w - 0.5*quad_form(w, Sigma)),
                    constraints = list(w >= 0, sum(w) == 1))
    result <- solve(prob)
    return(as.vector(result$getValue(w)))
}


portfolios <- list("Quintile"  = quintile_portfolio_fun,
                   "GMVP"      = GMVP_portfolio_fun,
                   "Markowitz" = Markowitz_portfolio_fun)
bt <- portfolioBacktest(portfolios, dataset10, benchmark = c("1/N", "index"))

backtestSelector(bt, portfolio_name = "Quintile", 
                 measures = c("Sharpe ratio", "max drawdown"))
backtestTable(bt, measures = c("Sharpe ratio", "max drawdown"))
res_sum <- backtestSummary(bt)
names(res_sum)
res_sum$performance_summary 

# ploting summary
summaryTable(res_sum, type = "DT", order_col = "Sharpe ratio", order_dir = "desc")

# barplot
summaryBarPlot(res_sum, measures = c("Sharpe ratio", "max drawdown"))

# boxplot
backtestBoxPlot(bt, measure = "Sharpe ratio")

# cumulative return
backtestChartCumReturn(bt, c("Quintile", "GMVP", "index"))
backtestChartDrawdown(bt, c("Quintile", "GMVP", "index"))





