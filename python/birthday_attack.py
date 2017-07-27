#!/bin/env python

import sys

def calculate_half_probability_attack(n):
    non_conflict_p = 1.0
    for i in range(1, n):
        p = 1 - 1.0 * i / n
        non_conflict_p *= p
        if non_conflict_p <= 0.5:
            print('The %dth element has the probability of %f to conflict' % (i, 1 - non_conflict_p))
            return i
    return -1

def usage(progname):
    print('Calculate how many elements can cause conflict probability exceed 50% for a given number')
    print('Usage: %s N' % (progname))

if __name__ == '__main__':
    if len(sys.argv) != 2:
        usage(sys.argv[0])
        sys.exit(1)
 
    calculate_half_probability_attack(int(sys.argv[1]))
