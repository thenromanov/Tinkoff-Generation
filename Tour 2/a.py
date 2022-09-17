l = int(input())
r = int(input())

if len(str(l)) == 1 and len(str(r)) == 1:
    print(r - l + 1)
    exit()

if len(str(l)) == 1:
    ans = 10 - l
    rstep = 1
    while rstep <= r:
        rstep *= 10
    rstep //= 10
    rstep *= (r // rstep)
    ans += (rstep // 10 - 1) * 10
    for d in range(10):
        cur = list(str(rstep))
        for pos in range(1, len(str(rstep))):
            cur[pos] = str((int(cur[pos - 1]) + d) % 10)
        if int(''.join(cur)) <= r:
            ans += 1
    print(ans)
    exit()


rstep = 1;
while rstep <= r:
    rstep *= 10
rstep //= 10
rstep *= (r // rstep)

lstep = 1
while lstep <= l:
    lstep *= 10
lstep //= 10
lstep *= (l // lstep)

lcp = lstep
rcp = rstep
while lcp % 10 == 0:
    lcp //= 10
    rcp //= 10

ans = (rcp - lcp) * 10

if len(str(l)) == 1:
    for d in range(10):
        if d < l:
            ans -= 1
else:
    for d in range(10):
        cur = list(str(lstep))
        for pos in range(1, len(str(lstep))):
            cur[pos] = str((int(cur[pos - 1]) + d) % 10)
        if int(''.join(cur)) < l:
            ans -= 1

for d in range(10):
    cur = list(str(rstep))
    for pos in range(1, len(str(rstep))):
        cur[pos] = str((int(cur[pos - 1]) + d) % 10)
    if int(''.join(cur)) <= r:
        ans += 1

print(ans)
