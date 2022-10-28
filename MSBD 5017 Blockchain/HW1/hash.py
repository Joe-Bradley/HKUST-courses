import hashlib


def do_cal(string):
    md5 = hashlib.md5()
    md5.update(string.encode("utf-8"))
    return md5.hexdigest()


a = "Hello, world!"
b = ""
number = 1
while b[:4] != "0000":
    c = a + str(number)
    b = do_cal(c)
    number = number + 1
print("The string is: " + c)
print("The hash value of string is: " + b)
