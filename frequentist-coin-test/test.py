"""Test how many coin flipping is required to get a half chance approximately
using simple random module
"""
import random

class Coin(object):
    HEAD = 1
    TAIL = -1
    CHOICES = [HEAD, TAIL]
    def __init__(self):
        self.face = self.HEAD

    def flip(self):
        self.face = random.choice(self.CHOICES)

    def head_or_tail(self):
        return self.face

class CoinFlipSimulator(object):
    def __init__(self):
        self.coin = Coin()
        self.throwing_count = 0
        self.accumulator = 0

    def throw_coin(self, times=1):
        for _ in range(times):
            self.coin.flip()
            self.throwing_count += 1
            self.accumulator += self.coin.face

    def is_half_chance(self):
        return True if self.accumulator == 0 else False

if __name__ == "__main__":
    SIMULATOR = CoinFlipSimulator()
    SIMULATOR.throw_coin(100000)

    while not SIMULATOR.is_half_chance():
        SIMULATOR.throw_coin(1)

    print "%d times coin flipped to get a half chance by frequentist." % SIMULATOR.throwing_count
