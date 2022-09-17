import os, sys

_, f1, f2, gen, iters = sys.argv

for i in range(int(iters)):
    print('Test', i + 1)
    os.popen('python3 %s > test.txt' % gen)
    v1 = os.popen('./%s < test.txt' % f1).read()
    v2 = os.popen('./%s < test.txt' % f2).read()
    if v1 != v2:
        print('Failed test:', open('test.txt').read(), sep=' ')
        print(f'Output of {f1}:', v1, sep=' ')
        print(f'Output of {f2}:', v2, sep=' ')
        break