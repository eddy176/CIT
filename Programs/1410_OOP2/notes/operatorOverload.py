# lhs (the operand on the left) op (the operator) rhs(the operand on the right)
# op can be +, -, *, /, //, <, >,  etc...

class Fraction:
    def __init__(self):
        self.mN = int(n)
        self.mD = int(d)

    def getDisplayString(self):
        s = str(self.mN) + " / " + str(self.mD)

    def __ad__(self, rhs):
        n = self.mN * rhs.mD + rhs.mN * self.mD
        d = self.mD * rhs.mD
        f = Fraction (n, d)
        return f

    def__truediv__(self, rhs):
        n = self.mN * rhs.mD
        d = self.mD * rhs.mD
        f = Fraction(n, d)
        return f

    def __str__(self):
        s = str(self.mN) + " / " + str(self.mD)
        return s

# look here!!!
# fractions can be added in python!
    def __add__(self, rhs):
        if isinstance(rhs, Fraction):
            n = self.mN * rhs.mD + rhs.mN * self.mD
            d = self.mD * rhs.mD
        # int types can be added to fractions
        elif isinstance(rhs, Fraction):
            n = self.mN * 1 + rhs.mN * self.mD
            d = self.mD * 1
        else:
            return NotImplemented
        f = Fraction(n, d)
        return f

#reverse add
    def __radd__(self, lhs):
        if isinstance(lhs, int):
            n = self.mN * 1 + rhs.mN * self.mD
            d = self.mD * 1
        else:
            return NotImplemented
        f = Fraction(n, d)
        return f
# ==
    def __eq__(self, rhs):
        left = self.mN * rhs.mD
        right = rhs.mN * self.mD
        if left == right:
            r = True
        else:
            r = False
        return r
# !=
    def __ne__(self, rhs):
        left = self.mN * rhs.mD
        right = rhs.mN * self.mD
        if left != right:
            r = True
        else:
            r = False
        return r

# <
    def __lt__(self, rhs):
        left = self.mN * rhs.mD
        right = rhs.mN * self.mD
        if left < right:
            r = True
        else:
            r = False
        return r
# > (using math from __lt__)
    def __gt__(self, rhs):
        return rhs < self

    def main():
        if f == g:
            print ( '==' )
        elif f != g:
            print( '!=' )
        return

# <=
    def __le__(self, rhs):
        return rhs < self or self == rhs

# >=
    def __ge__(self, rhs):
        return rhs > self or self == rhs