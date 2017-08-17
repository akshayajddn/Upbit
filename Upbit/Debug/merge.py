import glob
import os
import time
import multiprocessing
from fp import fencep
import sys

N = 7

def merge(folder_name, file_name):

	vbv = folder_name + '/vbv/'
	ubv = folder_name + '/ubv/'

	inf = vbv + file_name + ".txt"
	outf = ubv + file_name + "u.txt"

	os.system('./merge_update ' + inf + ' ' + outf )
	os.system('./initializeub_update ' + folder_name + ' ' + file_name + '.txt')
	fencep(folder_name, file_name + ".txt", N)


if __name__ == "__main__":
	#os.system('g++ -Wall -o merge_update merge_update.cpp')
	#os.system('g++ -Wall -o initializeub_update initializeub_update.cpp')
	folder_name = sys.argv[1]


	# Without Multiprocessing
	# start = time.time()
	# for file in glob.glob(folder_name + '/vbv/' + '/*.txt'):
	# 	head, tail = os.path.split(file)
	# 	# tail = tail[:-4]
	# 	#print folder_name, tail
	# 	merge(folder_name, tail[:-4])

	# print time.time() - start


	# With Multiproecessing
	start = time.time()
	jobs = []
	for file in glob.glob(folder_name + '/vbv/' + '/*.txt'):
		head, tail = os.path.split(file)
		tail = tail[:-4]
		p = multiprocessing.Process(target=merge, args=(folder_name, tail))
		jobs.append(p)
		p.start()

	for proc in jobs:
 		proc.join()

 	#print time.time() - start
