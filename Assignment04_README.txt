1. salt_and_pepper-median.cpp
	: input image, kernel size를 결정할 n, boundary processing을 결정할 opt를 입력하면,
          salt and pepper noise image를 만들고, 이를 median filtering으로 제거하는 함수이다.
	: the input image file "lena.jpg" should be under the project directory

	1) int main
		input: input image in matrix form
		input_gray: input image를 흑백으로 바꾼 matrix form
		noise_Gray: salt and pepper noise가 더해진 gray image
		noise_RGB: salt and pepper noise가 더해진 color image

	2) Mat Add_salt_pepper_Noise(const Mat input, float ps, float pp);
		: input 이미지, ps (percent of salt) pp (percent of pepper) 값을 입력받아, 
		  salt and pepper noise image를 return하는 함수
		intput: input image matrix
		ps: percent of salt noise
		pp: percent of pepper noise
		output: salt and pepper noise가 더해진 gray/color image

	3) Mat Salt_pepper_noise_removal_Gray(const Mat input, int n, const char* opt);
		intput: input image matrix
		n : filter kernel size를 결정. kernel사이즈가 [2*n+1][2*n+1]이 된다
		opt: Boundary process를 나타내는 것으로 zero-paddle, mirroring, adjustkernel 중 하나
		row: input image의 row
		col: input image의 col
		kernel_size: 주어진 n에 대해 2*n+1을 의미. kernel size를 의미
		tempa: mirroring 방법에서 사용할 변수로서, a의 임시값을 의미
		tempb: mirroring 방법에서 사용할 변수로서, b의 임시값을 의미
		kernel: kernel을 저장해둔 matrix
		median: median vaule의 index
		output: salt and pepper noise가 제거된 denoise image
		cnt: adjustkernel 방법에서 사용할 변수로서, 해당 (i,j)에서 kernel을 구했을 때, 이미지 영역안에 들어가는 부분의 개수를 의미한다.

	4) Mat Salt_pepper_noise_removal_RGB(const Mat input, int n, const char* opt);
		intput: input image matrix
		n : filter kernel size를 결정. kernel사이즈가 [2*n+1][2*n+1]이 된다
		opt: Boundary process를 나타내는 것으로 zero-paddle, mirroring, adjustkernel 중 하나
		row: input image의 row
		col: input image의 col
		kernel_size: 주어진 n에 대해 2*n+1을 의미. kernel size를 의미
		tempa: mirroring 방법에서 사용할 변수로서, a의 임시값을 의미
		tempb: mirroring 방법에서 사용할 변수로서, b의 임시값을 의미
		kernel: kernel을 저장해둔 matrix
		median: median vaule의 index
		output: salt and pepper noise가 제거된 denoise image
		cnt: adjustkernel 방법에서 사용할 변수로서, 해당 (i,j)에서 kernel을 구했을 때, 이미지 영역안에 들어가는 부분의 개수를 의미한다.

	
2. gaussian noise-gaussian.cpp
	: input 이미지, sigma t, sigma s, boundary processing을 결정하는 opt 값을 입력받아, 
          gaussian noise image를 만들고, gaussian noise를 gaussian filtering을 이용해 제거한 denoised image를 return하는 함수
	: the input image file "lena.jpg" should be under the project directory

	1) int main
		input: input image in matrix form
		input_gray: input image를 흑백으로 바꾼 matrix form
		noise_Gray: salt and pepper noise가 더해진 gray image
		noise_RGB: salt and pepper noise가 더해진 color image

	2) Mat Add_Gaussian_noise(const Mat input, double mean, double sigma);
		input: input image in matrix form
		mean: gaussian distribution에서 mean을 의미
		sigma: gaussian distribution에서 sigma를 의미
		NoiseArr: gaussian noise가 더해진 gray/color image

	3) Mat Gaussianfilter_Gray(const Mat input, int n, double sigma_t, double sigma_s, const char* opt);
		input: input image in matrix form	
		input_gray: input image를 gray로 변환한 것
		n: filter kernel size를 결정. kernel사이즈가 [2*n+1][2*n+1]이 된다
		sigmaT: w(s,t)를 구할 때 사용될 시그마T
		sigmaS: w(s,t)를 구할 때 사용될 시그마S
		kernel_size: 주어진 n에 대해 2*n+1을 의미. kernel size를 의미
		opt: Boundary process를 나타내는 것으로 zero-paddle, mirroring, adjustkernel 중 하나
		row: input image의 row
		col: input image의 col
		denom: m(s,t)에서의 분모
		tempa: mirroring 방법에서 사용할 변수로서, a의 임시값을 의미
		tempb: mirroring 방법에서 사용할 변수로서, b의 임시값을 의미
		kernel: kernel을 저장해둔 곳
		output: output image
		sum1: kernel window를 곱해 더한 값 (가중합)을 저장하는 변수
		sum2: adjustkernel에서의 분모로, 유효한 가중합을 저장해둔 것.

	4) Mat Gaussianfilter_RGB(const Mat input, int n, double sigma_t, double sigma_s, const char* opt);
		input: input image in matrix form	
		n: filter kernel size를 결정. kernel사이즈가 [2*n+1][2*n+1]이 된다
		sigmaT: w(s,t)를 구할 때 사용될 시그마T
		sigmaS: w(s,t)를 구할 때 사용될 시그마S
		kernel_size: 주어진 n에 대해 2*n+1을 의미. kernel size를 의미
		opt: Boundary process를 나타내는 것으로 zero-paddle, mirroring, adjustkernel 중 하나
		row: input image의 row
		col: input image의 col
		tempa: mirroring 방법에서 사용할 변수로서, a의 임시값을 의미
		tempb: mirroring 방법에서 사용할 변수로서, b의 임시값을 의미
		kernel: kernel을 저장해둔 곳
		kernelvalue: meanfilter에서는 kernel의 각 값이 같으므로 그 값을 저장해둔 것
		output: output image
		sum1_r: [0]에서의 kernel window를 곱해 더한 값 (가중합)을 저장하는 변수
		sum1_g: [1]에서의 kernel window를 곱해 더한 값 (가중합)을 저장하는 변수
		sum1_b: [2]에서의 kernel window를 곱해 더한 값 (가중합)을 저장하는 변수
		sum2: adjustkernel에서의 분모로, 유효한 가중합을 저장해둔 것.

3. gaussian noise-bilateral.cpp
	: input 이미지, sigma t, sigma s, sigma r, boundary processing을 결정하는 opt 값을 입력받아, 
	  gaussian noise image를 만들고, gaussian noise를 bilateral filtering을 이용해 제거한 denoised image를 return하는 함수
	: the input image file "lena.jpg" should be under the project directory

	1) int main
		input: input image in matrix form
		input_gray: input image를 흑백으로 바꾼 matrix form
		noise_Gray: salt and pepper noise가 더해진 gray image
		noise_RGB: salt and pepper noise가 더해진 color image

	2) Mat Add_Gaussian_noise(const Mat input, double mean, double sigma);
		input: input image in matrix form
		mean: gaussian distribution에서 mean을 의미
		sigma: gaussian distribution에서 sigma를 의미
		NoiseArr: gaussian noise가 더해진 gray/color image

	3) Mat Bilateralfilter_Gray(const Mat input, int n, double sigma_t, double sigma_s, double sigma_r, const char* opt);
		input: input image in matrix form	
		input_gray: input image를 gray로 변환한 것
		n: filter kernel size를 결정. kernel사이즈가 [2*n+1][2*n+1]이 된다
		sigmaT: w(s,t)를 구할 때 사용될 시그마T
		sigmaS: w(s,t)를 구할 때 사용될 시그마S
		kernel_size: 주어진 n에 대해 2*n+1을 의미. kernel size를 의미
		opt: Boundary process를 나타내는 것으로 zero-paddle, mirroring, adjustkernel 중 하나
		row: input image의 row
		col: input image의 col
		denom: m(s,t)에서의 분모
		tempa: mirroring 방법에서 사용할 변수로서, a의 임시값을 의미
		tempb: mirroring 방법에서 사용할 변수로서, b의 임시값을 의미
		kernel: kernel을 저장해둔 곳
		output: output image
		sum1: kernel window를 곱해 더한 값 (가중합)을 저장하는 변수
		sum2: adjustkernel에서의 분모로, 유효한 가중합을 저장해둔 것.
		value1: kernel값을 구할 때 중간과정의 계산식을 저장해두는 곳
		intensity_distance: kernel을 구할때 중간과정인 intensity_distance를 의미.

	4) Mat Bilateralfilter_RGB(const Mat input, int n, double sigma_t, double sigma_s, double sigma_r, const char* opt);
		input: input image in matrix form	
		n: filter kernel size를 결정. kernel사이즈가 [2*n+1][2*n+1]이 된다
		sigmaT: w(s,t)를 구할 때 사용될 시그마T
		sigmaS: w(s,t)를 구할 때 사용될 시그마S
		kernel_size: 주어진 n에 대해 2*n+1을 의미. kernel size를 의미
		opt: Boundary process를 나타내는 것으로 zero-paddle, mirroring, adjustkernel 중 하나
		row: input image의 row
		col: input image의 col
		denom: m(s,t)에서의 분모
		tempa: mirroring 방법에서 사용할 변수로서, a의 임시값을 의미
		tempb: mirroring 방법에서 사용할 변수로서, b의 임시값을 의미
		kernel: kernel을 저장해둔 곳
		kernelvalue: meanfilter에서는 kernel의 각 값이 같으므로 그 값을 저장해둔 것
		output: output image
		sum1_r: [0]에서의 kernel window를 곱해 더한 값 (가중합)을 저장하는 변수
		sum1_g: [1]에서의 kernel window를 곱해 더한 값 (가중합)을 저장하는 변수
		sum1_b: [2]에서의 kernel window를 곱해 더한 값 (가중합)을 저장하는 변수
		sum2: adjustkernel에서의 분모로, 유효한 가중합을 저장해둔 것.
		value1: kernel값을 구할 때 중간과정의 계산식을 저장해두는 곳.
		color_distance: kernel을 구할때 중간과정인 color_distance를 의미.
