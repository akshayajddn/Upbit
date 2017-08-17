import matplotlib.pyplot as plt
import numpy as np

m1 = [19.01, 20.56, 20.20, 20.01]
m2 = [42.93, 42.34, 45.26, 43.02]
m3 = [59.20, 49.396, 62.32, 60.58]
m4 = [112.90, 107.40, 112.01, 104.40]

th = [1.5, 1.75, 2.0, 2.25]
index = np.arange(4)


plt.plot(m4, label = '500')
plt.plot(m3, label = '300')
plt.plot(m2, label = '200')
plt.plot(m1, label = '100')


plt.xticks(index, ('1.5', '1.75', '2', '2.25'))


# plt.axis([1.5, 2.25, 0, 180])
plt.xlabel('Threshold')
plt.ylabel('Time taken(secs)')
plt.title('Varying Secondary Threshold')
plt.legend()
plt.show()