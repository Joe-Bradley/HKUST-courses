# prepare data
suppressPackageStartupMessages(library(quantmod))

options(digits=10)

# APPLE: 20220601-20221125
AAPL <- getSymbols("AAPL",auto.assign = FALSE, from= Sys.Date()-360*3)
logprices <- log(AAPL$AAPL.Close)
x <- diff(logprices)[-1]
T <- nrow(x)
T_trn <- round(0.7*T)
T_tst <- T - T_trn
x_trn <- x[1:T_trn]
x_tst <- x[-c(1:T_trn)]

# see pictures of volatility simulation
library(RcppRoll)
library(fGarch)
library(stochvol)
library(rugarch)
library(forecast)

lookback_var <- 20
var_t <- roll_meanr(x_trn^2, n = lookback_var, fill = NA)

fit_ets <- ets(x_trn^2, model = "ANN")
std_t_EWMA <- as.numeric(sqrt(fit_ets$fitted))

garch_fit <- fGarch::garchFit(formula = ~ garch(1,1), x_trn, trace = FALSE)
std_t_GARCH <- garch_fit@sigma.t


res <- svsample(x_trn - mean(x_trn), priormu = c(0, 100), priornu = 0)
std_t_SV <- res$summary$sd[, 1]
plot(cbind(std_t, x_trn), col = c("red", "black"), lwd = c(2.5, 1.5),
     main = "Envelope based on stochastic volatility")

plot(cbind(sqrt(var_t), std_t_EWMA,std_t_GARCH,std_t_SV,x_trn), col = c("red","blue","green","purple","black"), lwd = c(0.75,0.75,0.75,0.75,0.75),
     main = "different volatilities models")

# calcualte the call option price
# 3month-call option on apple with: K = 120, S = 148.11, R = 0.0421, T = 0.25, Q = 0.0061, C = 31.35, Implied = 0.4974 

# define BSM funcitons
callbs <- function(S, K, R, T, sig, q=0) {
    d1 <- (log(S/K) + (R +q+ sig^2/2)*T) / (sig*sqrt(T))
    d2 <- d1 - sig*sqrt(T)
    c <- S*exp(-q*T)*pnorm(d1) - K*exp(-R*T)*pnorm(d2)
    if(c>=0){return(c)}
    else{return(0)}
}
put_bs <- function(S, K, R, T, sig, q=0) {
    d1 <- (log(S/K) + (R + q+ sig^2/2)*T) / (sig*sqrt(T))
    d2 <- d1 - sig*sqrt(T)
    p <- K*exp(-R*T)*pnorm(-d2)-S*exp(-q*T)*pnorm(-d1)
    if(p>=0){return(p)}
    else{return(0)}
}

# BSM using standard deviation
AAPL <- getSymbols("AAPL",auto.assign = FALSE, from= Sys.Date()-360)
ret <- diff(log(AAPL$AAPL.Close))[-1]
ret[1] <- 0
vol <- sd(ret)
vol <- vol*sqrt(0.25)
callbs(148.11, 120, 0.0061, 0.25, vol, 0.0421)
callbs(148.11, 270, 0.0061, 0.25, vol, 0.0421)

#BSM using EWMA
library(quarks)
cvar <- ewma(x = ret, lambda = 0.95)
EWMA_sigma <- sqrt(cvar)
callbs(148.11, 120, 0.0061, 0.25, tail(EWMA_sigma,n=1)*sqrt(90), 0.0421)
callbs(148.11, 170, 0.0061, 0.25, tail(EWMA_sigma,n=1)*sqrt(90), 0.0421)


# BSM using GARCH(1,1)
garch_fit <- fGarch::garchFit(formula = ~ garch(1,1), ret, trace = FALSE)
std_t_GARCH_ret <- garch_fit@sigma.t
callbs(148.11, 120, 0.0061, 0.25, tail(std_t_GARCH_ret,n=1)*sqrt(90), 0.0421)
callbs(148.11, 170, 0.0061, 0.25, tail(std_t_GARCH_ret,n=1)*sqrt(90), 0.0421)

# BSM using SV
target <- 31.35
v0 = 0.2
vT = 0.2
rho= 0.5
k= 0.2
sig= 0.05

library(NMOF)
x <- c(v0,vT,rho,k,sig)
optim_func <- function(x){
    v0= x[1]
    vT= x[2]
    rho= x[3]
    k= x[4]
    sig= x[5]
    mse <- (callHestoncf(148.11,120,0.25, 0.0061,0.0421, v0, vT, rho,k,sig)-target)^2
    return(mse)
}

optim(x, optim_func)

mat <- matrix(nrow=5, ncol=3)
mat[1,] <- c("v0","current variance",0.288170718835)
mat[2,] <- c("vT", "long-run variance", 0.238908182371)
mat[3,] <- c("rho","correlation between spot and variance", 0.473721668267)
mat[4,] <- c("k","speed of mean-reversion", 0.193409543295)
mat[5,] <- c("sigma", "volatility of variance", -0.001137251094)
df <- as.data.frame(mat)
colnames(df) <- c("Parameters","Meaning","Value")
print(df)

callHestoncf(148.11,120,0.25, 0.0061,0.0421,0.288170718835, 0.238908182371, 0.473721668267,0.193409543295,-0.001137251094)



###########
############ BSM using SV
target <- 2.19
v0 = 0.2
vT = 0.2
rho= 0.5
k= 0.2
sig= 0.05

library(NMOF)
x <- c(v0,vT,rho,k,sig)
optim_func <- function(x){
    v0= x[1]
    vT= x[2]
    rho= x[3]
    k= x[4]
    sig= x[5]
    mse <- (callHestoncf(148.11,170,0.25, 0.0061,0.0421, v0, vT, rho,k,sig)-target)^2
    return(mse)
}

optim(x, optim_func)

mat <- matrix(nrow=5, ncol=3)
mat[1,] <- c("v0","current variance",0.08781913913)
mat[2,] <- c("vT", "long-run variance", 0.21874562087)
mat[3,] <- c("rho","correlation between spot and variance", 0.53445073867)
mat[4,] <- c("k","speed of mean-reversion", 0.26839511941)
mat[5,] <- c("sigma", "volatility of variance", 0.05647784644)
df <- as.data.frame(mat)
colnames(df) <- c("Parameters","Meaning","Value")
print(df)
callHestoncf(148.11,170,0.25, 0.0061,0.0421,0.08781913913, 0.21874562087, 0.53445073867,0.26839511941,0.05647784644)

########################
mat <- matrix(nrow=2, ncol=6)
mat[1,] <- c("In-the-Money",26.74217757,27.1084363, 26.91855601, 30.34989122,31.35)
mat[2,] <- c("Out-of--Money", 0,1.129831294, 0.6713966474, 2.089795823,2.19)
df <- as.data.frame(mat)
colnames(df) <- c(" ","BSM_SD","BSM_EWMA","BSM_GARCH", "BSM_SV","Actual")
print(df)




