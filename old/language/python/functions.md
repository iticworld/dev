# FUNCTIONS

## WHAT ARE FUNCTIONS?

Functions are a convenient to divide your code into useful blocks, allowing us to order our code, make it more readable, reuse it and save some time. Also functions are a key way to define interfaces so programmers can share their code.

## HOW DO YOU WRITE FUNCTIONS IN PYTHON?

As we have seen on previous tutorials, Python makes use of blocks.

A block is a area of code of written in the format of:

```
block_head:
    1st block line
    2nd block line
```

Where a block line is more Python code (even another block), and the block head is of the following format: block_keyword block_name(argument1, argument2, ...) Block keywords you already know are "if", "for", and "while".

Functions in python are defined using the block keyword "def", followed with the function's name as the block's name. For example:

```
def my_function():
    print("Hello From My Function!")
```

Functions may also receive arguments (variables passed from the caller to the function). For example:

```
def my_function_with_args(username, greeting):
    print("Hello, %s , From My Function!, I wish you %s" % (username, greeting))
```

Functions may return a value to the caller, using the keyword - 'return'. For example:

```
def sum_two_numbers(a, b):
    return a + b
```

## HOW DO YOU CALL FUNCTIONS IN PYTHON?

Simply write the function's name followed by (), placing any required arguments within the brackets. For example, lets call the functions written above (in the previous example):

```
def my_function():
    print("Hello From My Function!")

def my_function_with_args(username, greeting):
    print("Hello %s , From My Function!, I wish you %s", %(username, greeting))

def sum_two_numbers(a, b):
    return a + b

my_function()

my_function_with_args("John Doe", "a greet year!")

x = sum_two_numbers(1, 2)
```

## EXERCISE

In this exercise you'll use an existing function, and write adding your own to create a fully functional program.

1. Add a function named list_benefits() that returns the following list of strings: "More organized Code", "More readable code", "Easier code reuse", "Allow programmers to share and connect code together"

2. Add a function named build_sentence(info) which receives a single argument containing a string and returns a sentence starting with the given string and ending with the string " is a benefit of functions!"

3. Run and see all the functions work together!

```
def list_benefits():
    return ["More organized Code", "More readable code", "Easier code reuse", "Allow programmers to share and connect code together"]

def build_sentence(benefit):
    return benefit + " is a benefit of functions!"

def name_the_benefits_of_functions():
    list_of_benefits = list_benefits()
    for benefit in list_of_benefits:
        print(build_sentence(benefit))

name_the_benefits_of_functions()
```
