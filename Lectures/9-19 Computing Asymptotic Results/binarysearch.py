import math

epsilon = 1e-9

# Binary search (iterative version)
def nlogn(c):
    lower = 0.0
    upper = c
    while True:
        # Avoid any possible overflow when computing middle:
        # not (lower + upper) / 2 because the addition result could be too large (overflow)
        middle  = lower + (upper - lower) / 2
        # since we half it each time, algorithm is O(log c)
        # not big theta because you might get lucky right away in the first 'middle'
        val = middle * math.log(middle, 2)
        if abs(c - val) <= epsilon:
            # Rounding down to integer
            # because we get the biggest integer that we can guarantee that for this size input the algorithm finishes
            return int(middle)
        if val > c:
            upper = middle
        else:
            lower = middle

# Binary search (recursive version)
def nlogn_rec_helper(c, lower, upper):
    # Avoid any possible overflow when computing middle:
    middle = lower + (upper - lower)/ 2
    val = middle * math.log(middle, 2)
    if abs(c - val) <= epsilon:
        # Rouding down to integer:
        return int(middle)
    if val > c:
        return nlogn_rec_helper(c, lower, middle)
    else:
        return nlogn_rec_helper(c, middle, upper)

def nlogn_rec(c):
    return nlogn_rec_helper(c, 0.0, c)

# print(nlogn(3600000000))
# print(nlogn_rec(3600000000))
print(nlogn(36000000))