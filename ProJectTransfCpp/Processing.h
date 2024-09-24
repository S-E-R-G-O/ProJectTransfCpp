#ifndef PROCESSING_H
#define PROCESSING_H
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


class Processing
{
public:

	Processing(const string& fileName1, const string& fileName2);

	~Processing();

	void detectedChanges();

private:
	VideoCapture stream1;
	VideoCapture stream2;
	Mat previousFrame;
	bool isFrame;

	void processingFrame(Mat& frame, Mat& grayFrame);

};




#endif 