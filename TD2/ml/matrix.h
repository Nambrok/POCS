#ifndef matrix_h
#define matrix_h

#include <cassert>
#include "vector.h"

namespace ml {

class matrix_base {
protected:
std::size_t NbRows;
std::size_t NbCols;


public:
virtual std::size_t rows() const = 0;
virtual std::size_t cols() const = 0;
virtual double& operator()(const std::size_t, const std::size_t) = 0;
virtual const double& operator()(const std::size_t, const std::size_t) const = 0;
matrix_base& operator=(double);
vector operator*(const vector& v) const;
virtual std::ostream& print(std::ostream&) const = 0;
//std::ostream& operator<<(std::ostream&, const matrix_base&);
};

namespace version2 {
class matrix : public matrix_base {
private:
double ** mat;

public:
matrix(const std::size_t, const std::size_t);
std::size_t rows() const;
std::size_t cols() const;
double& operator()(const std::size_t, const std::size_t);
const double& operator()(const std::size_t, const std::size_t) const;
~matrix();
std::ostream& print(std::ostream&) const;
//std::ostream& operator<<(std::ostream&, const matrix&);
//Manque les destructeurs


class transpose_matrix : public matrix_base {
private:
matrix_base* m;
public:
transpose_matrix(matrix_base*);
std::size_t rows() const;
std::size_t cols() const;
double& operator()(const std::size_t, const std::size_t);
const double& operator()(const std::size_t, const std::size_t) const;
std::ostream& print(std::ostream&) const;
};

transpose_matrix transpose();
};
}
std::ostream& operator<<(std::ostream&, const ml::matrix_base&);

namespace version3 {
class matrix {
private:
double ** mat;
std::size_t x;
std::size_t y;

public:
matrix(const std::size_t, const std::size_t);
matrix(const matrix&) = delete;
std::size_t rows() const;
std::size_t cols() const;
double& operator()(const std::size_t, const std::size_t);
const double& operator()(const std::size_t, const std::size_t) const;
~matrix();
std::ostream& print(std::ostream&) const;
//std::ostream& operator<<(std::ostream&, const matrix&);

matrix& operator=(double);
vector operator*(const vector& v) const;


class transpose_matrix {
private:
matrix* m;
public:
transpose_matrix(matrix*);
std::size_t rows() const;
std::size_t cols() const;
double& operator()(const std::size_t, const std::size_t);
const double& operator()(const std::size_t, const std::size_t) const;
std::ostream& print(std::ostream&) const;
vector operator*(const vector& v) const;
};

transpose_matrix transpose();
};
}


}

std::ostream& operator<<(std::ostream&, const ml::version3::matrix&);
std::ostream& operator<<(std::ostream&, const ml::version3::matrix::transpose_matrix&);
#endif
