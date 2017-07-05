import random
import math

a = 1e9
b = 1e10 -1

def gen():
	return math.floor(random.random() * (b - a) + a)


with open('data2.txt', 'w') as file:
	file.write('{:d}'.format(1000) + '\n')
	for i in range(1000000):
		file.write('{:d}'.format(gen()) + ' ')

