with open('data5e.txt', 'w') as file:
	file.write('1000000')
	file.write('\n')
	for i in range(1000000-1):
		file.write(str(1000000-i))
	file.write('1')