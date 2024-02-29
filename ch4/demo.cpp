#include <iostream>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include "sophus/se3.hpp"
#include <cmath>

using namespace Eigen;
using namespace std;


int main() {
    Matrix3d R = AngleAxisd(M_PI / 2, Vector3d(0, 0, 1)).toRotationMatrix();
    Quaterniond q(R);
    Sophus::SO3d SO3_R(R);
    Sophus::SO3d SO3_q(q);
    cout << R << endl;
    cout << string(50, '=') << endl;
    // cout << R << endl;
    // std::cout << std::string(50, '=') << std::endl;
    // cout << SO3_R.matrix() << endl;
    // std::cout << std::string(50, '=') << std::endl;
    // cout << SO3_q.matrix() << endl;
    // std::cout << std::string(50, '=') << std::endl;
    // // 获取李代数
    // Vector3d so3 = SO3_R.log();
    // cout << so3.transpose() << endl;
    // 增量扰动模型
    // Vector3d update_so3(1e-4, 0, 0); //假设更新量为这么多
    // Sophus::SO3d SO3_updated = Sophus::SO3d::exp(update_so3) * SO3_R;
    // cout << "SO3 updated = \n" << SO3_updated.matrix() << endl;
    Vector3d t(1, 0, 0);        // 沿X轴平移1
    Sophus::SE3d SE3_Rt(R, t);  // 从R,t构造SE(3)
    Sophus::SE3d SE3_qt(q, t);  // 从q,t构造SE(3)
    cout << "SE3 from R,t= \n"
         << SE3_Rt.matrix() << endl;
    cout << "SE3 from q,t= \n"
         << SE3_qt.matrix() << endl;
    // 李代数se(3) 是一个六维向量，方便起见先typedef一下
    typedef Eigen::Matrix<double, 6, 1> Vector6d;
    Vector6d se3 = SE3_Rt.log();
    cout << "se3 = " << se3.transpose() << endl;
}