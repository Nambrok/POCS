#ifndef matrixv1_h
#define matrixv1_h

#include <iostream>
#include <cassert>
#define NDEBUG
#include "vector.h"

namespace ml {
namespace version1 {
class matrix {
private:
std::size_t NbRows;
std::size_t NbCols;
double ** mat;

public:
matrix(const std::size_t x, const std::size_t y);
matrix(const matrix&) = delete;
std::size_t rows() const;
std::size_t cols() const;
double& operator()(const std::size_t, const std::size_t);
const double& operator()(const std::size_t, const std::size_t) const;
matrix& operator=(double);
vector operator*(const vector& v) const;
std::ostream& print(std::ostream&) const;
//std::ostream& operator<<(std::ostream&, const matrix_base&);
matrix& transpose();
~matrix();
};
std::ostream& operator<<(std::ostream&, const matrix&);
}
}

#endif
