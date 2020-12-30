
#! /usr/bin/env python3
# -*- coding:utf-8 -*-
# 求最大公约数
import time
from concurrent.futures import ThreadPoolExecutor, ProcessPoolExecutor, Executor

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
# 采用进程池，由于python
start = time.time()
# 创建一个进程池，四核
with ProcessPoolExecutor(max_workers=4) as pool:
# pool.map()线程池执行gcd(numbers)
    results = list(pool.map(gcd, numbers))
    print(results)
    end = time.time()
    print( 'Took %.3f seconds.' %(end - start) )
