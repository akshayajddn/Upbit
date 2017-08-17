import matplotlib.pyplot as plt
import numpy as np

index = np.arange(4)
bar_width = 0.25

# plt.subplot(2, 1, 1)
updated = [27.83, 22.12, 16.44, 16.43]
normal = [40.87, 25.57, 21.55, 21.67]

rects1 = plt.bar(index, updated, bar_width, color='r')
rects2 = plt.bar(index + bar_width, normal, bar_width, color='black') 


plt.xlabel('Threshold')
plt.ylabel('Time Taken(secs)')
plt.title('100 queries')
plt.xticks(index + bar_width, ('5', '10', '15', '20'))
plt.subplots_adjust(hspace = 0.5)


# plt.subplot(2, 1, 2)
# updated = [46.67, 33.20, 33.75, 33.106]
# normal = [49.03, 41.02, 38.37, 37.28]

# rects1 = plt.bar(index, updated, bar_width, color='r', label = 'updated')
# rects2 = plt.bar(index + bar_width, normal, bar_width, color='black', label = 'original') 


# plt.xlabel('Threshold')
# plt.ylabel('Time Taken(secs)')
# plt.title('200 queries')

# plt.xticks(index + bar_width, ('5', '10', '15', '20'))

plt.show()

