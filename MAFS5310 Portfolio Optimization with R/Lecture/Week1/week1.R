x <- "Hello"
y <- c("Hello", "everyone")
z <- c(1:1000)
ls()
str(z)
head(z)
tail(z)
help(matrix)
example(matrix) 
apropos("matrix")
vignette()
vignette("xts")
a <- c(1, 2, 5.3, 6, -2, 4)  # numeric vector
b <- c("one", "two", "three")  # character vector
c <- c(TRUE, TRUE, TRUE, FALSE, TRUE, FALSE) # logical vector
x <- c(1, 2)
y <- c(10, 20)
x * y 
#> [1] 10 40
x %*% y
#>      [,1]
#> [1,]   50
t(x) %*% y
#>      [,1]
#> [1,]   50
x %o% y
#>      [,1] [,2]
#> [1,]   10   20
#> [2,]   20   40

names(y)
names(y) <- c("convex", "optimization")
x <- matrix(1:20, nrow = 5, ncol = 4)
colnames(x) <- c("col1", "col2", "col3", "col4")
rownames(x) <- c("row1", "row2", "row3", "row4", "row5")
str(x)
dim(x)
nrow(x)
ncol(x)

x[, 4]
str(x[, 4])
x[, 4, drop = FALSE]
str(x[, 4, drop = FALSE])
x[3, ]
x[2:4, 1:3]
str(x[2:4, 1:3])

d <- c(1, 2, 3, 4)
e <- c("red", "white", "red", NA)
f <- c(TRUE, TRUE, TRUE, FALSE)
myframe <- data.frame(d, e, f)
names(myframe) <- c("ID", "Color", "Passed")
myframe
str(myframe)

myframe[c(1, 3)]
myframe[c("ID", "Color")]
myframe["ID"]
myframe$ID

w <- list(name = "Fred", mynumbers = c(1:10), mymatrix = matrix(NA, 3, 3), age = 5.3)

ength(object) # number of elements or components of a vector
str(object) # structure of an object 
class(object) # class or type of an object
names(object) # names
c(object, object, ...) # combine objects into a vector
cbind(object, object, ...) # combine objects as columns
rbind(object, object, ...) # combine objects as rows 
object # prints the object
print(object) # prints the object
ls() # list current objects
rm(object) # delete an object

x <- rnorm(1000)  # generate normal random numbers
x <- cumsum(x)    # random walk
plot(x, type = "l", col = "blue", main = "Random walk", xlab = "time", ylab = "log-price")
lines(cumsum(rnorm(1000)), col = "red")

par(mfrow = c(2, 2))  # define a 2x2 matrix of plots
plot(cumsum(rnorm(1000)), type = "l", ylab = "x1")
plot(cumsum(rnorm(1000)), type = "l", ylab = "x2")
plot(cumsum(rnorm(1000)), type = "l", ylab = "x3")
plot(cumsum(rnorm(1000)), type = "l", ylab = "x4")
par(mfrow = c(1, 1))  # set it to default single plot



############################################################
library(ggplot2)   # install.packages("ggplot2")
library(reshape2)  # required for melting the data frame

# create data frame with data
df <- data.frame(index   = 1:1000,
                 series1 = cumsum(rnorm(1000)),
                 series2 = cumsum(rnorm(1000)),
                 series3 = cumsum(rnorm(1000)),
                 series4 = cumsum(rnorm(1000)))
molten_df <- melt(df, id.vars = "index", measure.vars = c("series1", "series2", "series3", "series4"))
str(molten_df)
#> 'data.frame':    4000 obs. of  3 variables:
#>  $ index   : int  1 2 3 4 5 6 7 8 9 10 ...
#>  $ variable: Factor w/ 4 levels "series1","series2",..: 1 1 1 1 1 1 1 1 1 1 ...
#>  $ value   : num  1.646 0.309 0.775 1.526 3.11 ...

# plot
ggplot(molten_df, aes(x = index, y = value, col = variable)) + 
    geom_line() +
    ggtitle("Random walks")

