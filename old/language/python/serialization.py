import json
json_string = json.dumps([1, 2, 3, "a", "b", "c"])
print(json_string)

import json
def add_employee(salaries_json, name, salary):
    decoded_salaries = json.loads(salaries_json)
    decoded_salaries[name] = salary
    return json.dumps(decoded_salaries)

# test code
salaries = '{"Alfred" : 300, "Jane" : 400 }'
new_salaries = add_employee(salaries, "Me", 800)
decoded_salaries = json.loads(new_salaries)
print(decoded_salaries["Alfred"])
print(decoded_salaries["Jane"])
print(decoded_salaries["Me"])
