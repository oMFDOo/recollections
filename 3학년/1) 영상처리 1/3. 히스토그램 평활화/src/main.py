import numpy as np
import matplotlib.pylab as pylab
import matplotlib.image as mpimg

# Normalized histogram을 위한 확률 분포 함수
def imhist(im):
   # 이미지의 행, 열 크기값 저장
	m, n = im.shape
   # 연산의 전체 영역 지정
	h = [0.0] * 256
   # 전체 픽셀을 돌며 특정 밝기값(rk)을 갖는 수(nk)를 구하는 과정
	for i in range(m):
		for j in range(n):
			h[im[i, j]]+=1 # 밝기값을 인덱스로 사용해 빈도 값 증가
   # pr(rk) = nk / M*N , 전체 값을 표준화 함으로 0~1의 값을 갖도록 함
	return np.array(h)/(m*n)

# 누적분포함수(CDF)를 구하는 함수
def cumsum(h):
	# 리스트의 끝까지 확률분포 값을 더해 누적분포합을 반환
	return [sum(h[:i+1]) for i in range(len(h))]

# 히스토그램 평활화 함수
def histeq(im):
	# 히스토그램 계산을 통한 PDF값 생성
	h = imhist(im)
   # 누적 분포함수(CDF)를 배열에 담음
	cdf = np.array(cumsum(h))
   # 수식(T(r))을 통해 히스토그램 변환 값(s)을 찾는다. 
   # 최근접 상수로 변환하기 위한 정수화도  포함한다.
	sk = np.uint8(255 * cdf)
   # PDF 행렬  크기를 s1, s2에 담는다.
	s1, s2 = im.shape
   # 0으로 가득 채운 배열 생성
	Y = np.zeros_like(im)
	# 전체 픽셀을 돌며 CDF를 이용한 히스토그램 매칭값 저장
	for i in range(0, s1):
		for j in range(0, s2):
          # 평활화 한 값과 원본이미지가 매칭되는 지점을 저장
			Y[i, j] = sk[im[i, j]] # 
   # 변환값을 적용한 히스토그램을 H에 저장한다
	H = imhist(Y)
   # 변환 이미지, 원본 히스토그램, 변환 히스토그램, 변환함수를 반환한다.
	return Y , h, H, sk
  
#이미지를 불러오고 255크기로 맵핑을 해준뒤 정수화 시킨다.
img = np.uint8(mpimg.imread('../img/beans_g.png')*255.0)

# R, G, B, A 채널에 대해 grayscale로 변환한다.
img = np.uint8((0.2126* img[:,:,0]) + \
  		np.uint8(0.7152 * img[:,:,1]) +\
			 np.uint8(0.0722 * img[:,:,2]))


# 변환 이미지, 원본 히스토그램, 변환 히스토그램, 변환함수를 반환한다.
new_img, h, new_h, sk = histeq(img)

# 원본 이미지를  보여준다.
pylab.subplot(121) # 위치설정
pylab.title('original image') # 제목표기
# 출력값이 현재 데이터와 맞도록 vmin, vmax를 이용해 값 범위 조정 후 출력
pylab.imshow(img, cmap='gray', vmin=0, vmax=255), pylab.axis('off')

# 평활화 이미지를 보여준다.
pylab.subplot(122) # 위치설정
pylab.title('equalized image') # 제목표기
# 출력값이 현재 데이터와 맞도록 vmin, vmax를 이용해 값 범위 조정 후 출력
pylab.imshow(new_img, cmap='gray', vmin=0, vmax=255), pylab.axis('off')


fig = pylab.figure(figsize=(15, 5)) # 출력 사이즈 설정
fig.add_subplot(131) # 위치설정
pylab.plot(h) # 원본 그래프 그리기
pylab.title('Original histogram') # 제목표기

fig.add_subplot(132) # 위치설정
pylab.plot(new_h) # 평활화 그래프 그리기
pylab.title('New histogram') # 제목표기

fig.add_subplot(133) # 위치설정
pylab.plot(sk) # CDF 그래프 그리기
pylab.title('Transfer function') # 제목표기

pylab.show() # 그리기
