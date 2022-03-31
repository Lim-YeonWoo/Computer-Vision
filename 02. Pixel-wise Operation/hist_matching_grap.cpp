#include "hist_func.h"

void hist_eq_func(Mat &input, G *trans_func, float *CDF);

int main()
{
	/*Step0. input이미지, reference이미지 등 준비*/
	Mat input = imread("input.jpg", CV_LOAD_IMAGE_COLOR);
	Mat input_gray;
	Mat reference = imread("reference.jpg", CV_LOAD_IMAGE_COLOR);
	Mat reference_gray;

	cvtColor(input, input_gray, CV_RGB2GRAY);		  // convert RGB to Grayscale
	cvtColor(reference, reference_gray, CV_RGB2GRAY); // convert RGB to Grayscale

	Mat matched = input_gray.clone();

	// PDF or transfer function txt files
	FILE *f_PDF;
	FILE *f_reference_PDF_gray;
	FILE *f_matched_PDF_gray;
	FILE *f_trans_func_matching;

	fopen_s(&f_PDF, "PDF.txt", "w+");
	fopen_s(&f_reference_PDF_gray, "reference_PDF_gray.txt", "w+");
	fopen_s(&f_matched_PDF_gray, "matched_PDF_gray.txt", "w+");
	fopen_s(&f_trans_func_matching, "trans_func_matching.txt", "w+");

	float *PDF = cal_PDF(input_gray);				// PDF of Input image(Grayscale) : [L]
	float *PDF_reference = cal_PDF(reference_gray); // PDF of Reference image(Grayscale) : [L]
	float *CDF1 = cal_CDF(input_gray);				// CDF of Input image(Grayscale) : [L]
	float *CDF2 = cal_CDF(reference_gray);			// CDF of Reference image(Grayscale) : [L]

	G trans_func_eq_T[L] = {0}; // transfer func T
	G trans_func_eq_G[L] = {0}; // transfer func G
	G trans_func[L] = {0};		// transfer func G-1(T(r))

	/* Step1. trans_func_eq_T구하기 */
	// r -> s, obtain the transfer function s = T(r), input이미지를 histo_eq
	hist_eq_func(input_gray, trans_func_eq_T, CDF1);

	/* Step2. trans_func_eq_G구하기 */
	// z -> s, obtain the transfer function s = G(z), reference이미지를 histo_eq
	hist_eq_func(reference_gray, trans_func_eq_G, CDF2);

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
			matched.at<G>(i, j) = trans_func[input_gray.at<G>(i, j)];

	/* Step5. 결과이미지, 1trans_func, 1histogram of the original image, 1histogram of the ouput image 를 출력*/
	float *matched_PDF_gray = cal_PDF(matched); // matched된 output이미지 PDF 구하기(grayscale)
	for (int i = 0; i < L; i++)
	{
		// write PDF
		fprintf(f_PDF, "%d\t%f\n", i, PDF[i]);
		fprintf(f_reference_PDF_gray, "%d\t%f\n", i, PDF_reference[i]);
		fprintf(f_matched_PDF_gray, "%d\t%f\n", i, matched_PDF_gray[i]);

		// write transfer functions
		fprintf(f_trans_func_matching, "%d\t%d\n", i, trans_func[i]);
	}

	// memory release
	free(PDF);
	free(PDF_reference);
	free(CDF1);
	free(CDF2);
	free(matched_PDF_gray);
	fclose(f_PDF);
	fclose(f_reference_PDF_gray);
	fclose(f_matched_PDF_gray);
	fclose(f_trans_func_matching);

	////////////////////// Show each image ///////////////////////

	namedWindow("Grayscale", WINDOW_AUTOSIZE);
	imshow("Grayscale", input_gray);

	namedWindow("Reference", WINDOW_AUTOSIZE);
	imshow("Reference", reference_gray);

	namedWindow("Matched", WINDOW_AUTOSIZE);
	imshow("Matched", matched);

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
