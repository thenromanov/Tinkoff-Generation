import random, os, sys

_, solution, iters = sys.argv

for i in range(1, int(iters) + 1):
    with open(f"./tests/{str(i).rjust(3, '0')}.dat", 'w') as f:
        n = random.randint(1, 200000)
        f.write(f'{n}\n')
        f.write(f'{" ".join([str(random.randint(0, 1000000000)) for _ in range(n)])}\n')
    ans = os.popen(f'./solution < ./tests/{str(i).rjust(3, "0")}.dat').read()
    with open(f'./tests/{str(i).rjust(3, "0")}.ans', 'w') as f:
       f.write(ans)