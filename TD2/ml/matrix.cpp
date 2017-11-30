#include "matrix.h"

ml::matrix_base& ml::matrix_base::operator=(double d){
        for(auto i = 0u; i < this->size_x(); i++) {
                for(auto j = 0u; j < this->size_y(); j++) {
                        this->operator()(i, j) = d;
                }
        }
        return *this;
}

ml::vector ml::matrix_base::operator*(const vector& v) const {

        assert(this->size_y() == v.size());
        ml::vector res(this->size_x());
        for(auto i = 0u; i<this->size_x(); i++) {
                for(auto j = 0u; j<this->size_y(); j++) {
                        res[i] += this->operator()(i, j) * v[j];
                }
        }
        return res;
}

ml::version2::matrix::matrix(const std::size_t x, const std::size_t y){
        this->x = x;
        this->y = y;
        mat = new double*[x];
        for(auto i = 0u; i<x; i++) {
                mat[i] = new double[y]();
        }

        for(auto i = 0u; i<x; i++) {
                for(auto j = 0u; j<y; j++) {
                        mat[i][j] = 0;
                }
        }
}

std::size_t ml::version2::matrix::size_x() const {
        return this->x;
}

std::size_t ml::version2::matrix::size_y() const {
        return this->y;
}

double& ml::version2::matrix::operator()(const std::size_t i, const std::size_t j){
        assert(i < this->size_x() && j < this->size_y());
        return this->mat[i][j];
}

const double& ml::version2::matrix::operator()(const std::size_t i, const std::size_t j) const {
        assert(i < this->size_x() && j < this->size_y());
        return this->mat[i][j];
}

ml::version2::matrix::~matrix(){
        for(auto i = 0u; i<this->size_x(); i++) {
                delete [] this->mat[i];
        }
        delete[] this->mat;
}

std::ostream& ml::version2::matrix::print(std::ostream& os) const {
        for(auto i = 0u; i<this->size_x(); i++) {
                for(auto j = 0u; j<this->size_y(); j++) {
                        os << this->operator()(i, j) << " ";
                }
                os << std::endl;
        }
        return os;
}

std::ostream& ml::operator<<(std::ostream& os, const ml::matrix_base& mat){
        mat.print(os);
        return os;
}

ml::version2::matrix::transpose_matrix::transpose_matrix(matrix_base * mat){
        this->m = mat;
}

std::size_t ml::version2::matrix::transpose_matrix::size_x() const {
        return this->m->size_y();
}

std::size_t ml::version2::matrix::transpose_matrix::size_y() const {
        return this->m->size_x();
}

double& ml::version2::matrix::transpose_matrix::operator()(const std::size_t i, const std::size_t j){
        assert(i < this->size_x() && j < this->size_y());
        return this->m->operator()(j,i);
}

const double& ml::version2::matrix::transpose_matrix::operator()(const std::size_t i, const std::size_t j) const {
        assert(i < this->size_x() && j < this->size_y());
        return this->m->operator()(j,i);
}

std::ostream& ml::version2::matrix::transpose_matrix::print(std::ostream& os) const {
        for(auto i = 0u; i<this->size_x(); i++) {
                for(auto j = 0u; j<this->size_y(); j++) {
                        os << this->operator()(i, j) << " ";
                }
                os << std::endl;
        }
        return os;
}

ml::version2::matrix::transpose_matrix ml::version2::matrix::transpose(){
        return ml::version2::matrix::transpose_matrix(this);
}
