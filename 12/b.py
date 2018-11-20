def main():
    num = input()
    ans = input()
    a = [int(i) for i in num]
    a.sort()
    if a[0] == 0:
        idx = 1
        for i in range(1, len(a)):
            if a[i] != 0:
                idx = i
                break
        a[0] = a[idx]
        a[idx] = 0
    rslt = ''.join([str(i) for i in a])
    print (rslt == ans)


if __name__ == '__main__':
    main()