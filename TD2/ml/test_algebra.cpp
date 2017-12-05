#include <iostream>

#include "vector.h"
#include "matrix.h"
#include "matrixv1.h"

int main()
{
        std::cout << "test de ml::vector" << std::endl;

        // EXEMPLES

        ml::vector v(3);
        v[0] = 1.0;
        v[1] = 2.0;
        v[2] = 3.0;

        std::cout << "v = " << v << std::endl;
        std::cout << "v.sum() = " << v.sum() << std::endl;
        std::cout << "v.squaredNorm() = " << v.squaredNorm() << std::endl;

        ml::vector u(3);
        u[0] = 10.0;
        u[1] = 20.0;
        u[2] = 30.0;
        std::cout << "u + v = " << (u+v) << std::endl;




        u += v;
        std::cout << "u = " << u << std::endl;

        std::cout << "u = " << (v + v * 2.0 * v) << std::endl;

        std::cout << "test de ml::version1::matrix" << std::endl;


        ml::version1::matrix mat1(2, 3);
        mat1(0,0) = 1; mat1(0,1) = 2; mat1(0, 2) = 3;
        mat1(1, 0) = 4; mat1(1, 1) = 5; mat1(1, 2) = 6;


        std::cout << mat1 << std::endl;
        std::cout << mat1.transpose() << std::endl;
        std::cout << mat1 * v << std::endl;

        std::cout << "test de ml::version2::matrix" << std::endl;
        // ml::version2::matrix yo(5, 3);
        //
        // std::cout << yo << std::endl;

        ml::version2::matrix mat(2, 3);
        mat(0,0) = 1; mat(0,1) = 2; mat(0, 2) = 3;
        mat(1, 0) = 4; mat(1, 1) = 5; mat(1, 2) = 6;

        std::cout << mat << std::endl;
        std::cout << mat.transpose() << std::endl;
        std::cout << mat * v << std::endl;

        {
                std::cout << "test de ml::version3::matrix" << std::endl;

                ml::version3::matrix mat(2, 3);
                mat(0,0) = 1; mat(0,1) = 2; mat(0, 2) = 3;
                mat(1, 0) = 4; mat(1, 1) = 5; mat(1, 2) = 6;

                std::cout << mat << std::endl;
                std::cout << mat.transpose() << std::endl;
                std::cout << mat * v << std::endl;
        }

        return 0;
}
