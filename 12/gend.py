import random
def main():
    n = 500000
    f = open("d.data", "w")
    f.write(str(n) + '\n')
    for i in range(0, n):
        f.write(str(random.randint(0, 10**9)) + ' ')
    f.write('\n')
    for i in range(0, n):
        f.write(str(random.randint(0, 10**9)) + ' ')
    f.write('\n')
    for i in range(0, n):
        f.write(str(random.randint(0, 10**9)) + ' ')
    f.write('\n')
    f.close()

main()