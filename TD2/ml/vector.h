#ifndef vector_h
#define vector_h

#include <iostream>
#include <cmath>
#define NDEBUG
#include <cassert>

namespace ml {
class vector {

private:
double * vect;
std::size_t taille;

//TODO: Remplacer les if pour les size par des assert

public:
vector(const std::size_t);
vector();
void creation(const std::size_t);
~vector();
std::size_t size() const;
double& operator[](const std::size_t);
const double& operator[](const std::size_t) const;
vector& operator=(const vector&);
vector& operator=(double);
vector& operator+=(const vector&);
vector& operator-=(const vector&);
vector operator-(const vector&);
vector operator+(const vector&);
vector operator*(double);
vector operator*(const vector&);
// vector operator*(double, const vector&);

double dot(const vector &) const;
double squaredNorm() const;
double sum() const;
std::ostream& print(std::ostream&) const;
};

std::ostream& operator<<(std::ostream&, const ml::vector&);

}

#endif
