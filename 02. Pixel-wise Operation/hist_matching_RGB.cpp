#include "hist_func.h"

void hist_eq_func(Mat &input, G *trans_func, float *CDF);

int main()
{
	/*Step0. input이미지, reference이미지 등 준비*/
	Mat input = imread("input.jpg", CV_LOAD_IMAGE_COLOR);
	Mat reference = imread("reference.jpg", CV_LOAD_IMAGE_COLOR);

	/*Step1. input, reference RGB > YUV 로 변환 후 Y만 추출*/
	Mat input_YUV; //여기에 최종 matchedRGB저장할 거임.
	Mat reference_YUV;

	cvtColor(input, input_YUV, CV_RGB2YUV);			// RGB -> YUV
	cvtColor(reference, reference_YUV, CV_RGB2YUV); // RGB -> YUV

	// [input] split each channel(Y, U, V)
	Mat input_channels[3];
	split(input_YUV, input_channels);
	Mat input_Y = input_channels[0];

	// [reference] each channel(Y, U, V)
	Mat reference_channels[3];
	split(reference_YUV, reference_channels);
	Mat reference_Y = reference_channels[0];

	// PDF or transfer function txt files
	FILE *f_PDF;
	FILE *f_reference_PDF_RGB;
	FILE *f_matched_PDF_RGB;
	FILE *f_trans_func_matching;

	fopen_s(&f_PDF, "PDF.txt", "w+");
	fopen_s(&f_reference_PDF_RGB, "reference_PDF_RGB.txt", "w+");
	fopen_s(&f_matched_PDF_RGB, "matched_PDF_RGB.txt", "w+");
	fopen_s(&f_trans_func_matching, "trans_func_matching.txt", "w+");

	float **PDF = cal_PDF_RGB(input);				// PDF of Input image(RGB) : [L][3]
	float **PDF_reference = cal_PDF_RGB(reference); // PDF of Reference image(RGB) : [L][3]
	float *CDF1 = cal_CDF(input_Y);					// CDF of Input image(Grayscale) : [L]
	float *CDF2 = cal_CDF(reference_Y);				// CDF of Reference image(Grayscale) : [L]

	G trans_func_eq_T[L] = {0}; // transfer func T
	G trans_func_eq_G[L] = {0}; // transfer func G
	G trans_func[L] = {0};		// transfer func G-1(T(r))

	/* Step2-1. trans_func_eq_T구하기 */
	// r -> s, obtain the transfer function s = T(r), input이미지를 histo_eq
	hist_eq_func(input_Y, trans_func_eq_T, CDF1);

	/* Step2-2. trans_func_eq_G구하기 */
	// z -> s, obtain the transfer function s = G(z), reference이미지를 histo_eq
	hist_eq_func(reference_Y, trans_func_eq_G, CDF2);

	/* Step3. G의 역함수 구하기, trans_func구하기*/
	// G가 엄밀 단조증가 함수가 아니므로, 역변환 함수가 유일하지 않아서 모호성 문제가 생긴다.
	// 이를 해결하기 위해, T(ri)에 대해 G(z)들과의 차를 구해서, 가장 작은 diff를 가질때, ri > z 로 가게 해준다.
	for (int i = 0; i < L; i++)
	{
		int diff_min_idx = -1;
		int diff_min = L;
		for (int j = 0; j < L; j++)
		{
			if (diff_min > abs(trans_func_eq_T[i] - trans_func_eq_G[j]))
			{
				diff_min = abs(trans_func_eq_T[i] - trans_func_eq_G[j]); // diff_min 갱신
				diff_min_idx = j;										 // diff_min_idx 갱신
			}
		}
		trans_func[i] = diff_min_idx;
	}

	/* Step4. step3에서 찾은 trans_func을 이용해 매핑, histogram matching*/
	for (int i = 0; i < input.rows; i++)
		for (int j = 0; j < input.cols; j++)
			input_Y.at<G>(i, j) = trans_func[input_Y.at<G>(i, j)];

	/* Step5. 다시 YUV합치고, RGB로 바꿔주기*/
	merge(input_channels, 3, input_YUV);		// merge Y, U, V channels
	cvtColor(input_YUV, input_YUV, CV_YUV2RGB); // YUV -> RGB (use "CV_YUV2RGB" flag)

	/* Step6. 결과이미지, 1trans_func, 3histogram of the original image, 3histogram of the ouput image 를 출력*/
	float **PDF_matched = cal_PDF_RGB(input_YUV); // matched된 output이미지 PDF 구하기

	// write PDF (이미지3개에 대해, RGB 각각 PDF구하기)
	for (int j = 0; j < 3; j++)
	{
		fprintf(f_PDF, "PDF for %d \n", j);
		fprintf(f_reference_PDF_RGB, "PDF for %d \n", j);
		fprintf(f_matched_PDF_RGB, "PDF for %d \n", j);

		for (int i = 0; i < L; i++)
		{
			fprintf(f_PDF, "%d\t%f\n", i, PDF[i][j]);
			fprintf(f_reference_PDF_RGB, "%d\t%f\n", i, PDF_reference[i][j]);
			fprintf(f_matched_PDF_RGB, "%d\t%f\n", i, PDF_matched[i][j]);
		}

		fprintf(f_PDF, "\n");
		fprintf(f_reference_PDF_RGB, "\n");
		fprintf(f_matched_PDF_RGB, "\n");
	}

	// write transfer functions
	for (int i = 0; i < L; i++)
	{
		fprintf(f_trans_func_matching, "%d\t%d\n", i, trans_func[i]);
	}

	// memory release
	free(PDF);
	free(PDF_reference);
	free(CDF1);
	free(CDF2);
	free(PDF_matched);
	fclose(f_PDF);
	fclose(f_reference_PDF_RGB);
	fclose(f_matched_PDF_RGB);
	fclose(f_trans_func_matching);

	////////////////////// Show each image ///////////////////////

	namedWindow("RGB", WINDOW_AUTOSIZE);
	imshow("RGB", input);

	namedWindow("Reference", WINDOW_AUTOSIZE);
	imshow("Reference", reference);

	namedWindow("Matched", WINDOW_AUTOSIZE);
	imshow("Matched", input_YUV);

	//////////////////////////////////////////////////////////////

	waitKey(0);

	return 0;
}

// histogram equalization _ compute transfer function
void hist_eq_func(Mat &input, G *trans_func, float *CDF)
{
	for (int i = 0; i < L; i++)
		trans_func[i] = (G)((L - 1) * CDF[i]);
}
