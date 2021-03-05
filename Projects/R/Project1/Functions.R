### Praca projektowa nr 1 
### Rozwiązanie zadan
### Imie Nazwisko nr_indeksu kierunek (wybierz: MAT, MAD, IAD)

## ...---... Zadanie 01.01 ...---...

calka <- function(f, a, b, n = 100){
  stopifnot(length(a) == 1 & length(b) == 1 & is.numeric(a) & is.numeric(b))
  stopifnot(a < b)
  stopifnot(n > 0)
  stopifnot(n - as.integer(n) ==0 )
  h <- (b-a)/n
  podzial <- seq(a, b, by = h)
  wartosci <- unlist(lapply(podzial[2:n-1], f))
  h*((f(a) + f(b)) + sum(wartosci))
}

## ...---... Zadanie 01.02 ...---...

sklej <- function(x, sep = ""){
  stopifnot(is.list(x))
  stopifnot(min(unlist(lapply(x, length))) == max(unlist(lapply(x, length))))
  stopifnot(all(unlist(lapply(x, function(x) length(x) > 0))))
  stopifnot(lapply(x, function(x) is.character(x)))
  n <- length(x[[1]])
  div <- split(unlist(x), 1: n)
  napis <- lapply(div,function(a) paste(a, collapse = sep))
  unlist(napis)
}

## ...---... Zadanie 01.03 ...---...

repr_macierz <- function(x, eps = 1e-16){
  stopifnot(is.matrix(x))
  stopifnot(is.numeric(x))
  macierz <- which((x >= eps | x <= -eps), arr.ind = TRUE)
  macierz1 <- cbind(macierz, x[macierz])
  dimnames(macierz1) <- list(NULL, c("row","col", "val"))
  macierz1
}

## ...---... Zadanie 01.04 ...---...

logiderle <- function(i, j, n){
  stopifnot(length(i) == length(j) & length(i) > 1)
  stopifnot(n > 0)
  stopifnot(n - as.integer(n) ==0 )
  stopifnot(1 <= i & i <= j & j <= n)
  stopifnot(i[2:length(i)] > j[1:(length(j)-1)])
  w <- 1:n
  x <- rle(findInterval(w,i))
  z <- sort(ifelse(x[[2]] > 0, i, i <- c(min(i), i)))
  y <- sort(ifelse(x[[2]] > 0, j, j <- c(min(j), j)))
  vec1 <- rep(z, x[[1]])
  vec2 <- rep(y, x[[1]])
  ifelse((vec1 <= w & w <= vec2), TRUE, FALSE)
} 

