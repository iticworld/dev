# DECORATOR

Decorator allow you to make simple modifications to callable objects like functions, methods, or classes. We shall deal with functions for this tutorial. The syntax

```
@decorator
def function(arg):
    return "value"
```

Is equivalent to:

```
def function(arg):
    return "value"
function = decorator(function)
```

As you may have seen, a decorator is just another function which takes a functions and returns one. For example you could do this:

```
def repeater(old_function):
    def new_function(*args, **kwds):
        old_function(*args, **kwds)
        old_function(*args, **kwds)
    return new_function
```

This would make a function repeat twice:

```
>>> @repeater
def multiply(num1, num2):
    print(num1 * num2)

>>> multiply(2, 3)
6
6
```

You can also make it change the output

```
def double_out(old_function):
    def new_function(*args, **kwds):
        return 2 * old_function(*args, **kwds)
    return new_function
```

change input

```
def double_Ii(old_function):
    def new_function(arg):
        return old_function(arg * 2)
    return new_function
```

and do checking.

```
def check(old_function)
    def new_function(arg):
        if arg < 0: raise(ValueError, "Negative Argument")
        old_function(arg)
    return new_function
```

Let's say you want to multiply the output by a variable amount. You could define the decorator and use it as follows:

```
def multiply(multiplier):
    def multiply_generator(old_function):
        def new_function(*args, **kwds):
            return multiplier * old_function(*args, **kwds)
        return new function
    return multiply_generator

@multiply(3)
def return_num(num):
    return num

return_num(5)
```

You can do anything you want with the old function, even completely ignore it! Advanced decorators can also manipulate the doc string and argument number. For some snazzy decorators, go to http://wiki.python.org/moin/PythonDecoratorLibrary.

# EXERCISE

Make a decorator factory which returns a decorator that decorates functions with one argument. The factory should take one argument, a type, and then returns a decorator that makes function should check if the input is the correct type. If it is wrong, it should print("Bad Type") (In reality, it should raise an error, but error raising isn't in this tutorial). Look at the tutorial code and expected output to see what it is if you are confused (I know I would be.) Using isinstance(object, type_of_object) or type(object) might help

```
def type_check(correct_type):
    def check(old_function):
        def new_function(arg):
            if (isinstance(arg, correct_type)):
                return old_function(arg)
            else:
                print("Bad Type")
        return new_function
    return check

@type_check(int)
def times2(num):
    return num*2

print(times2(2))
times2('Not A Number')

@type_check(str)
def first_letter(word):
    return word[0]

print(first_letter('Hello World'))
first_letter(['Not', 'A', 'String'])
```
