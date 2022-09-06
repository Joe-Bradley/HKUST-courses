library(xts)
x <- "hello"

# 查看变量信息
x <- c(1:1000)
str(x)
length(x)
head(x)
tail(x)
example(matrix)

a <- c(1, 2, 5.3, 6, -2, 4)  # numeric vector
b <- c("one", "two", "three")  # character vector
c <- c(TRUE, TRUE, TRUE, FALSE, TRUE, FALSE) # logical vector

x <- c(1, 2)
y <- c(10, 20)
z1 <- x * y
z2 <- x %*% y
z3 <- t(x) %*% y
z4 <- x %o% y


names(y) <- c("convex", "optimization")
x <- matrix(1:20, nrow = 5, ncol = 4)

x[, 4]
x[, 4, drop = FALSE]
x[3, ]
x[2:4, 1:3]
str(x[2:4, 1:3])

d <- c(1, 2, 3, 4)
e <- c("red", "white", "red", NA) # not available
f <- c(TRUE, TRUE, TRUE, FALSE)
myframe <- data.frame(d, e, f)
names(myframe) <- c("ID", "Color", "Passed")
str(myframe)

w <- list(name = "Fred", mynumbers = c(1:10), mymatrix = matrix(NA, 3, 3), age = 5.3)

# plot
x <- rnorm(1000)  # generate normal random numbers
x <- cumsum(x)    # random walk
plot(x, type = "l", col = "blue", main = "Random walk", xlab = "time", ylab = "log-price")
lines(cumsum(rnorm(1000)), col = "red")



