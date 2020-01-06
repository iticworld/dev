s = "Hey there! what should this string be?"
print("Length of s %d" % len(s))

print("The first occurrence of the letter a = %d" % s.index("a"))

print("a occurs %d times" % s.count("a"))

print("The first five characters are '%s'" % s[:5])
print("The next first characters are '%s'" % s[5:10])
print("The thirteenth characters '%s'" % s[12])
print("The chacters with odd index are '%s'" % s[1::2])
print("The last five characters are '%s'" % s[-5:])

print("String in uppercase: %s" % s.upper())
