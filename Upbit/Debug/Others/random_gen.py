import random

nl = 800
nr = 80
loop = 1

#size = 70400000

numbers = [10, 20, 30, 40, 50, 60, 70, 80] * nl

#numbers = [10, 20, 30, 40, 50, 60, 70, 80] this are various values possible in the column



fw = open('sample_new.txt', 'w')#set output file name here

fw.write('[C'+ str(0) + '] ')


for i in range(loop):
	
	data = random.sample(numbers, nl)

	data.extend([10] * nr)

	for item in data:
		fw.write('%s ' % item)
	
	data = random.sample(numbers, nl)
	
	data.extend([20] * nr)

	for item in data:
		fw.write('%s ' % item)

	data = random.sample(numbers, nl)

	data.extend([30] * nr)

	
	for item in data:
		fw.write('%s ' % item)
	
	data = random.sample(numbers, nl)
	
	data.extend([40] * nr)
	
	for item in data:
		fw.write('%s ' % item)
	
	data = random.sample(numbers, nl)

	data.extend([50] * nr)

	
	for item in data:
		fw.write('%s ' % item)
	data = random.sample(numbers, nl)

	data.extend([60] * nr)

	
	for item in data:
		fw.write('%s ' % item)

	data = random.sample(numbers, nl)

	data.extend([70] * nr)
	
	for item in data:
		fw.write('%s ' % item)

	data = random.sample(numbers, nl)

	data.extend([80] * nr)
	
	for item in data:
		fw.write('%s ' % item)


fw.write('\n')


fw.write('[C'+ str(1) + '] ')

for i in range(loop):
	
	data = random.sample(numbers, nl)

	data.extend([10] * nr)

	for item in data:
		fw.write('%s ' % item)
	
	data = random.sample(numbers, nl)
	
	data.extend([20] * nr)

	for item in data:
		fw.write('%s ' % item)

	data = random.sample(numbers, nl)

	data.extend([30] * nr)

	
	for item in data:
		fw.write('%s ' % item)
	
	data = random.sample(numbers, nl)
	
	data.extend([40] * nr)

	for item in data:
		fw.write('%s ' % item)
	

	data = random.sample(numbers, nl)

	data.extend([50] * nr)

	
	for item in data:
		fw.write('%s ' % item)

	data = random.sample(numbers, nl)

	data.extend([60] * nr)

	
	for item in data:
		fw.write('%s ' % item)

	data = random.sample(numbers, nl)

	data.extend([70] * nr)
	
	for item in data:
		fw.write('%s ' % item)

	data = random.sample(numbers, nl)

	data.extend([80] * nr)
	
	for item in data:
		fw.write('%s ' % item)


	
fw.close()


