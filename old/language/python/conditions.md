# CONDITIONS

Python uses boolean variables to evaluate conditions. The boolean values True and False are returned when an expression is compared or evaluated. For example:

```
x = 2
print(x == 2)
print(x == 3)
print(x < 3)
```

Notice that variable assignment is done using a single equals operator "=", whereas comparison between two variables is done using the double equals operator "==". The "not equals" operator is marked as "!=".

## BOOLEAN OPERATORS

```
name = "John"
age = 23

if name == "John" and age == 23:
    print("Your name is John, and you are also 23 years old.")

if name == "John" or name == "Rick":
    print("Your name is either John or Rick.")
```

## THE "IN" OPERATOR

The "in" operator could be used to check if a specified object exist within an iterable object container, such as a list:

```
name = "John"
if name in[ "John", "Rick" ]:
    print("Your name is either John or Rick.")
```

Python uses indentation to define code blocks, instead of brackets. The standard Python indentation is 4 spaces, although tabs and any other space size will work, as long as it is consistent. Notice that code blocks do not need any termination.

Here is an example for using Python's "if" statement using cod blocks:

```
if <statement is="" true="">:
    <do something="">
    ....
    ....
elif <another statement="" is="" true="">: # else if
    <do something="" else="">
    ....
    ....
else:
    <do another="" thing="">
    ....
    ....
</do></do></another></do></statement>
```

For example

```
x = 2
if x == 2:
    print("x equals two!")
else:
    print("x does not equal to two.")
```    

A statement is evaluated as true if one of the following is correct: 1. The "True" boolean variable is given, or calculated using an expression, such as an arithmetic comparison. 2. An object which is not considered "empty" is passed.

Here are some examples for objects which are considered as empty: 1. An empty string: "" 2. An empty list: [] 3. The number zero: 0 4. The false boolean variable: False

## THE "IS" OPERATOR

Unlike the double equals operator "==", the "is" operator does not match the values of the variables, but the instances themselves. For example:

```
x = [1,2,3]
y = [1,2,3]
print(x==y)
print(x is y)
```

## THE "NOT" OPERATOR

Using "not" before a boolean expression inverts it:

```
print(not False)
print((not False) == (False))
```
