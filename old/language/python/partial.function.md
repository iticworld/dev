# PARTIAL FUNCTION

You can create partial functions in python by using the partial function from the function library.

Partial function allow one to derive a function with x parameters to a function with fewer parameters and fixed values set for the more limited function.

Import required:

```
from functools import partial
```

This code will return 8.

```
from functools import partial

def multiply(x, y):
    return x * y

dbl = partial(multiply, 2)
print(dbl(4))
```

An important note: the default values will start replacing variable from the left. The 2 will replace x, y will equal 4 wne dbl(4) is called. It does not make a difference in this example, but it does in the example below:

Edit the function provided by calling partial() and replacing the first three variables in func(). Then print with the new partial function using only one input variable so that the output equals 60.

```
from functools import partial
def func(u,v,w,x):
    return u*4 + v*3 + w*2 + x

p = partial(func,5,6,7)
print(p(8))
```
