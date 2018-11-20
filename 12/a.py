
def is_central_symetric(keys):
    rslt = True
    for i in range(0, 5):
        x = i // 3
        y = i % 3 
        if keys[x][y] != keys[2-x][2-y]:
            rslt = False
            break
    return rslt


def main():
    line1 = input()
    line2 = input()
    line3 = input()
    keys = [line1, line2, line3]
    print(is_central_symetric(keys))
  
if __name__ == '__main__':
    main()
