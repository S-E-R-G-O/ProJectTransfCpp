#include "Processing.h"
#include "TrackingBox.h"
using namespace cv;
using namespace std;

Processing::Processing(const string& fileName1, const string& fileName2) : isFrame(true)
{
	stream1.open(fileName1);
	if (!stream1.isOpened())
	{
		throw runtime_error("Could not open video stream");
	}

	stream2.open(fileName2);
	if (!stream1.isOpened())
	{
		throw runtime_error("Could not open video stream");
	}
}

Processing::~Processing()
{
	stream1.release();
	stream2.release();
	destroyAllWindows();
}

void Processing::detectedChanges()
{
	Mat frame1, frame2, grayFrame1;

	while (true)
	{
		stream1 >> frame1;
		stream2 >> frame2;

		if (frame1.empty() || frame2.empty())
		{
			cout << "Frame is empty" << endl;
			break;
		}
		hconcat(frame1, frame2, frame1);

		cvtColor(frame1, grayFrame1, COLOR_BGR2GRAY);

		if (isFrame)
		{
			previousFrame = grayFrame1;
			isFrame = false;
			continue;
		}
		processingFrame(frame1, grayFrame1);
		previousFrame = grayFrame1.clone();

		if (waitKey(10) == 27)
		{
			break;
		}
	}
}

void Processing::processingFrame(Mat& frame, Mat& grayFrame)
{
	Mat difference, thresh, dilated, frameBlur;

	absdiff(previousFrame, grayFrame, difference);

	threshold(difference, thresh, 20, 255, THRESH_BINARY);

	dilate(thresh, dilated, Mat(), Point(-1, -1), 4);

	GaussianBlur(dilated, frameBlur, Size(5, 5), 0, 0);

	vector<vector<Point>> contours;

	findContours(frameBlur, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	vector<TrackingBox> boxes = TrackingBox::createBoxes(contours);

	TrackingBox::drawBoxes(frame, boxes);



	imshow("Combined Video", frame);
	imshow("Masked Video", thresh);

}