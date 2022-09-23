library(portfolioBacktest)

# load the SP500 symbols
data(SP500_symbols)

# download data from internet
SP500 <- stockDataDownload(stock_symbols = SP500_symbols, 
                           from = "2008-12-01", to = "2018-12-01")

# resample 10 times from SP500, each with 50 stocks and 2-year consecutive data
my_dataset_list <- financialDataResample(SP500, 
                                         N_sample = 50, T_sample = 252*2, 
                                         num_datasets = 10)

# Each individual dataset will contain 7 xts objects with names: open, high, low, close, volume, adjusted, index

# Expanding the datasets
for (i in 1:length(dataset10))
    dataset10[[i]]$MACD <- apply(dataset10[[i]]$adjusted, 2, 
                                 function(x) { TTR::MACD(x)[ , "macd"] })





