for d in range(10):
    cur = list(str(rstep))
    for pos in range(1, len(str(rstep))):
        cur[pos] = str((int(cur[pos - 1]) + d) % 10)
    if int(''.join(cur)) <= r:
        ans += 1