# GENERATORS

Generators are very easy to implement, but a bit difficult to understand.

Generators are used to iterators, but with a different approach.
Generators are simple functions which return an iterable set of items, one at a time, in a special way.

When an iteration over an set of item starts using the for statement, the generator is run.
Once the generator's function code reaches a "yield" statement, the generator yields its execution back to the for loop, returning a new value form the set. The generator function can generate as many values (possibly infinite) as it wants, yielding each one in its turn.

Here is a simple example of a generator function which returns 7 random integers:

```
import random

def lottery():
    # returns 6 numbers between 1 and 40
    for i in range(6):
        yield random.randint(1, 40)

    # return a 7th number between 1 and 15
    yield random.randint(1, 15)

for random_number in lottery():
    print("And the next number is ... %d!" %(random_number))
```

This function decides how to generate the random numbers on its own, and executes the yield statements one at a time, pausing in between to yield execution back to the main for loop.

## EXERCISE

Write a generator function which returns the Fibonacci series. They are calculated using the following formula: The first two numbers of the series is always equal to 1, and each consecutive number returned is the sum of the last numbers. Hint: Can you use only two variable in the generator function? Remember that assignments can be done simultaneously. The code

```
a = 1
b = 2
a, b = b, a
print(a,b)
```

will simultaneously switch the values of a and b.

```
# fill in this function
def fib():
    a = 1
    b = 2
    a, b = b, (a + b)
    yield a, b


import types

if type(fib()) == types.GeneratorType:
    print("Good, The fib function is a generator.")

    counter = 0;
    for n in fib():
        print(n)
        counter += 1
        if counter == 10:
            break;
```
