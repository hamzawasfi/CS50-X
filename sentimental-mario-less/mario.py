from cs50 import get_int

while True:
    height = get_int("Which height? ")

    if height <= 8 and height >= 1:
        break

for i in range(height):
    for j in range(height - i - 1):
        print(" ", end = "")
    for k in range(i + 1):
        print("#", end = "")
    print("")
