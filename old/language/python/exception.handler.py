def do_stuff_with_number(n):
    print(n)

the_list = (1, 2, 3, 4, 5)
for i in range(20):
    try:
        do_stuff_with_number(the_list[i])
    except IndexError:
        do_stuff_with_number(0)

# Handle all the exceptions!
#Setup
actor = {"name": "John Cleese", "rank": "awesome"}

#Function to modify, should return the last name of the actor - think back to previous lessons for how to get it
def get_last_name():
    return actor["name"].split()[1]

#Test code
get_last_name()
print("All exceptions caught! Good job!")
print("The actor's last name is %s" % get_last_name())
