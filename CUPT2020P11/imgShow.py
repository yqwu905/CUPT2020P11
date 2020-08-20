import numpy as np
import cv2

num = 4
data = np.loadtxt("Image{}.csv".format(num), dtype=np.int16, delimiter=',')
cv2.imwrite('img{}.jpg'.format(num), data)
