import mmap
import contextlib
import os
import sys
import glob

def fencep(folder_name, file_name, n):
	if not os.path.exists(folder_name + '/fp/'):
		os.makedirs(folder_name + '/fp/')

	f = open(folder_name + '/vbv/' + file_name)


	size = os.stat(folder_name + '/vbv/' + file_name).st_size
	fw = open( folder_name + '/fp/' + file_name[:-4] + '_' + 'fp.txt', 'w')

	r = size%9

	fence = []
	temp = 0
	fp = n

	with contextlib.closing(mmap.mmap(f.fileno(), 0, access=mmap.ACCESS_READ)) as m:
		i = 0
		while (m.tell() < (size-r-9)):
			v = m.tell()
			block = m.read(9)[:-1]
			if (block[0] == '[' or block[0] == ']'):
				fw.close()
				break
			elif (int(block[0]) == 1):
				temp += 1
				if (fp == temp):
					fw.write(str(fp) + ' ' + str(i+1) + '\n')
					fp += n


			else:
				temp += int(block[2:], 2)
				if (fp < temp):
					if((temp%n) != 0):
						fp = (int(temp/n) + 1) * n
					else:
						fp = temp
						fw.write(str(fp) + ' ' + str(i+1) + '\n')
						fp += n
			i += 1

	fw.close()






def fenceptr(folder_name, n):

	if not os.path.exists(folder_name + '/fp/'):
		os.makedirs(folder_name + '/fp/')

	for file in glob.glob(folder_name + '/vbv/' + '/*.txt'):
		head, tail = os.path.split(file)
		
		tail = tail[:-4]

		f = open(file)

		size = os.stat(file).st_size
		fw = open( folder_name + '/fp/' + tail + '_' + 'fp.txt', 'w')

		r = size%9

		fence = []
		temp = 0
		fp = n

		with contextlib.closing(mmap.mmap(f.fileno(), 0, access=mmap.ACCESS_READ)) as m:
			i = 0
			while (m.tell() < (size-r-9)):
				block = m.read(9)[:-1]
				if (block[0] == '[' or block[0] == ']'):
					fw.close()
					break

				elif (int(block[0]) == 1):
					temp += 1
					if (fp == temp):
						fw.write(str(fp) + ' ' + str(i+1) + '\n')
						fp += n


				else:
					temp += int(block[2:], 2)
					if (fp < temp):
						if((temp%n) != 0):
							fp = (int(temp/n) + 1) * n
						else:
							fp = temp
							fw.write(str(fp) + ' ' + str(i+1) + '\n')
							fp += n
				i += 1

		fw.close()


if __name__ == "__main__":
	fenceptr(sys.argv[1], int(sys.argv[2]))
