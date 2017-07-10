import random
import math

def gen(bound):
	return math.floor(random.random() * bound + 1)


with open('data3.txt', 'w') as file:
	length = 50000
	for i in range(length):
		file.write('?')
	file.write('\n')
	for i in range(length):
		file.write(str(gen(1e6)))
		file.write(' ')
		file.write(str(gen(1e6)))
		file.write('\n')
