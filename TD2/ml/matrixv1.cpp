#include "matrixv1.h"

ml::version1::matrix& ml::version1::matrix::operator=(double d){
        for(unsigned int i = 0; i < this->size_x(); i++) {
                for(unsigned int j = 0; j < this->size_y(); j++) {
                        this->operator()(i, j) = d;
                }
        }
        return *this;
}

ml::vector ml::version1::matrix::operator*(const vector& v) const {
        assert(this->size_y() == v.size());
        ml::vector res(this->size_x());
        for(unsigned int i = 0; i<this->size_x(); i++) {
                for(unsigned int j = 0; j<this->size_y(); j++) {
                        res[i] += this->operator()(i, j) * v[j];
                }
        }
        return res;
}

ml::version1::matrix::matrix(const std::size_t x, const std::size_t y){
        this->x = x;
        this->y = y;
        mat = new double*[x];
        for(unsigned int i = 0; i<x; i++) {
                mat[i] = new double[y];
        }

        for(unsigned int i = 0; i<x; i++) {
                for(unsigned int j = 0; j<y; j++) {
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
        assert(i < this->size_x() && j < this->size_y());
        return this->mat[i][j];
}

const double& ml::version1::matrix::operator()(const std::size_t i, const std::size_t j) const {
        assert(i < this->size_x() && j < this->size_y());
        return this->mat[i][j];
}

ml::version1::matrix& ml::version1::matrix::transpose(){
        ml::version1::matrix * newMat = new ml::version1::matrix(this->size_y(), this->size_x());

        for(unsigned int i = 0; i<this->size_x(); i++) {
                for(unsigned int j = 0; j<this->size_y(); j++) {
                        newMat->operator()(j, i) = this->operator()(i, j);
                }
        }
        return *newMat;
}

ml::version1::matrix::~matrix(){
        for(unsigned int i = 0; i<this->size_x(); i++) {
                delete[] this->mat[i];
        }
        delete[] this->mat;
}

std::ostream& ml::version1::matrix::print(std::ostream& os) const {
        for(unsigned int i = 0; i<this->size_x(); i++) {
                for(unsigned int j = 0; j<this->size_y(); j++) {
                        os << this->operator()(i, j) << " ";
                }
                os << std::endl;
        }
        return os;
}

std::ostream& ml::version1::operator<<(std::ostream& os, const ml::version1::matrix& mat){
        mat.print(os);
        return os;
}
