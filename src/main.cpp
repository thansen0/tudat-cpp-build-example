#include <Eigen/Dense>
#include <iostream>
#include <stdlib.h>

// Note: this doesn't use tudat code yet

using namespace std;

int main() {
    Eigen::Matrix<double, 6, 1> v;
    v << 1, 2, 3, 4, 5, 6;
    std::cout << v.transpose() << std::endl;
    return 0;

}

