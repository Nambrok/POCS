#ifndef matrix_h
#define matrix_h

#include <cassert>
#include "vector.h"

namespace ml {

class matrix_base {
protected:
std::size_t x;
std::size_t y;


public:
virtual std::size_t size_x() const = 0;
virtual std::size_t size_y() const = 0;
virtual double& operator()(const std::size_t, const std::size_t) = 0;
virtual const double& operator()(const std::size_t, const std::size_t) const = 0;
matrix_base& operator=(double);
vector operator*(const vector& v) const;
virtual std::ostream& print(std::ostream&) const = 0;
//std::ostream& operator<<(std::ostream&, const matrix_base&);
//TODO: Manque les destructeurs
};

namespace version1 {
class matrix : public matrix_base {
private:
double ** mat;

public:
matrix(const std::size_t, const std::size_t);
std::size_t size_x() const;
std::size_t size_y() const;
double& operator()(const std::size_t, const std::size_t);
const double& operator()(const std::size_t, const std::size_t) const;
std::ostream& print(std::ostream&) const;
//std::ostream& operator<<(std::ostream&, const matrix&);
//Manque les destructeurs


class transpose_matrix : public matrix_base {
private:
matrix_base* m;
public:
transpose_matrix(matrix_base*);
std::size_t size_x() const;
std::size_t size_y() const;
double& operator()(const std::size_t, const std::size_t);
const double& operator()(const std::size_t, const std::size_t) const;
std::ostream& print(std::ostream&) const;
};

transpose_matrix transpose();
};
}
std::ostream& operator<<(std::ostream&, const ml::matrix_base&);

}

#endif
