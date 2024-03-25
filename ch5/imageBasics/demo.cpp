#include <opencv2/opencv.hpp>
#include <string>

using namespace std;
// #define ONE

string image_file = "../../imageBasics/distorted.png";

// 获取原图对应坐标的像素值
uchar get_scale_value(cv::Mat &img, int i, int j) {
    uchar *ptr = img.ptr<uchar>(i);
    return p[j];
}