class MyClass:
    variable = "blas"

    def function(self):
        print("This is a message inside the class.")

myobjectx = MyClass()
myobjecty = MyClass()

myobjecty.variable = "yackity"

print(myobjectx.variable)
print(myobjecty.variable)

class MyClass:
    variable = "blas"

    def function(self):
        print("This is a message inside the class.")

myobjectx = MyClass()
myobjectx.function()

class Vehicle:
    name = ""
    kind = "car"
    color = ""
    value = 100.00
    def description(self):
        desc_str = "%s is a %s %s worth $%.2f." % (self.name, self.color, self.kind, self.value)
        return desc_str

car1 = Vehicle()
car1.name = "Fer"
car1.value = 60000.00
car1.color = "red"
car1.kind = "convertible"

car2 = Vehicle()
car2.name = "Jump"
car2.value = 10000.00
car2.color = "blue"
car2.kind = "van"

print(car1.description())
print(car2.description())
