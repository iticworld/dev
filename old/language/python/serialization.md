# SERIALIZATION

Python provides built-in JSON libraries to encode and decode JSON.

In Python 2.5, the simplejson module is used, whereas in Python 2.7, the json module is used. Since this interpreter used Python 2.7, we'll be using json.

In order to use the json module, it must first be imported:

```
import json
```

There are two basic formats for JSON data. Either in a string or the object data structure. The object data structure, in Python, consist of lists and directories nested inside each other. The object data structure allows one to use python methods (for lists and dictionaries) to add, list, search and remove elements from the data structure. The String format is mainly used to pass the data into another program or load into a data structure.

To load JSON back to a data structure, use the "loads" method. This method takes a string and turns it back into the json object data structure.

```
import json
print(json.loads(json_string))
```

To encode a data structure to JSON, use the "dumps" method. This method takes an object and returns a String:

```
import json
json_string = json.dumps([1, 2, 3, "a", "b", "c"])
print(json_string)
```

The aim of this exercise is to print out the JSON string with key value pair "Me": 800 added to it.

```
import json
def add_employee(salaries_json, name, salary):
    salaries_json[name] = salary
    return salaries_json

# test code
salaries = '{"Alfred" : 300, "Jane" : 400 }'
new_salaries = add_employee(salaries, "Me", 800)
decoded_salaries = json.loads(new_salaries)
print(decoded_salaries["Alfred"])
print(decoded_salaries["Jane"])
print(decoded_salaries["Me"])
```
