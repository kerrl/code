#! /usr/bin/env python3
# -*- coding:utf-8 -*-
# 求最大公约数
import time
def gcd(pair):
    a, b = pair
    low = min(a, b)
    for i in range(low, 0, -1):
        if a % i == 0 and b % i == 0:
            return i



numbers = [
    (1963309, 2265973), (1879675, 2493670), (2030677, 3814172),
    (1551645, 2229620), (1988912, 4736670), (2198964, 7876293)
]


start = time.time()
results = list(map(gcd, numbers))
print(results)
end = time.time()
 
print( 'Took %.3f seconds.' %(end - start))
