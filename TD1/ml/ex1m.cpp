#include <iostream>
#include <fstream>

// jeu de données (poids, taille)
// pour un ensemble de 50 hommes
double data[] = {
        187.571,109.723,
        174.706,73.624,
        188.24,96.4993,
        182.197,99.8113,
        177.5,93.6003,
        170.823,69.0434,
        174.714,83.4297,
        173.605,76.1917,
        170.228,79.8016,
        161.179,70.9429,
        180.836,84.644,
        181.968,96.953,
        164.506,75.809,
        175.979,85.9328,
        175.879,84.5665,
        171.82,78.104,
        183.943,88.9185,
        162.495,78.4199,
        176.886,84.3623,
        172.557,82.7487,
        172.504,78.979,
        176.376,89.691,
        168.019,67.6651,
        191.023,103.766,
        172.449,73.4862,
        173.086,87.2472,
        175.488,83.6598,
        184.914,93.8173,
        171.25,79.477,
        173.981,70.0098,
        174.29,85.0531,
        188.046,96.5761,
        181.682,88.4666,
        175.718,93.0713,
        176.726,92.6088,
        178.818,87.501,
        175.453,89.5807,
        170.672,83.3767,
        167.151,74.3232,
        163.333,73.9858,
        172.655,78.0807,
        183.361,88.019,
        165.787,76.485,
        167.869,73.1173,
        171.476,74.6899,
        178.066,85.6952,
        173.36,84.8507,
        183.319,94.8345,
        175.717,87.0977,
        185.091,95.865
};

const auto m = 50;

auto hypothesis(double x, double theta[2])
{
        return theta[0]+(theta[1]*x);
}

auto computeCost(double x[m], double y[m], double theta[2])
{
        double res = 0.0, temp = 0.0;
        for(int i = 0; i<m; i++) {
                temp = hypothesis(x[i], theta) - y[i];
                res += temp * temp;
        }
        res *= 1.0/(2.0*m);
        return res;
}

void gradientDescent(double x[m], double y[m], double theta[2], double alpha, int iteration)
{
        std::ofstream fichier("costm.txt", std::ios::out | std::ios::trunc);

        if(!fichier) {
                std::cerr << "Erreur d'ouverture de fichier costm.txt"<<std::endl;
                exit(0);
        }
        double c = alpha / m, h;
        double u0, u1;
        for(int k = 0; k<iteration; k++) {
                u0 = 0; u1 = 0;
                for(int i = 0; i<m; i++) {
                        h = hypothesis(x[i], theta) - y[i];
                        u0 += c*h;
                        u1 += c*h*x[i];
                }
                theta[0] = theta[0] - u0;
                theta[1] = theta[1] - u1;
                //Sauvegarder theta dans un fichier : costm.txt
                fichier << computeCost(x, y, theta)<< std::endl;
        }
        fichier.close();
}

void separation_data(double x[], double y[]){
        int adrX = 0, adrY = 0;
        for(int i = 0; i<100; i++) {
                if(i%2) { //Impaire : taille
                        y[adrY] = data[i];
                        adrY += 1;
                }
                else{ //Paire : Poids
                        x[adrX] = data[i];
                        adrX += 1;
                }
        }
}

int main()
{
        double x[m], y[m];

        std::cout << "recopie de data dans les vecteurs x et y" << std::endl;
        separation_data(x, y);

        { // verification de l'hypothèse
                std::cout << "Vérification de l'hypothèse : "<< std::endl;
                double theta[] = {1.0, 2.0};
                std::cout << "Verification hypothesis(x[11], theta1) = "<<hypothesis(x[11], theta)<<std::endl;
                theta[0] = 2.0; theta[1] = 2.5;
                std::cout << "Verification hypothesis(x[22], theta2) = "<<hypothesis(x[22], theta)<<std::endl;
                theta[0] = 0.5; theta[1] = 2.9;
                std::cout << "Verification hypothesis(x[33], theta3) = "<<hypothesis(x[33], theta)<<std::endl;
                theta[0] = 4.9; theta[1] = 2.2;
                std::cout << "Verification hypothesis(x[44], theta4) = "<<hypothesis(x[44], theta)<<std::endl;
        }

        { // verification de la fonction de cout
                std::cout<<"Vérification de la fonctione de cout : "<<std::endl;
                double theta[] = {1.0, 2.0};
                std::cout << "Verification computeCost(x, y, theta1) = "<<computeCost(x, y, theta)<<std::endl;
                theta[0] = 2.0; theta[1] = 2.5;
                std::cout << "Verification computeCost(x, y, theta2) = "<<computeCost(x, y, theta) <<std::endl;
                theta[0] = 0.5; theta[1] = 2.9;
                std::cout << "Verification computeCost(x, y, theta3) = "<<computeCost(x, y, theta) <<std::endl;
                theta[0] = 4.9; theta[1] = 2.2;
                std::cout << "Verification computeCost(x, y, theta4) = "<<computeCost(x, y, theta) <<std::endl;
        }

        std::cout << "recherche des paramètres theta optimaux" << std::endl;

        double theta[] = { 0.0, 0.0 };

        auto iterations = 20;
        auto alpha = 0.00001;

        gradientDescent(x, y, theta, alpha, iterations);

        std::cout << "paramètre theta obtenu : ["
                  << theta[0] << ","
                  << theta[1] << "]" << std::endl;

        { // Prédictions
                std::cout<<"Pour un homme de taille 168cm, on prédit un poids de " <<hypothesis(168.0, theta)<< "kg." <<std::endl;
                std::cout<<"Pour un homme de taille 195cm, on prédit un poids de " <<hypothesis(195.0, theta)<< "kg." <<std::endl;
        }

        std::ofstream file("datam.txt");
        for(auto i = 0; i < m; ++i) {
                file << x[i] << " " << y[i] << std::endl;
        }

        return 0;
}
