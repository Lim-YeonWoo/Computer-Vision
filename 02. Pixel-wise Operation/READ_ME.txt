1. hist_func.h
- Purpose of this code
	grayscale인지, RGB인지 판단해, 간단하게 타입 명시해주기. ("G" for GrayScale Image, "C" for Color Image)
	generate PDF for single channel image
	generate PDF for color image
	generate CDF for single channel image
	generate CDF for color image

2. hist_strecthing.cpp
- Purpose of this code
	컬러이미지와 원하는 stretching점들을 넣어주면,
	흑백이미지로 변환하고, 
	주어진 stretching점에 맞게 stretching func을 구해, 이미지의 contrast를 높여 출력하는 코드.
- How to run this code
	원하는 색깔이미지를 "input.jpg"로 해당파일과 같은 디렉토리에 두고 실행시킨다.

3. hist_eq.cpp
- Purpose of this code
	컬러이미지를 넣어주면, 흑백이미지로 변환해, 자동으로 histogram equalization func을 구해, 이미지의 contrast를 높여 출력하는 코드.
- How to run this code
	원하는 색깔이미지를 "input.jpg"로 해당파일과 같은 디렉토리에 두고 실행시킨다.

4. hist_eq_RGB.cpp
- Purpose of this code
	컬러이미지를 넣어주면, 각각 RGB마다 독립적으로 histogram equalization func을 구한 후, 그 RGB값을 가지는 이미지를 출력하는 코드. (histogram equalization for color image할 때 옳지 못한 방법임을 알 수 있음)
- How to run this code
	원하는 색깔이미지를 "input.jpg"로 해당파일과 같은 디렉토리에 두고 실행시킨다.

5. hist_eq_YUV.cpp
- Purpose of this code
	컬러이미지를 넣어주면, RGB>YUV 한 후, Y만 분리해 histogram equalization을 실행 한 후, 다시 YUV를 합치고, YUV > RGB로 바꿔서, 이미지의 contrast를 높인 결과물을 출력하는 코드.
	histogram equalization for color image할 때 옳은 방법임을 알 수 있음.
- How to run this code
	원하는 색깔이미지를 "input.jpg"로 해당파일과 같은 디렉토리에 두고 실행시킨다.


6. hist_matching_gray.cpp
- Purpose of this code
	컬러이미지와 reference 이미지를 넣어주면, 두 이미지를 흑백이미지로 변환해, 자동으로 reference image의 histogram과 유사하게 주어진 이미지의 histogram을 contrast가 높도록 변환해 출력하는 코드.
- How to run this code
	[원하는 색깔이미지]를 "input.jpg"로, [참고 색깔이미지]를 "reference.jpg"로 해당파일과 같은 디렉토리에 두고 실행시킨다.

7. hist_matching_RGB.cpp
- Purpose of this code
	컬러이미지와 reference 이미지를 넣어주면, 자동으로 reference image의 histogram과 유사하게 주어진 이미지의 histogram을 contrast가 높도록 변환해 출력하는 코드.
- How to run this code
	[원하는 색깔이미지]를 "input.jpg"로, [참고 색깔이미지]를 "reference.jpg"로 해당파일과 같은 디렉토리에 두고 실행시킨다.
