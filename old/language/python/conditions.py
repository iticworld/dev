x = 2
print(x == 2)
print(x == 3)
print(x < 3)

name = "John"
age = 23

if name == "John" and age == 23:
    print("Your name is John, and you are also 23 years old.")

if name == "John" or name == "Rick":
    print("Your name is either John or Rick.")

name = "John"
if name in[ "John", "Rick" ]:
    print("Your name is either John or Rick.")

x = 2
if x == 2:
    print("x equals two!")
else:
    print("x does not equal to two.")

x = [1,2,3]
y = [1,2,3]
z = x
print(x==y)
print(x is y)
print(x is z)

print(not False)
print((not False) == (False))

number = 20
second_number = 0
first_array = [1,2,3]
second_array = [4,5]

if number > 15:
        print("1")

if first_array:
    print("2")

if len(second_array) == 2:
    print("3")

if len(first_array) + len(second_array) == 5:
    print("4")

if first_array and first_array[0] == 1:
    print("5")

if not second_number:
    print("6")
