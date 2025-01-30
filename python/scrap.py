from math import comb

def d(n):
    if n == 0:
        return 1
    else:
        return sum([comb(n-1,k)*d(k) for k in range(n)])

print(d(4))
print(d(15))