from cs50 import get_int

number = get_int("Number: ")
length = len(str(number))

def isVisa(number, length):
    if (length == 13 or length == 16) and str(number)[0] == "4":
        return True
    return False

def isAE(number, length):
    code = int(str(number)[0] + str(number)[1])
    codes = [34, 37]
    if length == 15 and code in codes:
        return True
    return False

def isMaster(number, length):
    code = int(str(number)[0] + str(number)[1])
    codes = range(51, 56)
    if length == 16 and code in codes:
        return True
    return False

def checkSum(number, length):
    sum = 0
    for i in range(length - 2, -1, -2):
        sum = sum + int(str(number)[i]) * 2 if len(str(int(str(number)[i]) * 2)) == 1 else sum + int(str(int(str(number)[i]) * 2)[0]) + int(str(int(str(number)[i]) * 2)[1])
    for i in range(length - 1, -1, -2):
        sum += int(str(number)[i])
    if sum % 10 == 0:
        return True
    else:
        return False

type = "VISA" if isVisa(number, length) else "MASTERCARD" if isMaster(number, length) else "AMEX" if isAE(number, length) else "INVALID"
if type != "INVALID":
    type = "INVALID" if not checkSum(number, length) else type

print(type)
