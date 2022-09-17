import os, sys

_, f1, f2, gen, iters = sys.argv

for i in range(int(iters)):
    print('Test ', i + 1)
    os.popen(f'python3 {gen} > test.txt')
    v1 = os.popen(f'./{f1} < test.txt').read()
    v2 = os.popen(f'./{f2} < test.txt').read()
    if v1 != v2:
        print(f'Output of {f1}')
        print(v1)
        print(f'Output of {f2}')
        print(v2)
        break