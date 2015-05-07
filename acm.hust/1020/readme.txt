a[1]=1;
a[i*2]=a[i];
a[i*2+1]=a[i]+a[i+1];

fib array.
2 3
3 5
5 11
8 21
13 43
21 85
the max number when i less than 85 must less than 21

may be useful information.
the max number of next n level between a and b is 
max{F[n]*a+F[n-1]*b, F[n-1]*a+F[n]*b}
F is fib array and F[0]=F[1]=1

search and depth control?
