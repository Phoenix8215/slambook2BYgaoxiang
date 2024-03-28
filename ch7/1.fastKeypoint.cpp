#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>

class FastKeyPointDec {
public:
    /**
     * @brief 检测是否为关键点
     * 
     * @param Ip :输入想检测的关键点的亮度信息
     * @param threshhold :亮度阈值
     * @param IpVector :以3个像素点为半径的园上的点
     * @return true 
     * @return false 
     */
    bool isKeyPoint(double Ip, double threshhold, std::vector<double> &IpVector) {
        // 预筛选：只考察1,5,9,13这四个点
        int a1 = IpVector[0]>Ip + threshhold || IpVector[0]<Ip - threshhold; //判断依据:亮度过小过大
        int a2 = IpVector[6]>Ip + threshhold || IpVector[6]<Ip - threshhold;
        int a3 = IpVector[10]>Ip + threshhold || IpVector[10]<Ip - threshhold;
        int a4 = IpVector[14]>Ip + threshhold || IpVector[14]<Ip - threshhold;
        if(a1+a2+a3+a4 < 2) return false;
        int num = 0;
        for(const auto &item:IpVector) {
            if(item>Ip + threshhold || item<Ip - threshhold) {
                ++num;
            }
        }

        if(num >= 12) return true;
        if(num < 12) return false;
    }

    /**
     * @brief 对关键点进行非极大值抑制
     * 
     */
    // void nms(std::vector<cv::Point>&keyPoint, const cv::Mat &srcImg) {
    //     for(int i = 0; i<keyPoint.size(); i++) {
    //         for(int j = 1; j<keyPoint.size(); j++) {
    //             if(sqrt(pow((keyPoint[i].x - keyPoint[j].x), 2) + pow((keyPoint[i].y - keyPoint[j].y), 2)) < 3) {
    //                 // 保留亮度最大的像素值
    //                 if(srcImg.at<uchar>(keyPoint[i].x, keyPoint[i].y) < srcImg.at<uchar>(keyPoint[j].x, keyPoint[j].y)) {
    //                     auto it = keyPoint.begin() + j;
    //                     keyPoint.erase(it);
    //                 } else {
    //                     auto it = keyPoint.begin() + i;
    //                     keyPoint.erase(it);
    //                 }
    //             }
    //         }
    //     }
    // }

    void fastDectKey(const cv::Mat &srcImg, std::vector<cv::Point>&keyPoint, double T){
        assert(!srcImg.empty());
        cv::Mat img;
        int row=srcImg.rows;
        int col=srcImg.cols;
        std::vector<double>ipVec(0);
        cv::cvtColor(srcImg,img,cv::COLOR_BGR2GRAY);
        //assert(img.channels()==1);
        for(int i=3;i<row-3;i++){
            for(int j=3;j<col-3;j++){
                double ipval=img.at<uchar>(i,j);
                ipVec.push_back(img.at<uchar>(i-3,j));ipVec.push_back(img.at<uchar>(i-3,j+1));   //1,2
                ipVec.push_back(img.at<uchar>(i-2,j+2));    //3
                ipVec.push_back(img.at<uchar>(i-1,j+3));ipVec.push_back(img.at<uchar>(i,j+3));ipVec.push_back(img.at<uchar>(i+1,j+3));//4,5,6
                ipVec.push_back(img.at<uchar>(i+2,j+2));    //7
                ipVec.push_back(img.at<uchar>(i+3,j+1));ipVec.push_back(img.at<uchar>(i+3,j));ipVec.push_back(img.at<uchar>(i+3,j-1));//8,9,10
                ipVec.push_back(img.at<uchar>(i+2,j-2));    //11
                ipVec.push_back(img.at<uchar>(i+1,j-3));ipVec.push_back(img.at<uchar>(i,j-3));ipVec.push_back(img.at<uchar>(i-1,j-3));//12,13,14
                ipVec.push_back(img.at<uchar>(i-2,j-2));    //15
                ipVec.push_back(img.at<uchar>(i-3,j-2));    //16
                if(ipVec.size()==16){
                    if(isKeyPoint(ipval,T,ipVec)){
                        keyPoint.push_back(cv::Point(j,i));
                        // nms(keyPoint);
                        // cv::circle(srcImg,cv::Point(j,i),2,cv::Scalar(255,255,0),1,cv::LINE_8);
                    }
                    // nms(keyPoint, srcImg);

                    ipVec.clear();
                }
            }
        }
        cv::imwrite("res-keywithNoNMS.png",srcImg);
    }

};



int main() {
    cv::Mat src=cv::imread("../1.png");
    if(src.empty()){
        std::cout<<"no image\n";
    }
    FastKeyPointDec fast;
    std::vector<cv::Point>pt;
    fast.fastDectKey(src,pt,30);
    return 0;
}
