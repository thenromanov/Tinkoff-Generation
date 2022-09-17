f = open('test.txt', 'w')
f.write("1 1000000\n")
for i in range(1000000):
    f.write(f'{i % 2}')
f.write("\n")
f.write("1000000 1\n")
for i in range(1000000):
    f.write(f'{i % 2}\n')
f.close()