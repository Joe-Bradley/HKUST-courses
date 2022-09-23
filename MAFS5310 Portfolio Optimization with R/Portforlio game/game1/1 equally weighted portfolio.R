# Equally Weighted Portfolio
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

# 主函数
my_portfolio <- function(dataset, ...) {
    prices <- dataset$adjusted
    N <- ncol(prices)
    return(rep(1/N, N))
}

bt <- portfolioBacktest(my_portfolio, dataset10)
backtestSummary(bt)$performance

