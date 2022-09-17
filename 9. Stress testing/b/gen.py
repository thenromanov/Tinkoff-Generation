import random

n = random.randint(1, 100)
print(n)
for i in range(n):
    l = random.randint(0, 1000)
    arr = [random.randint(-1000000000, 1000000000) for _ in range(l)]
    print(l, *arr)