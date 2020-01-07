phonebook = {}
phonebook["John"] = 938477566
phonebook["Jack"] = 938377264
phonebook["Jill"] = 937662781
print(phonebook)

phonebook = {
    "Jonh": 938477566,
    "Jack": 938377264,
    "Jill": 947662781
}
print(phonebook)

phonebook = {"John": 938477566, "Jack": 93837264, "Jill": 947662781}
for name, number in phonebook.items():
    print("Phone number of %s is %d" % (name, number))

phonebook = {
    "John": 938477566,
    "Jack": 938377264,
    "Jill": 947662781
}
del phonebook["John"]
print(phonebook)

phonebook = {
    "John": 938477566,
    "Jack": 938377264,
    "Jill": 947662781
}
phonebook.pop("John")
print(phonebook)

phonebook = {
    "John" : 938477566,
    "Jack" : 938377264,
    "Jill" : 947662781
}

phonebook["Jake"] = 938273443
phonebook.pop("Jill")

if "Jake" in phonebook:
    print("Jake is listed in the phonebook.")
if "Jill" not in phonebook:
    print("Jill is not listed in the phonebook.")
