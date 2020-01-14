

# Poor definition:
def bad_fib(index):
    if index == 0 or index == 1:
        return 1
    return bad_fib(index - 1) + bad_fib(index - 2)


def fib(index):
    if index == 0 or index == 1:
        return 1
    return fib(index - 1) + fib(index - 2)
