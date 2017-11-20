#include "matrix.h"

ml::matrix_base& ml::matrix_base::operator=(double d){
        for(int i = 0; i < this->size_x(); i++) {
                for(int j = 0; j < this->size_y(); j++) {
                        this->operator()(i, j) = d;
                }
        }
        return *this;
}

ml::vector ml::matrix_base::operator*(const vector& v) const {
        assert(this->size_y() == v.size());
        ml::vector res(v.size());
        for(int i = 0; i<this->size_x(); i++) {
                for(int j = 0; j<this->size_y(); j++) {
                        res[i] += this->operator()(i, j) * v[j];
                }
        }
        return res;
}

ml::version1::matrix::matrix(const std::size_t x, const std::size_t y){
        this->x = x;
        this->y = y;
        mat = new double*[x];
        for(int i = 0; i<x; i++) {
                mat[i] = new double[y]();
        }

        for(int i = 0; i<x; i++) {
                for(int j = 0; j<y; j++) {
                        mat[i][j] = 0;
                }
        }
}

std::size_t ml::version1::matrix::size_x() const {
        return this->x;
}

std::size_t ml::version1::matrix::size_y() const {
        return this->y;
}

double& ml::version1::matrix::operator()(const std::size_t i, const std::size_t j){
        return this->mat[i][j];
}

const double& ml::version1::matrix::operator()(const std::size_t i, const std::size_t j) const {
        return this->mat[i][j];
}

std::ostream& ml::version1::matrix::print(std::ostream& os) const {
        for(int i = 0; i<this->size_x(); i++) {
                for(int j = 0; j<this->size_y(); j++) {
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

ml::version1::matrix::transpose_matrix::transpose_matrix(matrix_base * mat){
        this->m = mat;
}

std::size_t ml::version1::matrix::transpose_matrix::size_x() const {
        return this->m->size_y();
}

std::size_t ml::version1::matrix::transpose_matrix::size_y() const {
        return this->m->size_x();
}

double& ml::version1::matrix::transpose_matrix::operator()(const std::size_t i, const std::size_t j){
        return this->m->operator()(j,i);
}

const double& ml::version1::matrix::transpose_matrix::operator()(const std::size_t i, const std::size_t j) const {
        return this->m->operator()(j,i);
}

std::ostream& ml::version1::matrix::transpose_matrix::print(std::ostream& os) const {
        for(int i = 0; i<this->size_x(); i++) {
                for(int j = 0; j<this->size_y(); j++) {
                        os << this->operator()(i, j) << " ";
                }
                os << std::endl;
        }
        return os;
}

ml::version1::matrix::transpose_matrix ml::version1::matrix::transpose(){
        return ml::version1::matrix::transpose_matrix(this);
}
