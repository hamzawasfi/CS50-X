from cs50 import get_float

while True:
    change = get_float("What is the change? ") * 100.0
    if change >= 0:
        break

coins = [25, 10, 5, 1]

total = 0
for coin in coins:
    total +=  int(change / coin)
    change %= coin
print(total)
