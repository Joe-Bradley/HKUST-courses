library(xts)  # to manipulate time series of stock data
library(quantmod)  # to download stock data
library(PerformanceAnalytics)  # to compute performance measures

# download data from YahooFinance
stock_namelist <- c("AAPL", "AMD", "ADI",  "ABBV", "AEZS", "A",  "APD", "AA","CF")
prices <- xts()
for (i in 1:length(stock_namelist)) {
    #adjust price
    tmp <- Ad(getSymbols(stock_namelist[i], from = "2013-01-01", to = "2016-12-31", auto.assign = FALSE))
    tmp <- na.approx(tmp, na.rm = FALSE)  # interpolate NAs
    prices <- cbind(prices, tmp)
}
colnames(prices) <- stock_namelist
tclass(prices) <- "Date"

# see data
str(prices)
head(prices)
tail(prices)

# compute log-returns and linear returns
X_log <- diff(log(prices))[-1]
X_lin <- (prices/lag(prices) - 1)[-1]

# or alternatively...
X_log <- CalculateReturns(prices, "log")[-1]
X_lin <- CalculateReturns(prices)[-1]

N <- ncol(X_log)  # number of stocks
T <- nrow(X_log)  # number of days

plot(prices/rep(prices[1, ], each = nrow(prices)), col = rainbow10equal, legend.loc = "topleft",
     main = "Normalized prices")

# We now divide the data into a training set and test set
T_trn <- round(0.7*T)  # 70% of data
X_log_trn <- X_log[1:T_trn, ]
X_log_tst <- X_log[(T_trn+1):T, ]
X_lin_trn <- X_lin[1:T_trn, ]
X_lin_tst <- X_lin[(T_trn+1):T, ]

