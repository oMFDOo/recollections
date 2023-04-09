import cv2
import numpy.fft as fp
import numpy as np 
import matplotlib.pyplot as pylab
from skimage.io import imread
from skimage.color import rgb2gray

read_img = imread('../img/parrot.jpg')
cmap_lst = ["Blue", "Green", "Red"]
img_arr = cv2.split(read_img)
color_arr = []

for i in range(0, 3) :
  pylab.subplot(1,3,i+1), pylab.imshow(np.clip(img_arr[i],0,255))
  pylab.title('Split Channel ' + cmap_lst[i], size=10)

for i in range(0, 3):
  im1 = rgb2gray(img_arr[i])
  pylab.figure(figsize=(12,10))
  freq1 = fp.fft2(im1)
  im1_ = fp.ifft2(freq1).real
  pylab.subplot(4,4,1), pylab.imshow(im1)
  pylab.title('Original Image - ' + cmap_lst[i], size=12) 
  pylab.subplot(4,4,2), pylab.imshow(20*np.log10( 0.01 + np.abs(fp.fftshift(freq1))))
  pylab.title('FFT Spectrum Maginitude', size=12)
  pylab.subplot(4,4,3), pylab.imshow(np.angle(fp.fftshift(freq1)))
  pylab.title('FFT Phase', size=12)
  pylab.subplot(4,4,4), pylab.imshow(np.clip(im1_,0,255))
  pylab.title('Reconstructed Image', size=12)
  pylab.show()
  color_arr.append(np.clip(im1_,0,255))
 

merge_img =cv2.merge([color_arr[0], color_arr[1], color_arr[2]])
merge_img = merge_img.astype(np.int64)
pylab.subplot(1,1,1), pylab.imshow(np.clip(merge_img, 0, 255))
pylab.title('Result2', size=20)

