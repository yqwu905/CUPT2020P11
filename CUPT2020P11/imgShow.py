import numpy as np
import cv2


data = np.loadtxt("Image2.csv", dtype=np.int16, delimiter=',')
cv2.imwrite('img2.jpg', data)
