#include <iostream>
#include <chrono>

#include "vector.h"
#include "matrix.h"
#include "matrixv1.h"

int main()
{
        {
                std::cout << "test de performances de ml::vector" << std::endl;

                auto start = std::chrono::system_clock::now();
                ml::vector V(100000);
                std::cout << V << std::endl;
                for(int i = 0; i<V.size(); i++) {
                        V[i] = i;

                }
                std::cout << V << std::endl;
                auto end = std::chrono::system_clock::now();

                auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
                std::cout << "time = " << elapsed << " ms" << std::endl;
        }
        std::cout << "test de performances de ml::version2::matrix" << std::endl;

        auto start = std::chrono::system_clock::now();
        ml::version2::matrix m(100, 100);

        for(int i = 0; i<m.size_x(); i++) {
                for(int j = 0; j<m.size_y(); j++) {
                        m(i, j) = i+j;
                }
        }

        std::cout << m << std::endl;
        std::cout << m.transpose() << std::endl;

        std::cout << m * 10.0 << std::endl;

        auto end = std::chrono::system_clock::now();

        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
        std::cout << "time = " << elapsed << " ms" << std::endl;

        std::cout << "test de performances de ml::version3::matrix" << std::endl;

        // TODO

        return 0;
}
