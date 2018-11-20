import bisect

class Lady:
    def __init__(self, beauty,  intellect, richness):
        self.beauty = beauty
        self.intellect = intellect
        self.richness = richness
    
    def __repr__(self):
        return "%s, %s, %s" % (self.beauty, self.intellect, self.richness)
    
def input_str_to_list(str):
    return list(map(int, str.split()))

def main():
    n = int(input())
    beauty = input_str_to_list(input()) 
    intellect = input_str_to_list(input())
    richness = input_str_to_list(input())
    ladies = [Lady(beauty[i], intellect[i], richness[i]) for i in range(0, n)]
    # Sort in reverse order according to beauty, and secondary on intellect
    ladies.sort(key=lambda l: (-l.beauty, l.intellect))

    # Calculate how many are greater than the current intellect
    sorted_intellect = sorted(intellect)
    # intellect_greater = [n - bisect.bisect_left(sorted_intellect, item.intellect) for item in ladies] 
    for item in ladies:
        item.intellect_greater = n - bisect.bisect_left(sorted_intellect, item.intellect)
    # print(intellect_greater)
    # print(ladies)

    richest_from_me = [-10**10] * (n+1)
    ans = 0
    for i in range(0, n):
        lady = ladies[i]
        maximum = -10 ** 10
        i = lady.intellect_greater - 1
        while i != 0:
            if richest_from_me[i] > maximum:
                maximum = richest_from_me[i]
            i = i - (i & -i) 
        
        if maximum > lady.richness:
            ans = ans + 1 
        
        i = lady.intellect_greater
        while i <= n:
            if richest_from_me[i] < lady.richness:
                richest_from_me[i] = lady.richness
            i = i + (i & -i)
    print(ans)


if __name__ == '__main__':
    main()


