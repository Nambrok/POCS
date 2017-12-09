#include "matrixv1.h"

ml::version1::matrix& ml::version1::matrix::operator=(double d){
        for(unsigned int i = 0; i < this->rows(); i++) {
                for(unsigned int j = 0; j < this->cols(); j++) {
                        this->operator()(i, j) = d;
                }
        }
        return *this;
}

ml::vector ml::version1::matrix::operator*(const vector& v) const {
        assert(this->cols() == v.size());
        ml::vector res(this->rows());
        for(unsigned int i = 0; i<this->rows(); i++) {
                for(unsigned int j = 0; j<this->cols(); j++) {
                        res[i] += this->operator()(i, j) * v[j];
                }
        }
        return res;
}

ml::version1::matrix::matrix(const std::size_t x, const std::size_t y){
        this->NbRows = x;
        this->NbCols = y;
        this->mat = new double*[x];
        for(auto i = 0u; i<x; i++) {
                this->mat[i] = new double[y];
        }

        for(auto i = 0u; i<x; i++) {
                for(auto j = 0u; j<y; j++) {
                        this->mat[i][j] = 0;
                }
        }
}

std::size_t ml::version1::matrix::rows() const {
        return this->NbRows;
}

std::size_t ml::version1::matrix::cols() const {
        return this->NbCols;
}

double& ml::version1::matrix::operator()(const std::size_t i, const std::size_t j){
        assert(i < this->rows() && j < this->cols());
        return this->mat[i][j];
}

const double& ml::version1::matrix::operator()(const std::size_t i, const std::size_t j) const {
        assert(i < this->rows() && j < this->cols());
        return this->mat[i][j];
}

ml::version1::matrix ml::version1::matrix::transpose(){
        ml::version1::matrix newMat(this->cols(), this->rows());

        for(unsigned int i = 0; i<this->rows(); i++) {
                for(unsigned int j = 0; j<this->cols(); j++) {
                        newMat(j, i) = this->operator()(i, j);
                }
        }
        return newMat;
}

ml::version1::matrix::~matrix(){
        for(unsigned int i = 0; i<this->rows(); i++) {
                delete[] this->mat[i];
        }
        delete[] this->mat;
}

std::ostream& ml::version1::matrix::print(std::ostream& os) const {
        for(unsigned int i = 0; i<this->rows(); i++) {
                for(unsigned int j = 0; j<this->cols(); j++) {
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

ml::version1::matrix::matrix(const ml::version1::matrix& oldMat){
        this->NbRows = oldMat.rows();
        this->NbCols = oldMat.cols();
        mat = new double*[oldMat.rows()];
        for(unsigned int i = 0; i<oldMat.rows(); i++) {
                mat[i] = new double[oldMat.cols()];
        }

        for(unsigned int i = 0; i<oldMat.rows(); i++) {
                for(unsigned int j = 0; j<oldMat.cols(); j++) {
                        mat[i][j] = 0;
                }
        }
}
