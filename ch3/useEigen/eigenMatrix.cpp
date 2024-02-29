#include<iostream>
#include<Eigen/Core>
#include<Eigen/Dense>

#include<ctime>

using namespace Eigen;
#define MATRIX_SIZE 50

// 演示Eigen矩阵库的一些基本操作
void test1() {
    Matrix<float, 2, 3> matrix_23;
    Vector3d v_3d;// 注意默认表示的是三维列向量

    Matrix<float, 3, 1> vd_3d;

    Matrix3d matrix33 = Matrix3d::Zero();

    Matrix<double, Dynamic, Dynamic> matrix_dynamic;
    MatrixXd matrix_xd;
    Matrix3d matrix_5d;
    // 初始化操作
    v_3d << 1, 2, 3;
    matrix_23 << 1, 2, 3, 4, 5, 6;
    std::cout << "v_3d:" << v_3d << std::endl;
    std::cout << "v_3d.transpose():" << v_3d.transpose() << std::endl;
    std::cout << "matrix_23:" << matrix_23 << std::endl;

    //访问矩阵的元素
    for(int i = 0; i < 2; ++i) {
        for(int j = 0; j < 3; ++j) std::cout << matrix_23(i, j) << std::endl;
        std::cout << std::endl;
    }
}

void test2() {
    Matrix<float, 2, 3> matrix_23;
    matrix_23 << 1, 2, 3, 4, 5, 6;
    Vector3d v_3d;
    v_3d << 3, 2, 1;
    Vector3f vf_3d;
    vf_3d << 4, 5, 6;
    Matrix<double, 2, 1> ret = matrix_23.cast<double>() * v_3d;
    Matrix<float, 2, 1> ret1 = matrix_23 * vf_3d;
    std::cout << "ret :" << ret.transpose() << std::endl;
    std::cout << "ret1 :" << ret1.transpose() << std::endl;
}

void test3() {
    Matrix<double, 3, 3> matrix_33 = Matrix3d::Random();
}

int main() {
    test2();
}
