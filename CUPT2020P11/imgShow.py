import numpy as np
import cv2


data = np.loadtxt("Image.csv", dtype=np.int16, delimiter=',')
cv2.imwrite('img.jpg', data)
