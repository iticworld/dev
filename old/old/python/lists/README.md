# LISTS

Lists are very similar to arrays. They can contain any type of variable, and they contain as many variables as you wish.
Lists can also iterated over in a very simple manner.
Here is an example of how to build a list.

```
mylist = []
mylist.append(1)
mylist.append(2)
mylist.append(3)
print(mylist[0]) # print 1
print(mylist[1]) # print 2
print(mylist[2]) # print 3

# prints out 1, 2, 3
for x in mylist:
    print(x)
```

Accessing an index which does not exist generates an exception (an error).

```
mylist = [1, 2, 3]
print(mylist[10])
```

## Exercise

In this exercise, you will need to add numbers and strings to the correct lists using the "append" list method.
You must add the numbers 1, 2, and 3 to the "numbers" list, and the words 'hello' and 'world' to the strings variables.

You will also have to fill in the variable second_name with the second name in the names list, using the brackets operator ```[]```.
Note that the index zero-based, so if you want to access the second item in the list, its index will be 1.

```
numbers = []
strings = []
names = ["John", "Eric", "Jessica"]

# write your code here
second_name = names[1]

print(numbers)
print(strings)
print("The second name on the names list is %s" % second_name)
```