// [rotate.cpp]
// nearest-neighbor(NN) interpolation과 bilinear interpolation을 구현해, 이미지를 rotate시키는 코드를 작성해보자.
// 2071042 컴퓨터공학과 임연우
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

template <typename T>
Mat myrotate(const Mat input, float angle, const char *opt);

int main()
{
	Mat input, rotated;

	// Read each image
	input = imread("lena.jpg");

	// Check for invalid input
	if (!input.data)
	{
		std::cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	// original image
	namedWindow("image");
	imshow("image", input);

	rotated = myrotate<Vec3b>(input, 45, "bilinear");

	// rotated image
	namedWindow("rotated");
	imshow("rotated", rotated);

	waitKey(0);

	return 0;
}

template <typename T>
Mat myrotate(const Mat input, float angle, const char *opt)
{
	//주어진 input matrix의 row, col을 저장
	int row = input.rows;
	int col = input.cols;

	//주어진 angle을 라디안으로 변환(육십분법>호도법)
	float radian = angle * CV_PI / 180;

	// rotation시켰을때의 크기를 계산 (by rotation matrix)
	float sq_row = ceil(row * sin(radian) + col * cos(radian));
	float sq_col = ceil(col * sin(radian) + row * cos(radian));

	//구한 크기만큼의 영행렬을 생성.
	Mat output = Mat::zeros(sq_row, sq_col, input.type());

	for (int i = 0; i < sq_row; i++)
	{
		for (int j = 0; j < sq_col; j++)
		{
			// [1] inverse wraping
			float x = (j - sq_col / 2) * cos(radian) - (i - sq_row / 2) * sin(radian) + col / 2; // center를 고려해 rotate해야하기에, translation.
			float y = (j - sq_col / 2) * sin(radian) + (i - sq_row / 2) * cos(radian) + row / 2;

			// [2] interpolation
			if ((y >= 0) && (y <= (row - 1)) && (x >= 0) && (x <= (col - 1)))
			{
				if (!strcmp(opt, "nearest"))
				{ // [2-1] NN interpolation
					output.at<Vec3b>(i, j) = input.at<Vec3b>(y, x);
				}
				else if (!strcmp(opt, "bilinear"))
				{ // [2-2] bilinear interpolation
					float y1 = floor(y);
					float y2 = ceil(y);
					float x1 = floor(x);
					float x2 = ceil(x);

					float mu = y - y1;
					float lambda = x - x1;

					output.at<Vec3b>(i, j) = lambda * (mu * input.at<Vec3b>(y2, x2) + (1 - mu) * input.at<Vec3b>(y1, x2)) + (1 - lambda) * (mu * input.at<Vec3b>(y2, x1) + (1 - mu) * input.at<Vec3b>(y1, x1));
				}
			}
		}
	}

	return output;
}
