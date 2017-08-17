import sys
import mmap
import contextlib
import os
import time
import glob

import multiprocessing
from multiprocessing import Manager

# to read perticular row bit from 
def getbit(folder_name, file_name, num):

	#print 'getbit',
	fc = open(folder_name + '/ubv/' + file_name +'.txt')

	if(num%7 == 0):
		n = num/7
		r = 7
	else:
		n = num/7 + 1
		r = num%7

	with contextlib.closing(mmap.mmap(fc.fileno(), 0, access=mmap.ACCESS_READ)) as m:
		temp = n

		size = os.stat(folder_name + '/ubv/' + file_name +'.txt').st_size
		rem = size%9

		if ((m.tell() + 9) == (size-rem)):
			#print 'start',
			block = m.read(9)[:-1]
			if(int(block[0]) == 1 and temp == 1):
				nbits = int(m.read(rem)[1:-1])
			 	if (r <= nbits):
			 		#block = block[::-1]
			 		#print 'values for row ', block[r-1]
			 		return int(block[7-nbits:][r])
			 	else:
			 		#print 'Row is out of limit'
			 		return -1
			else:
				tp = int(block[2:], 2)
				#print temp, tp
				if(temp <= tp):
			 		#print 'value for row is fill bit', block[1]
			 		return int(block[1])
			 	else:
			 		#print 'Row is out of limit'
			 		return -1
		else:
			i = 0
			fc = 0
			bit = 0
			#print '2nd'

			while ((temp > 0) and (m.tell() < (size-rem-9))):

				#print 'middle',
				block = m.read(9)[:-1]
				if(int(block[0]) == 1):
					fc = 1
					temp = temp - 1
				else:
					fc = 0
					bit = int(block[1])
					temp = temp - int(block[2:], 2)
				i += 1

			if (temp > 0):
				#print 'end',
				block = m.read(9)[:-1]
				if(int(block[0]) == 1 and temp == 1):
					nbits = int(m.read(rem)[1:-2])
				 	if (r <= nbits):
				 		#block = block[::-1]
				 		#print 'values for row ', block[r-1]
				 		return int(block[7-nbits:][r])
				 	else:
				 		#print 'Row is out of limit'
				 		return -1
				else:
					tp = int(block[2:], 2)
					if(int(block[0]) == 0 and temp <= tp):
				 		#print 'value for row is fill bit', block[1]
				 		return int(block[1])
				 	else:
				 		#print 'Row is out of limit'
				 		return -1

		if(fc == 0 and temp <= 0):
				#print 'fill ', bit
				return bit
		elif(temp == 0):
				m.seek((i-1)*9)
				block = m.read(9)[:-1]
				#print 'literal ', block, block[r]
				return int(block[r])
		else:
			#print 'Row is out of limit'
			return -1

def nicefencep(folder_name, file_name, num, v_dict):
	#print 'fp',
	fc = open(folder_name + '/vbv/' + file_name +'.txt')
	fp = open(folder_name + '/fp/' + file_name + '_fp.txt')

	if(num%7 == 0):
		n = num/7
		r = 7
	else:
		n = num/7 + 1
		r = num%7

	prev = 1
	res = 1

	p = 1
	offset = 1
	count = 0
	# checking if the we went through the while fencepointer file without finding and any match, so we will use last block as reference.
	check = 0
	for line in fp:
		next1, res1 = line[:-1].split(' ')
		next1 = int(next1)
		res1 = int(res1)
		if (n == next1):
			p = next1
			offset = res1
			check += 1
			break
		elif (n < next1):
			p = prev
			offset = res
			check += 1
			break
		else:
			prev = next1
			res = res1
			count += 1

	if (check == 0):
		p = prev
		offset = res

	#print 'offset', p, offset, count

	with contextlib.closing(mmap.mmap(fc.fileno(), 0, access=mmap.ACCESS_READ)) as m:
		temp = n - p

		size = os.stat(folder_name + '/vbv/' + file_name +'.txt').st_size
		rem = size%9

		m.seek(9*(offset-1))
		block = m.read(9)[:-1]

		tp = 0
		if(int(block[0]) == 0):
			tp = int(block[2:], 2)

		val = int(file_name.split('_')[-1])
		ub = getbit( folder_name, file_name + 'u', num)

		if ub == -1:
			return -1
		#print m.tell(), size

		if (m.tell() == (size-rem)):
			#print tp, temp 
			if(int(block[0]) == 1 and temp == 0):
				v_dict[val] = int(block[7-nbits:][r]) ^ ub
			elif(tp > temp):
				v_dict[val] = int(block[1]) ^ ub
			else:
				v_dict[val] = -1
			return
		
		else:
			# print tp, temp
			if (tp != 0 and tp > temp):
				#print 'a' 
				v_dict[val] = int(block[1]) ^ ub
				return

			if(temp == 0 and int(block[0]) == 1):
				#print 'b'
				v_dict[val] = int(block[r]) ^ ub
				return
			elif((m.tell() + 9) == (size-rem)):
				#print 'start',
				block = m.read(9)[:-1]
				if(int(block[0]) == 1 and temp == 1):
					nbits = int(m.read(rem)[1:-1])
				 	if (r <= nbits):
				 		#block = block[::-1]
				 		#print 'values for row ', block[r-1]
				 		v_dict[val] = int(block[7-nbits:][r]) ^ ub
				 	else:
				 		#print 'Row is out of limit'
				 		v_dict[val] = -1
				else:
					tp = int(block[2:], 2)
					#print temp, tp
					if(temp <= tp):
				 		#print 'value for row is fill bit', block[1]
				 		v_dict[val] = int(block[1]) ^ ub
				 	else:
				 		#print 'Row is out of limit'
				 		v_dict[val] = -1
				return
			else:
				i = 0
				fc = 0
				bit = 0
				#print '2nd'

				while ((temp > 0) and (m.tell() < (size-rem-9))):
					#print 'middle',
					block = m.read(9)[:-1]
					if(int(block[0]) == 1):
						fc = 1
						temp = temp - 1
					else:
						fc = 0
						bit = int(block[1])
						temp = temp - int(block[2:], 2)
					i += 1

				if (temp > 0):
					#print 'end',
					block = m.read(9)[:-1]
					if(int(block[0]) == 1 and temp == 1):

						nbits = int(m.read(rem)[1:-1])
					 	if (r <= nbits):
					 		#block = block[::-1]
					 		#print 'values for row ', block[r-1]
					 		v_dict[val] = int(block[7-nbits:][r]) ^ ub
					 	else:
					 		#print 'Row is out of limit'
					 		v_dict[val] = -1
					 	return

					else:
						tp = int(block[2:], 2)
						if(int(block[0]) == 0 and temp <= tp):
					 		#print 'value for row is fill bit', block[1]
					 		v_dict[val] = int(block[1]) ^ ub
					 	else:
					 		#print 'Row is out of limit'
					 		v_dict[val] = -1
					 	return


		if(fc == 0 and temp <= 0):
				#print 'fill ', bit
				v_dict[val] = bit ^ ub
		elif(temp == 0):
				m.seek((i+offset-1)*9)
				block = m.read(9)[:-1]
				#print 'literal ', block, block[r]
				v_dict[val] = int(block[r]) ^ ub
		else:
			#print 'Row is out of limit'
			v_dict[val] = -1


	
def threadfenceptr(folder_name, num):
	#start = time.time()

	#dict = {}
	#for file in glob.glob(folder_name + '/vbv/' + '/*.txt'):
	#	head, tail = os.path.split(file)
	#	tail = tail[:-4]
	#	nicefencep(folder_name, tail, num, dict)

	#print time.time() - start

	#start = time.time()

	manager = Manager()
	return_dict = manager.dict()
	jobs = []
	for file in glob.glob(folder_name + '/vbv/' + '/*.txt'):
		head, tail = os.path.split(file)
		tail = tail[:-4]
 		p = multiprocessing.Process(target=nicefencep, args=(folder_name, tail, num, return_dict))
 		jobs.append(p)
 		p.start()

	for proc in jobs:
 		proc.join()

	#print time.time() - start
	
	#print dict, return_dict

	# for key, val in dict.iteritems():
	# 	if val == 1:
	# 		print key

	for key, val in return_dict.items():
		if val == 1:
			return key

	return -1


if __name__ == "__main__":
	# start = time.time()
	# n = 40000
	# for i in range(1, 5000):
	# 	getbit(sys.argv[1], int(n+i))

	# print time.time() - start

	# start = time.time()

	# for i in range(1, 5000):	

	# 	nicefencep(sys.argv[1], int(n+i))

	# print time.time() - start

	# for i in range(1, 11):
	# 	print nicefenceptr('data', i)

	#res = threadfenceptr(sys.argv[1], int(sys.argv[2]))
	
	res = threadfenceptr(sys.argv[1], int(sys.argv[2]))
	print res


	# for j in range(0, 43):
	# 	for i in range(j*7 + 1, (j+1)*7 + 1):
	# 		dict = {}
	# 		nicefencep('c1', 'c1_10', i, dict)
	# 		print dict[10],
	# 	print ' end of ', j

	# print 'results'
	# print dict
	
	# print getbit('c1', 'c1_40u', 10)


	# dict = {}
	# r = []
	# for i in range(1, 2):
	# 	r.append(nicefencep('c1', 'bcd', 7, dict))
	# 	r.append(nicefencep('c1', 'bcd', 14, dict))
	# 	r.append(nicefencep('c1', 'bcd', 21, dict))
	# 	r.append(nicefencep('c1', 'bcd', 38, dict))

	# print r
	# for i in range(1, 30):
	#  	nicefencep('test1', 'sample_10', i, v_dict)
