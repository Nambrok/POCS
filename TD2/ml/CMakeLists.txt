cmake_minimum_required(VERSION 3.7.2)

project(tp2 VERSION 1.0 LANGUAGES CXX)


# compilation c++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)


add_executable(ref
  ref.cpp
  )

add_executable(test_algebra
  test_algebra.cpp vector.cpp matrix.cpp matrixv1.cpp
  )

add_executable(test_performances
  test_performances.cpp vector.cpp matrix.cpp matrixv1.cpp
  )

add_executable(ml
  ml.cpp vector.cpp matrixv1.cpp matrix.cpp
  )
target_link_libraries(ml Eigen3::Eigen)

file(COPY ${CMAKE_CURRENT_SRC_DIR}data.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

target_compile_options(test_algebra PUBLIC -Wall)
target_compile_options(test_performances PUBLIC -Wall)
target_compile_options(ml PUBLIC -Wall)
target_compile_options(ml PUBLIC -g)
