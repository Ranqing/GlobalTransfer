#include "function.h"

void GlobalColorTransfer(Mat reference, Mat source, Mat& result)
{
	Mat lab_refence, lab_source;
	cvtColor(reference, lab_refence, CV_BGR2Lab);
	cvtColor(source, lab_source, CV_BGR2Lab);

	Scalar refmean, refstddv;
	Scalar srcmean, srcstddv;
	meanStdDev(lab_refence, refmean, refstddv);
	meanStdDev(lab_source, srcmean, srcstddv);

	double Lfactor = refstddv.val[0] / srcstddv.val[0];
	double Afactor = refstddv.val[1] / srcstddv.val[1];
	double Bfactor = refstddv.val[2] / srcstddv.val[2];

	cout << "refmean: " << refmean << endl;
	cout << "srcmean: " << srcmean << endl;
	cout << Lfactor << ' ' << Afactor << ' ' << Bfactor << endl;

	int width = reference.cols;
	int height = reference.rows;

	Mat lab_result(height, width, CV_8UC3);

	for (int y = 0; y < height; ++ y)
	{
		for (int x = 0; x < width; ++ x)
		{
			double transferL = refmean.val[0] + Lfactor * (lab_source.at<Vec3b>(y,x)[0] - srcmean.val[0]);
			double transferA = refmean.val[1] + Afactor * (lab_source.at<Vec3b>(y,x)[1] - srcmean.val[1]);
			double transferB = refmean.val[2] + Bfactor * (lab_source.at<Vec3b>(y,x)[2] - srcmean.val[2]);

			lab_result.at<Vec3b>(y,x)[0] = min(max(0.0, transferL), 255.0);
			lab_result.at<Vec3b>(y,x)[1] = min(max(0.0, transferA), 255.0);
			lab_result.at<Vec3b>(y,x)[2] = min(max(0.0, transferB), 255.0);
		}
	}

	cvtColor(lab_result, result, CV_Lab2BGR);
}