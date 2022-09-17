import random

n = random.randint(1, 100)
s = ""
for i in range(n):
    s = s + chr(random.randint(32, 126))
print(s)
k = random.randint(1, 100)
print(k)