# MULTI FUNCTION ARGUMENTS

Every function in Python receives a predefined number of arguments, if declared normally, like this:

```
def myfunction(first, second, third):

```

It is possible to declare functions which receive a variable number of arguments, using the following syntax:

```
def foo(first, second, third, *therest):
    print("First: %s" % first)
    print("Second: %s" % second)
    print("Third: %s" % third)
    print("And all the rest... %s" % list(therest))
```

The "therest" variable is a list of variables, which receives all arguments which were given to the "foo" function after the first 3 arguments.
So calling foo(1,2,3,4,5) will print out:

```
def foo(first, second, third, *therest):
    print("First: %s" %(first))
    print("Second: %s" %(second))
    print("Third: %s" %(third))
    print("And all the rest... %s" %(list(therest)))

foo(1,2,3,4,5)
```

It is also possible to send functions arguments by keyword, so that the order of the argument does not matter, using the following syntax.
The following code yields the following output: The sum is: 6 result: 1

```
def bar(first, second, third, **options):
    if options.get("action") == "sum":
        print("The sum is: %d" %(first + second + third))

    if options.get("number") == "first":
        return first

result = bar(1, 2, 3, action = "sum", number = "first")
print("Result: %d" %(result))
```

The "bar" function receives 3 arguments. If an additional "action" argument is received, and it instructs on summing up the numbers, then the sum is printed out. Alternatively, the function also knows it must return the first argument, if the value of the "number" parameter, passed into the function, is equal to "first".

## EXERCISE

Fill in the foo and bar functions so they can receive a variable amount of arguments (3 or more) The foo function must return the amount of extra arguments received. The bar must return True if the argument with the keyword magicnumber is worth 7, and False otherwise.

```
# edit the functions prototype and implementation
def foo(a, b, c, *list):
    return size(list)

def bar(a, b, c, **option):
    return options.get("magicnumber") == 7

# test code
if foo(1,2,3,4) == 1:
    print("Good.")
if foo(1,2,3,4,5) == 2:
    print("Better.")
if bar(1,2,3,magicnumber = 6) == False:
    print("Great.")
if bar(1,2,3,magicnumber = 7) == True:
    print("Awesome!")
```
