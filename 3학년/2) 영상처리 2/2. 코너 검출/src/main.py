image = imread('../images/4.png') # RGB image
image_harris = image.copy()
image_gray = rgb2gray(image)

coordinates = corner_harris(image_gray, k =0.00001)
image_harris[coordinates>0.01*coordinates.max()]=[255,0,0,255]
#image_harris[coordinates>0.01*coordinates.max()]=[255,0,0]

corner_coordinates = corner_peaks(coordinates, min_distance=15, threshold_rel=0.0001)
coordinates_subpix = corner_subpix(image_gray, corner_coordinates, window_size=11)

pylab.figure(figsize=(40,20))
pylab.subplot(211), pylab.imshow(image_harris), pylab.axis('off')
pylab.subplot(212), pylab.imshow(image, interpolation='nearest')
pylab.plot(corner_coordinates[:, 1], corner_coordinates[:, 0], 'bo', markersize=5)
pylab.plot(coordinates_subpix[:, 1], coordinates_subpix[:, 0], 'r+', markersize=10), pylab.axis('off')
pylab.tight_layout(), pylab.show()