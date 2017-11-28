# n start with 100000
# coin flip results:
# - front: 1
# - back: 0
#
import sys
from random import *

def coinFlip():
    return randint(0,1)

if __name__ == "__main__":
    defaultFlipCount = 100000
    flipResults = [0, 0]

    for _ in range(defaultFlipCount):
        flipResults[coinFlip()] += 1

    while flipResults[0] != flipResults[1]:
        flipResults[coinFlip()] += 1
    
    print("Total flip count: %d" % sum(flipResults))