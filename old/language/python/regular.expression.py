import re
pattern = re.compile(r"\[(on|off)\]") # slight
print(re.search(pattern, "Mono: Playback 65 [75%] [-16.50dB] [on]"))
print(re.search(pattern, "Nada...:-("))

def test_email(your_pattern):
    pattern = re.compile(your_pattern)
    emails = ["john@example.com", "python-list@python.org", "wha.t.`1an?ug{}ly@email.com"]
    for email in emails:
        if not re.match(pattern, email):
            print("You failed to match %s" % (email))
        elif not your_pattern:
            print("Forgot to enter a pattern!")
        else:
            print("Pass")

pattern = r"[a-zA-Z0-9-.`\{\}\?]*@[a-zA-Z0-9]*.[a-zA-Z0-9]*"
pattern = r"\"?([-a-zA-Z0-9.`?{}]+@\w+\.\w+)\"?"
test_email(pattern)
