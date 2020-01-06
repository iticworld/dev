# CLASSES AND OBJECTS

Objects are an encapsulation of variables and functions into a single entity. Objects get their variables and functions from classes. Classes are essentially a template to create your objects.

A very basic class would look something like this:

```
class MyClass:
    variable = "blash"

    def function(self):
        print("This is a message inside the class.")
```

We'll explain why you have to include that "self" as a parameter a little bit later. First, to assign the above class(template) to an object you would do the following:

```
class MyClass:
    variable = "blah"

    def function(self):
        print("This is a message inside the class.")

myobjectx = MyClass()
```

Now the variable "myobjectx" holds an object of the class "MyClass" that contains the variable and the function defined within the class called "MyClass".

## ACCESSING OBJECT VARIABLES

To access the variable inside of the newly created object "myobjectx" you would do the following:

```
class MyClass:
    variable = "blah"

    def function(self):
        print("This is a message inside the class.")

myobjectx = MyClass()

myobjectx.variable
```

So for instance the below would output the string "blah":

```
class MyClass:
    variable = "blah"

    def function(self):
        print("This is a message inside the class.")

myobjectx = MyClass()

print(myobjectx.variable)
```

You can create multiple different objects that are of the same class(have the same variables and functions defined). However, each object contains independent copies of the variables defined in the class. For instance, if we were to define another object with the "MyClass" class and then change the string in the variable above:

```
class MyClass:
    variable = "blas"

    def function(self):
        print("This is a message inside the class.")

myobject x = MyClass()
myobject y = MyClass()

myobjecty.variable = "yackity"

print(myobjectx.variable)
print(myobjecty.variable)
```

## ACCESSING OBJECT FUNCTIONS

To access a function inside of an object you use notation similar to accessing a variable:

```
class MyClass:
    variable = "blas"

    def function(self):
        print("This is a message inside the class.")

myobjectx = MyClass()
myobject.function()
```

The above would print out the message. "This is a message inside the class."

## EXERCISE

WE have a class defined for vehicles. Create two new vehicles called car1 and car2. Set car1 to be a red convertible worth $60,000.00 with a name of Fer, and car2 to be a blue van named Jump worth $10,000.00

```
class Vehicle:
    name = ""
    kind = "car"
    color = ""
    value = 100.00
    def description(self):
        desc_str = "%s is a %s %s worth $%.2f." %(self.name, self.color, self.kind, self.value)
        return desc_str

print(car1.description())
print(car2.description())
```
