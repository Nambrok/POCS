#include "vector.h"

ml::vector::vector(const std::size_t size){
        vect = new double[size]();
        this->taille = size;

        //Initialisation
        for(int i = 0; i<size; i++) {
                this->vect[i] = 0;
        }

        //std::cerr << "Construction" << std::endl;
        //std::cout << "u = " << (v + v * 2.0 * v) << std::endl;
        //5) Le constructeur est appeler trois fois une fois à chaque opérateurs une version temporaire avec les résultats de chaque opération est crée avant d'être utilisé puis supprimer
}

std::size_t ml::vector::size() const {
        return this->taille;
}

double& ml::vector::operator[](const ::size_t i){
        return vect[i];
}

const double& ml::vector::operator[](const std::size_t i) const {
        return this->vect[i];
}

ml::vector& ml::vector::operator=(const vector& oldVector){
        assert(this->size() == oldVector.size());
        for(int i = 0; i<oldVector.size(); i++) {
                this->vect[i] = oldVector[i];
        }
        return *this;
}

ml::vector& ml::vector::operator=(double val){
        for(int i = 0; i < this->size(); i++) {
                this->vect[i] = val;
        }
        return *this;
}

ml::vector& ml::vector::operator+=(const vector& oldVector){
        assert(this->size() == oldVector.size());
        for(int i = 0; i<oldVector.size(); i++) {
                this->vect[i] += oldVector[i];
        }
        return *this;
}

ml::vector& ml::vector::operator-=(const vector& oldVector){
        assert(this->size() == oldVector.size());
        for(int i = 0; i<oldVector.size(); i++) {
                this->vect[i] -= oldVector[i];
        }
        return *this;
}

ml::vector ml::vector::operator-(const vector& oldVector){
        assert(this->size() == oldVector.size());
        ml::vector newV(oldVector.size());
        for(int i = 0; i<oldVector.size(); i++) {
                newV[i] = this->vect[i] - oldVector[i];
        }
        return newV;

}

ml::vector ml::vector::operator+(const vector& oldVector){
        assert(this->size() == oldVector.size());
        ml::vector newV(oldVector.size());
        for(int i = 0; i<oldVector.size(); i++) {
                newV[i] = this->vect[i] + oldVector[i];
        }
        return newV;

}

ml::vector ml::vector::operator*(double d){
        ml::vector newV(this->size());
        for(int i = 0; i<this->size(); i++) {
                newV[i] = this->vect[i] * d;
        }
        return newV;
}

ml::vector ml::vector::operator*(const ml::vector& oldVector){
        assert(this->size() == oldVector.size());
        ml::vector newV(this->size());
        for(int i = 0; i<this->size(); i++) {
                newV[i] = this->vect[i] * oldVector[i];
        }
        return newV;
}

double ml::vector::dot(const vector &oldVector) const {
        assert(this->size() == oldVector.size());
        double somme;
        for(int i = 0; i<oldVector.size(); i++) {
                somme += this->vect[i] * oldVector[i];
        }
        return somme;
}

double ml::vector::sum() const {
        double somme = 0.0;
        for(int i = 0; i<this->size(); i++) {
                somme += this->vect[i];
        }
        return somme;
}

double ml::vector::squaredNorm() const {
        ml::vector v3(this->size());
        for(int i = 0; i<this->size(); i++) {
                v3[i] = this->vect[i] * this->vect[i];
        }
        return std::sqrt(v3.sum());
}

std::ostream& ml::vector::print(std::ostream& out) const {
        for(int i = 0; i<this->size(); i++) {
                out << this->vect[i] << " ";
        }
        return out;
}

std::ostream& ml::operator<<(std::ostream& out, const ml::vector& oldVector){
        oldVector.print(out);
        return out;
}

ml::vector::~vector(){
        delete[] this->vect;
}
