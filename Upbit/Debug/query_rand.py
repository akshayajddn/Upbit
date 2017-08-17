import random
op1 = ['i', 'u', 'd', 'r']
op2 = ['u', 'r']
op3 = [10, 20, 30, 30, 40, 50, 60, 70, 80]
op4 = ['C0','C1']

prev = 1
size = 7000000*2

# i c1 10 c2 20
# d 123
# r c1 123
# u c1 123 10


# run python query_rand.py > queries.txt


for i in xrange(100): #no of queries is 100
	c = random.sample(op2, 1)

	if c[0] == 'd':
		print c[0], random.sample(xrange(prev , size), 1)[0] # no of rows = 201
	elif c[0] == 'r':
		print c[0], random.sample(op4, 1)[0], random.sample(xrange(prev, size), 1)[0]
	elif c[0] == 'u':
		print c[0], random.sample(op4, 1)[0], random.sample(xrange(prev, size), 1)[0], random.sample(op3, 1)[0]
	else:
		print c[0], 'C0', random.sample(op3, 1)[0], 'C1', random.sample(op3, 1)[0]
