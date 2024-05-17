#include <cmath>
#include <iostream>
#include <opencv2/opencv.hpp>

const static int threshHold = 172;
const static int ksize = 3;
const static double k = 0.04;

void My_cornerHarris(cv::Mat src, cv::Mat& dst, int ksize, double k)  // 手写Harris特征
{
    cv::Mat Ix, Iy;                   // 存储图像一阶梯度
    cv::Mat M(src.size(), CV_32FC3);  // 创建3通道矩阵M存储 Ix*Ix , Ix*Iy , Iy*Iy
    cv::Mat R(src.size(), CV_32FC1);  // 创建3通道矩阵R存储Harris响应值

    // 使用Sobel算子提取图像x方向梯度和y方向梯度
    // void Sobel( InputArray src, OutputArray dst, int ddepth, int dx, int dy, int ksize=3, double scale=1, double delta=0, int borderType=cv::BORDER_DEFAULT );
    cv::Sobel(src, Ix, CV_32FC1, 1, 0, ksize);
    cv::Sobel(src, Iy, CV_32FC1, 0, 1, ksize);
    // 在 OpenCV 中，Vec3f 是一个表示三维浮点数向量的数据结构。

    // 存储Ix*Ix , Ix*Iy , Iy*Iy
    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            M.at<cv::Vec3f>(i, j)[0] = Ix.at<float>(i, j) * Ix.at<float>(i, j);  // Ix*Ix
            M.at<cv::Vec3f>(i, j)[1] = Ix.at<float>(i, j) * Iy.at<float>(i, j);  // Ix*Iy
            M.at<cv::Vec3f>(i, j)[2] = Iy.at<float>(i, j) * Iy.at<float>(i, j);  // Iy*Iy
        }
    }

    // 高斯滤波对M矩阵进行加权求和
    // void GaussianBlur(InputArray src, OutputArray dst, Size ksize, double sigmaX, double sigmaY = 0, int borderType = cv::BORDER_DEFAULT);
    cv::GaussianBlur(M, M, cv::Size(ksize, ksize), 2, 2);

    // 求得Harris响应值
    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            float A = M.at<cv::Vec3f>(i, j)[0];  // Ix*Ix
            float C = M.at<cv::Vec3f>(i, j)[1];  // Ix*Iy
            float B = M.at<cv::Vec3f>(i, j)[2];  // Iy*Iy

            // 响应值计算公式
            R.at<float>(i, j) = (A * B - C * C) - (k * (A + B) * (A + B));
        }
    }
    dst = R.clone();
}

void get_corners(const cv::Mat& res, const float thresh, std::vector<cv::Point>& corners) {
    for (int r = 0; r < res.rows; r++) {
        for (int c = 0; c < res.cols; c++) {
            if (res.at<float>(r, c) > thresh) {
                corners.emplace_back(c, r);
            }
        }
    }
}

int main() {
    cv::Mat src = cv::imread("../pattern.png", 1);
    if(src.empty()) {
        std::cerr << "failed to read image!" << std::endl;
        return -1;
    }

    cv::Mat res;
    cv::cvtColor(src, res, cv::COLOR_BGR2GRAY);
    My_cornerHarris(src, res, ksize, k);
    float thresh = 34 * abs(cv::mean(res)[0]);
    std::vector<cv::Point> corners;
    get_corners(res, thresh, corners);
    for(auto item:corners) {
        cv::circle(src, item, 2, cv::Scalar(0, 0, 255), 2);
    }
    cv::imwrite("result.jpg", src);
}