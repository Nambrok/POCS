
#include <iostream>
#include <fstream>
#include <cmath>
#include <fstream>

#include "vector.h"
#include "matrixv1.h"
#include "matrix.h"

#define NDEBUG

ml::vector hypothesis(const ml::version1::matrix& X, const ml::vector& theta)
{
        assert(ligne < X.size_x());
        assert(theta.size() == X.size_y());

        return X * theta;
}

double computeCost(const ml::version1::matrix& X, const ml::vector& y, const ml::vector& theta)
{
        const auto h = hypothesis(X, theta) - y;
        return 1.0/ (2.0*h.size()) * h.squaredNorm();

}

double computeMean(const ml::version1::matrix& X, int i)
{
        assert(X.size_y() < i);
        double mu = 0.0;
        for(auto j = 0u; j < X.size_x(); ++j) {
                mu += X(j,i);
        }
        return mu / X.size_x();
}

double computeStd(const ml::version1::matrix& X, const double mu, int i)
{
        auto sigma = 0.0;
        assert(i < X.size_y() && i >= 0); // On regarde si i est une colonne valide
        for(auto j = 0u; j < X.size_x(); j++) {
                sigma += std::pow((X(j,i) - mu), 2);
        }
        return std::sqrt(sigma/(X.size_x()-1));
}

void featureNormalize(ml::version1::matrix& X, const double mu, const double sigma, int i)
{
        assert(i >= 0 && i < X.size_y());
        for(auto j = 0u; j < X.size_x(); ++j) {
                X(j,i) = (X(j,i) - mu) / sigma;
        }
}

void gradientDescent(ml::version1::matrix& X, ml::vector& y, ml::vector& theta, double alpha, int iteration)
{
        std::ofstream file("cost.txt");

        for(auto iter = 0; iter<iteration; ++iter) {
                ml::vector Update(theta.size());
                for(auto i = 0u; i<Update.size(); i++) {
                        Update[i] = 0.0;
                }

                const auto h = hypothesis(X, theta) - y;
                // for(auto i = 0u; i<X.size_x(); ++i) {
                //         for(auto j = 0u; j<Update.size(); j++) {
                //                 Update[j] = Update[j] + alpha/X.size_x() * h[i] * X(i,j);
                //         }
                // }

                theta -= (X.transpose() * h)*(alpha/X.size_x());


                // theta -= Update;

                file << computeCost(X,y,theta) << std::endl;
        }
}

int main()
{
        std::ifstream file("data.txt");
        int m, size;
        file >> m >> size;

        std::cerr << "m : " << m << ", size : " << size << std::endl;

        ml::version1::matrix X(m, size); ml::vector y(m);
        std::cout << "Recopie de data dans les vecteurs x et y" << std::endl;

        assert(X.size_x() == m && y.size() == m);
        assert(X.size_y() == 3);
        for(auto i = 0; i < m; ++i) {
                X(i, 0) = 1.0;
                for(auto j = 1; j<size; j++) {
                        file >> X(i, j);
                        // std::cerr << "X("<< i << ", " << j << ") = "<<X(i, j) << std::endl;
                }
                file >> y[i];
                // std::cerr << "y[" << i << "] = " << y[i] << std::endl;
        }

        auto mu = computeMean(X,size-1);

        auto sigma = computeStd(X,mu,size-1);

        std::cout << "Mu : " << mu << std::endl;
        std::cout << "Sigma : " << sigma << std::endl;

        featureNormalize(X,mu,sigma,2);

        { // verification de l'hypothèse
                ml::vector theta1(3);
                theta1[0] = 1.;
                theta1[1] = 2.;
                theta1[2] = 3.;
                std::cout << "verification hypothesis(x[11],theta1) = " << hypothesis(X,theta1)[11] << std::endl;
                // double theta2[] = { 2., 2.5, 3.5 };
                ml::vector theta2(3);
                theta2[0] = 2.;
                theta2[1] = 2.5;
                theta2[2] = 3.5;
                std::cout << "verification hypothesis(x[33],theta2) = " << hypothesis(X,theta2)[33] << std::endl;
                // double theta3[] = { 0.5, 2.9, 3.9 };
                ml::vector theta3(3);
                theta3[0] = 0.5;
                theta3[1] = 2.9;
                theta3[2] = 3.9;
                std::cout << "verification hypothesis(x[55],theta3) = " << hypothesis(X,theta3)[55] << std::endl;
                // double theta4[] = { 4.9, 2.2, 1.1 }
                ml::vector theta4(3);
                theta1[0] = 4.9;
                theta1[1] = 2.2;
                theta1[2] = 1.1;
                std::cout << "verification hypothesis(x[77],theta4) = " << hypothesis(X,theta4)[77] << std::endl;
        }

        { // verification de la fonction de cout
                ml::vector theta1(3);
                theta1[0] = 1.;
                theta1[1] = 2.;
                theta1[2] = 3.;
                std::cout << "verification computeCost(x,y,theta1) = " << computeCost(X,y,theta1) << std::endl;
                ml::vector theta2(3);
                theta2[0] = 2.;
                theta2[1] = 2.5;
                theta2[2] = 3.5;
                std::cout << "verification computeCost(x,y,theta2) = " << computeCost(X,y,theta2) << std::endl;
                ml::vector theta3(3);
                theta3[0] = 0.5;
                theta3[1] = 2.9;
                theta3[2] = 3.9;
                std::cout << "verification computeCost(x,y,theta3) = " << computeCost(X,y,theta3) << std::endl;
                ml::vector theta4(3);
                theta1[0] = 4.9;
                theta1[1] = 2.2;
                theta1[2] = 1.1;
                std::cout << "verification computeCost(x,y,theta4) = " << computeCost(X,y,theta4) << std::endl;
        }

        std::cout << "recherche des paramètres theta optimaux" << std::endl;

        // double theta[] = { 0.0, 0.0, 0.0 };
        ml::vector theta(3);
        for(auto i = 0u; i<theta.size(); i++) {
                theta[i] = 0.0;
        }


        int iterations = 5000;
        double alpha = 0.1;

        gradientDescent(X, y, theta, alpha, iterations);

        std::cout << "paramètre theta obtenu : ["
                  << theta[0] << ","
                  << theta[1] << ","
                  << theta[2] << "]" << std::endl;

        // double x1[] = { 1.0, 0.0, (150-mu)/sigma };
        ml::version1::matrix x1(1,3);
        x1(0,0) = 1.0;
        x1(0,1) = 0.0;
        x1(0,2) = (150.0 - mu) / sigma;
        auto predict1 = hypothesis(x1, theta)[0];
        std::cout << "Pour une femme d'une taille de 150cm, on prédit un poids de " << predict1 << "kg" << std::endl;
        // double x2[] = { 1.0, 0.0, (175-mu)/sigma };
        ml::version1::matrix x2(1,3);
        x2(0,0) = 1.0;
        x2(0,1) = 0.0;
        x2(0,2) = (175.0 - mu) / sigma;
        auto predict2 = hypothesis(x2, theta)[0];
        std::cout << "Pour une femme d'une taille de 175cm, on prédit un poids de "
                  << predict2 << "kg" << std::endl;
        // double x3[] = { 1.0, 1.0, (168-mu)/sigma };
        ml::version1::matrix x3(1,3);
        x3(0,0) = 1.0;
        x3(0,1) = 1.0;
        x3(0,2) = (168 - mu) / sigma;
        auto predict3 = hypothesis(x3, theta)[0];
        std::cout << "Pour un homme d'une taille de 168cm, on prédit un poids de "
                  << predict3 << "kg" << std::endl;
        // double x4[] = { 1.0, 1.0, (195-mu)/sigma };
        ml::version1::matrix x4(1,3);
        x4(0,0) = 1.0;
        x4(0,1) = 1.0;
        x4(0,2) = (195 - mu) / sigma;
        auto predict4 = hypothesis(x4, theta)[0];
        std::cout << "Pour un homme d'une taille de 195cm, on prédit un poids de "
                  << predict4 << "kg" << std::endl;

        return 0;
}
