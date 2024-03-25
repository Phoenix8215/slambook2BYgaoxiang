#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include <tuple>
#include <functional>


using namespace std;

string image_file = "../../imageBasics/distorted.png";

  // 畸变参数
static double k1 = -0.28340811, k2 = 0.07395907, p1 = 0.00019359, p2 = 1.76187114e-05;
// 内参
static double fx = 458.654, fy = 457.296, cx = 367.215, cy = 248.375;


tuple<double, double> fromTarget2Source(int u, int v) {
    double x = (u - cx) / fx, y = (v - cy) / fy;
    double r = sqrt(x * x + y * y);
    double x_distorted = x * (1 + k1 * r * r + k2 * r * r * r * r) + 2 * p1 * x * y + p2 * (r * r + 2 * x * x);
    double y_distorted = y * (1 + k1 * r * r + k2 * r * r * r * r) + p1 * (r * r + 2 * y * y) + 2 * p2 * x * y;
    double u_distorted = fx * x_distorted + cx;
    double v_distorted = fy * y_distorted + cy;
    return {u_distorted, v_distorted};
}

void undistort() {
    cv::Mat src = cv::imread(image_file, 0);
    cv::Mat output_img = cv::Mat(src.rows, src.cols, CV_8UC1);
    for(int v=0; v<src.rows; v++) {
        for(int u=0; u<src.cols; u++) {
            auto [u_distorted, v_distorted] = fromTarget2Source(u, v);
            // 保证在范围之内
            if(v_distorted >= 0 && v_distorted < src.rows && u_distorted >= 0 && u_distorted < src.cols) {
                // output_img.at<uchar>(i, j) =  get_scale_value(src, temp_h, temp_w);
                output_img.at<uchar>(v, u) = src.at<uchar>(int(v_distorted), int(u_distorted));
            } else {
                output_img.at<uchar>(v, u) = 0;
            }
            
        }
    }
    cv::imwrite("undistort.png", output_img); 
}



//获取原图相应坐标的像素值
uchar get_scale_value(cv::Mat& input_img, int i, int j)
{
    uchar* p = input_img.ptr<uchar>(i);
    return p[j];
    
}

// 最近邻插值
void scale1(cv::Mat& input_img,int width,int height)
{
    cv::Mat output_img(height, width, CV_8UC1);
    output_img.setTo(0);
    float h_scale_rate = (float)input_img.rows/ height;  //高的比例
    float w_scale_rate = (float)input_img.cols / width;  //宽的比例
    // source -> target
    for (int v = 0; v < height; v++)
    {
        for (int u = 0; u < width; u++)
        {
            int v_scale = h_scale_rate * v;   //依照高的比例计算原图相应坐标中的x，这里采用的是向下取整，当然四舍五入也可以
            int u_scale = w_scale_rate * u;  //依照宽的比例计算原图相应坐标中的y
            output_img.at<uchar>(v, u) = input_img.at<uchar>(v_scale, u_scale);
        }
    }

    cv::imwrite("scale1.png", output_img);

}


// 双线性插值
void scale2(cv::Mat& input_img,int width,int height) {

}


int main() {
    
    // cv::imwrite("src.png", src);
    cv::Mat target = cv::imread(image_file, 0);
    // undistort();
    scale1(target, 880, 880);
    return 0;
}