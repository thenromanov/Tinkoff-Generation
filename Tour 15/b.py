b = int(input())
n = int(input())
m = int(input())

c = 0
while c <= 31 and (b ** c) % m != 0:
    c += 1
if (b ** c) % m == 0 and c < n:
    print(c)
    exit(0)
if m >= b ** min(n, 31):
    if n == 1:
        print(1)
    else:
        print(0)
    exit(0)
if b == 2:
    print(n - 1)
    exit(0)
print(n)