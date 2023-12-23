import sys
sys.stdin = open("input.txt","r")
sys.stdout = open("output.txt","w")

# GMAIL_PASS hlkhefiimhwoqsvk

t = int(input())
for _ in range(t):
    pass

import random
from math import gcd

def millerTest(d, n):
    a = 2 + random.randint(1,n-4)
    x = pow(a,d,n)
    if x == 1 or x == n-1: return True
    while d != n-1:
        x = x*x%n
        d *= 2;
        if x == 1: return False
        if x == n-1: return True
    return False

def isPrime(n,k):
    if n <= 1 or n == 4: return False
    if n <= 3: return True
    d = n-1
    while d%2 == 0: 
      d //= 2
    for i in range(k):
        if not millerTest(d,n):
            return False
    return True

def pollardRho(n):
    if n%2 == 0: return 2
    if isPrime(n,50): return n
    while True:
        c = random.randint(2,n-1)
        f = lambda x: (x**2+c)%n
        x = y = 2 
        d = 1 
        while d == 1:
            x = f(x) 
            y = f(f(y))
            d = gcd(abs(x-y),n)
        if d != n: return d

n = int(input())
mp,w = [],n
for i in range(2,10**4):
    if n%i == 0:
        mp.append(i)
        while n % i == 0: 
            n //= i
            
while n > 2:
    d = pollardRho(n)
    if len(mp) == 0 or mp[-1] != d: mp.append(d)
    n //= d
    
s = 1
mp.sort()
for j in mp:
    while w%j == 0:
        print(w,'|',j,sep='')
        w //= j
print("1|")