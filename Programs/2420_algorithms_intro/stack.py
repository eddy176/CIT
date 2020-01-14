#stack class
#cs 2420
class Stack:

    def __init__(self):
        self.stack = []

    def push(self, p):
        self.stack.append(p)

    def pop(self):
        p = self.stack.pop()
        return p

    def top(self):
        return self.stack[- 1]

    def isEmpty(self):
        if len(self.stack) == 0:
            return True
        else:
            return False