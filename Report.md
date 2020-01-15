# Cache Optimizations

#### 04.12.

## ─

### Ali Abu Saleh

#### Architecture II - HM

#### Computer Engineering

#### 9:00 - 11:


## Overview

Matrix multiplication is one of the most important modern computational kernels. In this
homework we will try to optimize this computation using the memory/cache optimization
techniques we learnt in class, using 3 methods, the first one using the interchange
optimization, the second one is blocking optimization, and the final one is using both.

## Goals

1. Implement the interchange optimization.
2. Implement the blocking optimization.
3. Implement both of the previous optimizations at the same time.

## Interchange Optimization

```
In tha main Matrix multiplication we will access the array column by column but the
array saved in the memory sequentially, we we will go row by row to increase the
spatial locality ( Sequential accesses instead of striding through).
```

The code as follows
Note I used a function to initialize the output array by clearing it.

## Blocking Optimization

To increase the temporal locality we have to decrease the time when the array will
re-read the same index, in this optimization I will divide the array into smaller ones
then find the output for each one, as follows,
The first 3 loops for the block that I want to find the result for it.
Note: Size and block_size is are defined as following
, the inner 3 loops for normal matrix multiplication.


## Blocking & Interchanging Optimization

In this optimization, we will merge the previous techniques to increase both
temporal and spatial locality, as follows,
Note: I used the provided function ( Verification ) to check the output of the mentioned
optimizations, the code was as follows,


## Timing

The cache optimization has a massive better performance on the timing for the running
time,
Note: in some cases the CPU gets higher time due to inner change of processes, so I run
the code for 10 times then take the average.
For Size of 512*512 and block size 64 the output as following
For Size of 512*512 and block size 32 the output as following
The 32 Size get’s better time because it fits in Level 1 cache where 64 fits in Level 2 cache.
The Blocked interchanged gets the in between performance even when it has 2
optimizations, because the interchanged get’s the best performance where the blocked
optimization get better than normal but worse than the interchanged one.


