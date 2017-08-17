
# coding: utf-8

# In[37]:

import numpy as np
import os

# In[38]:
name = 'sample_new'
f = open(name + '.txt', 'r')
# change direc to other directory to customize it
direc = name + '/'
if not os.path.exists(direc):
    os.makedirs(direc)

for line in f:
    d = line.split(' ')
    
    #create filename.txt where filename is column name

    filename = direc + str(d[0][1:-1])
    f1 = open(filename + '.txt', 'w')
    a = np.array(d[1:-1], dtype='int')
    u = np.unique(a)
    
    for item in u:
        
        name = '[' + str(item) + '] '
        f1.write(name)
        for i in a:
            if (i == item):
                f1.write('1 ')
            else:
                f1.write('0 ')
        f1.write('\n')
    
    f1.close()
    
f.close()

