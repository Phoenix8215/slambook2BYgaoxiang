#include <chrono>
#include <iostream>
#include <opencv2/opencv.hpp>



using namespace std;


int main(int argc, char **argv) {
    cv::Mat image;
    image = cv::imread(argv[1]);
    if(image.data == nullptr) {
        cerr << "文件不存在" << endl;
        return 0;
    }
    cout << image.rows << image.cols << endl;
    cout << image.channels() << endl;
    cv::imwrite("image.png", image);// 保存图片
    auto t1 = std::chrono::high_resolution_clock::now();
    // for(size_t y = 0; y < image.rows; ++y) {
    //     unsigned char *row_ptr = image.ptr<unsigned char>(y);
    //     for(size_t x = 0; x < image.cols; ++x) {
    //         unsigned char *data_ptr = &row_ptr[x * image.channels()];
    //         for(size_t i = 0; i != image.channels(); ++i) {
    //             unsigned char data = data_ptr[i];
    //             // cout << int(data) << endl;
    //         }
    //     }
    // }  // 使用时间为：6.4e-08


    auto t2 = chrono::high_resolution_clock::now();
    auto time_used = chrono::duration_cast<chrono::duration<double>> (t2 - t1);
    cout << "使用时间为：" << time_used.count() << endl;
}