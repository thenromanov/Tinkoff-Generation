import random

n, m = random.randint(3, 1000), random.randint(3, 1000)
print(n, m)
for i in range(n):
    print(random.randint(1, 1000000), end=' ')
print()
for i in range(m):
    c = random.randint(0, 1)
    l = random.randint(1, n)
    r = random.randint(l, n)
    if c == 1:
        print(c, l, r, random.randint(1, 1000000))
    else:
        print(c, l, r)
