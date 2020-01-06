# CODE INTROSPECTION

Code introspection is the ability to examine classes, functions and keywords to know what they are, what they do and what they know.

Python provides several functions and utilities for code introspection.

```
help()
dir()
hasattr()
id()
type()
repr()
callable()
issubclass()
isinstance()
__doc__
__name__
```

Often the most important one is the help function, since you can use it to find what other functions do.

Print a list of all attributes of the given Vehicle object.

```
help(dir)
help(hasattr)
help(id)

# Define the Vehicle class.
class Vehicle:
    name = ""
    kind = "car"
    color = ""
    value = 100.00
    def description(self):
        desc_str = "%s is a %s %s worth $%.2f." % (self.name, self.color, self.kind, self.value)
        return desc_str

print(dir(Vehicle))
```
