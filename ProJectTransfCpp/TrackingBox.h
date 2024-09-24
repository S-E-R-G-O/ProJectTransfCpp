#ifndef TRK_BOX
#define TRK_BOX

#include <opencv2/opencv.hpp>
#include <vector>

class TrackingBox {
public:
    static cv::Scalar GreenColor; // «елЄный 
    static cv::Scalar RedColor;
    static const int det_limArea = 6000;

    TrackingBox(int x, int y, int w, int h);

    std::tuple<int, int, int, int> shape() const;

    std::vector<int> rectangle() const;

    static std::vector<TrackingBox> createBoxes(const std::vector<std::vector<cv::Point>>& contours);
    static cv::Mat drawBoxes(cv::Mat& frame, const std::vector<TrackingBox>& boxes);

private:
    int x, y, w, h;
};

#endif
