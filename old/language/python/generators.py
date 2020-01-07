import random

def lottery():
    # returns 6 numbers between 1 and 40
    for i in range(6):
        yield random.randint(1, 40)

    # return a 7th number between 1 and 15
    yield random.randint(1, 15)

for random_number in lottery():
    print("And the next number is ... %d!" %(random_number))

a = 1
b = 2
a, b = b, a
print(a,b)

# fill in this function
def fib():
    a = 1
    b = 2
    while 1:
        a, b = b, (a + b)
        yield a, b


import types
if type(fib()) == types.GeneratorType:
    print("Good, The fib function is a generator.")

    counter = 0
    for n in fib():
        print(n)
        counter += 1
        if counter == 10:
            break
