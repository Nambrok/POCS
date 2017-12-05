#include "matrix.h"

ml::matrix_base& ml::matrix_base::operator=(double d){
        for(auto i = 0u; i < this->rows(); i++) {
                for(auto j = 0u; j < this->cols(); j++) {
                        this->operator()(i, j) = d;
                }
        }
        return *this;
}

ml::vector ml::matrix_base::operator*(const vector& v) const {

        assert(this->cols() == v.size());
        ml::vector res(this->rows());
        for(auto i = 0u; i<this->rows(); i++) {
                for(auto j = 0u; j<this->cols(); j++) {
                        res[i] += this->operator()(i, j) * v[j];
                }
        }
        return res;
}

ml::version2::matrix::matrix(const std::size_t x, const std::size_t y){
        this->NbRows = x;
        this->NbCols = y;
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

std::size_t ml::version2::matrix::rows() const {
        return this->NbRows;
}

std::size_t ml::version2::matrix::cols() const {
        return this->NbCols;
}

double& ml::version2::matrix::operator()(const std::size_t i, const std::size_t j){
        assert(i < this->rows() && j < this->cols());
        return this->mat[i][j];
}

const double& ml::version2::matrix::operator()(const std::size_t i, const std::size_t j) const {
        assert(i < this->rows() && j < this->cols());
        return this->mat[i][j];
}

ml::version2::matrix::~matrix(){
        for(auto i = 0u; i<this->rows(); i++) {
                delete [] this->mat[i];
        }
        delete[] this->mat;
}

std::ostream& ml::version2::matrix::print(std::ostream& os) const {
        for(auto i = 0u; i<this->rows(); i++) {
                for(auto j = 0u; j<this->cols(); j++) {
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

std::size_t ml::version2::matrix::transpose_matrix::rows() const {
        return this->m->cols();
}

std::size_t ml::version2::matrix::transpose_matrix::cols() const {
        return this->m->rows();
}

double& ml::version2::matrix::transpose_matrix::operator()(const std::size_t i, const std::size_t j){
        assert(i < this->rows() && j < this->cols());
        return this->m->operator()(j,i);
}

const double& ml::version2::matrix::transpose_matrix::operator()(const std::size_t i, const std::size_t j) const {
        assert(i < this->rows() && j < this->cols());
        return this->m->operator()(j,i);
}

std::ostream& ml::version2::matrix::transpose_matrix::print(std::ostream& os) const {
        for(auto i = 0u; i<this->rows(); i++) {
                for(auto j = 0u; j<this->cols(); j++) {
                        os << this->operator()(i, j) << " ";
                }
                os << std::endl;
        }
        return os;
}

ml::version2::matrix::transpose_matrix ml::version2::matrix::transpose(){
        return ml::version2::matrix::transpose_matrix(this);
}

ml::version3::matrix::matrix(const std::size_t x, const std::size_t y){
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

std::size_t ml::version3::matrix::rows() const {
        return this->x;
}

std::size_t ml::version3::matrix::cols() const {
        return this->y;
}

double& ml::version3::matrix::operator()(const std::size_t i, const std::size_t j){
        assert(i < this->rows() && j < this->cols());
        return this->mat[i][j];
}

const double& ml::version3::matrix::operator()(const std::size_t i, const std::size_t j) const {
        assert(i < this->rows() && j < this->cols());
        return this->mat[i][j];
}

ml::version3::matrix::~matrix(){
        for(auto i = 0u; i<this->rows(); i++) {
                delete [] this->mat[i];
        }
        delete[] this->mat;
}

std::ostream& ml::version3::matrix::print(std::ostream& os) const {
        for(auto i = 0u; i<this->rows(); i++) {
                for(auto j = 0u; j<this->cols(); j++) {
                        os << this->operator()(i, j) << " ";
                }
                os << std::endl;
        }
        return os;
}

ml::version3::matrix& ml::version3::matrix::operator=(double d){
        for(auto i = 0u; i < this->rows(); i++) {
                for(auto j = 0u; j < this->cols(); j++) {
                        this->operator()(i, j) = d;
                }
        }
        return *this;
}

ml::vector ml::version3::matrix::operator*(const vector& v) const {
        assert(this->cols() == v.size());
        ml::vector res(this->rows());
        for(auto i = 0u; i<this->rows(); i++) {
                for(auto j = 0u; j<this->cols(); j++) {
                        res[i] += this->operator()(i, j) * v[j];
                }
        }
        return res;
}

std::ostream& operator<<(std::ostream& os, const ml::version3::matrix& mat){
        mat.print(os);
        return os;
}

std::ostream& operator<<(std::ostream& os, const ml::version3::matrix::transpose_matrix& mat){
        mat.print(os);
        return os;
}

ml::version3::matrix::transpose_matrix::transpose_matrix(ml::version3::matrix * mat){
        this->m = mat;
}

std::size_t ml::version3::matrix::transpose_matrix::rows() const {
        return this->m->cols();
}

std::size_t ml::version3::matrix::transpose_matrix::cols() const {
        return this->m->rows();
}

double& ml::version3::matrix::transpose_matrix::operator()(const std::size_t i, const std::size_t j){
        assert(i < this->rows() && j < this->cols());
        return this->m->operator()(j,i);
}

const double& ml::version3::matrix::transpose_matrix::operator()(const std::size_t i, const std::size_t j) const {
        assert(i < this->rows() && j < this->cols());
        return this->m->operator()(j,i);
}

std::ostream& ml::version3::matrix::transpose_matrix::print(std::ostream& os) const {
        for(auto i = 0u; i<this->rows(); i++) {
                for(auto j = 0u; j<this->cols(); j++) {
                        os << this->operator()(i, j) << " ";
                }
                os << std::endl;
        }
        return os;
}

ml::version3::matrix::transpose_matrix ml::version3::matrix::transpose(){
        return ml::version3::matrix::transpose_matrix(this);
}

ml::vector ml::version3::matrix::transpose_matrix::operator*(const vector& v) const {
        assert(this->cols() == v.size());
        ml::vector res(this->rows());
        for(auto i = 0u; i<this->rows(); i++) {
                for(auto j = 0u; j<this->cols(); j++) {
                        res[i] += this->operator()(i, j) * v[j];
                }
        }
        return res;
}
