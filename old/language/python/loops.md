# LOOPS

There are two types of loops in Python, for and while

## THE "FOR" LOOP

For loops iterate over a given sequence. Here is an example:

```
primes = [2, 3, 5, 7]
for prime in primes:
    print(prime)
```

For loops can iterate over a sequence of numbers using the "range" and "xrange" functions. The difference between range and xrange is that the range function returns a new list with numbers of that specified range, whereas xrange returns an iterator, which is more efficient. (Python 3 uses the range function, which acts like xrange). Note that the range function is zero based.

```
for x in range(5):
    print(x)

for x in range(3, 6):
    print(x)

for x in range(3, 8, 2):
    print(x)
```

## "WHILE" LOOPS

While loops repeat as long as a certain boolean condition is met. For examle:

```
count = 0
while count < 5:
    print(count)
    count += 1
```

## "BREAK" AND "CONTINUE" STATEMENTS

break is used to exit a for loop or a while loop, whereas continue is used to skip the current block, and return to the "for" or "while" statement. A few examples:

```
count = 0
while True:
    print(count)
    count += 1
    if count >= 5:
        break

for x in range(10):
    if x % 2 == 0:
        continue
    print(x)
```

## CAN WE USE "ELSE" CLAUSE FOR LOOPS?

Unlike languages like C, CPP.. we can use else for loops. When the loop condition of "for" or "while" statement fails then code part in "else" is executed. If break statement is executed inside for loop then the "else" part is skipped. Note that "else" part is executed even if there is a condinue statement.

Here are a few examples:

```
count = 0
while(count<5):
    print(count)
    count += 1
else
    print("count value reached %d" % (count))

for i in range(i, 10)
    if(i%5 == 0):
        break
    print(i)
else
    print("this is not printed because for loop is terminated because of break but not due to fail in condition")
```

## EXERCISE

Loop through and print out all even numbers from the numbers lists in the same order they are received. Don't print any numbers that come after 237 in the sequence.

```
s
```
