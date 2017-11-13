#include <iostream>
#include <fstream>
#include <math.h>

// jeu de données (poids, taille)
// pour un ensemble de 50 femmes
// et 50 hommes
double data[] = {
        0,149.633,46.3073,
        0,165.684,64.0963,
        0,160.957,59.4404,
        0,163.779,58.1386,
        0,156.954,58.8688,
        0,167.559,71.1254,
        0,159.64,52.15,
        0,166.756,74.8816,
        0,157.201,50.6563,
        0,161.742,47.2431,
        0,172.977,75.5587,
        0,156.969,48.1876,
        0,160.964,58.1144,
        0,149.596,46.1232,
        0,148.433,44.5402,
        0,154.457,57.5689,
        0,178.127,68.6089,
        0,158.134,52.5257,
        0,156.807,48.9284,
        0,160.171,66.0396,
        0,158.209,63.2875,
        0,157.042,55.6867,
        0,168.523,71.388,
        0,165.914,65.789,
        0,167.904,67.4255,
        0,163.899,60.184,
        0,143.632,38.498,
        0,159.358,62.8374,
        0,156.426,62.3361,
        0,157.542,56.5203,
        0,165.891,63.625,
        0,155.461,49.1204,
        0,170.244,68.1394,
        0,152.936,53.9954,
        0,162.408,63.2754,
        0,160.929,56.9782,
        0,161.76,60.0036,
        0,153.134,59.168,
        0,161.055,58.4456,
        0,154.004,49.7689,
        0,171.129,66.2362,
        0,169.857,72.0567,
        0,152.52,51.9842,
        0,162.952,60.3916,
        0,161.193,58.4922,
        0,170.799,69.8823,
        0,168.183,63.0509,
        0,164.32,62.9056,
        0,168.146,81.9648,
        0,167.268,67.6402,
        1,187.571,109.723,
        1,174.706,73.624,
        1,188.24,96.4993,
        1,182.197,99.8113,
        1,177.5,93.6003,
        1,170.823,69.0434,
        1,174.714,83.4297,
        1,173.605,76.1917,
        1,170.228,79.8016,
        1,161.179,70.9429,
        1,180.836,84.644,
        1,181.968,96.953,
        1,164.506,75.809,
        1,175.979,85.9328,
        1,175.879,84.5665,
        1,171.82,78.104,
        1,183.943,88.9185,
        1,162.495,78.4199,
        1,176.886,84.3623,
        1,172.557,82.7487,
        1,172.504,78.979,
        1,176.376,89.691,
        1,168.019,67.6651,
        1,191.023,103.766,
        1,172.449,73.4862,
        1,173.086,87.2472,
        1,175.488,83.6598,
        1,184.914,93.8173,
        1,171.25,79.477,
        1,173.981,70.0098,
        1,174.29,85.0531,
        1,188.046,96.5761,
        1,181.682,88.4666,
        1,175.718,93.0713,
        1,176.726,92.6088,
        1,178.818,87.501,
        1,175.453,89.5807,
        1,170.672,83.3767,
        1,167.151,74.3232,
        1,163.333,73.9858,
        1,172.655,78.0807,
        1,183.361,88.019,
        1,165.787,76.485,
        1,167.869,73.1173,
        1,171.476,74.6899,
        1,178.066,85.6952,
        1,173.36,84.8507,
        1,183.319,94.8345,
        1,175.717,87.0977,
        1,185.091,95.865
};

const auto m = 100;

void separation_donnees(double x[m][3], double y[m]){
        auto k = 0;
        for(auto i = 0; i<m; i++) {
                x[i][0] = 1;
                for(auto j = 1; j<3; j++) {
                        x[i][j] = data[k];
                        k++;
                }
                y[i] = data[k];
                k++;
        }
}

void affichageX(double x[m][3]){
        for(auto i = 0; i<m; i++) {
                for(auto j = 0; j<3; j++) {
                        std::cout<<"x["<<i<<"]["<<j<<"] = "<<x[i][j]<<std::endl;
                }
        }
}

void affichageY(double y[m]){
        for(auto i = 0; i<m; i++) {
                std::cout<<"y["<<i<<"] = "<<y[i]<<std::endl;
        }
}

auto hypothesis(double x[3], double theta[3]){
        return theta[0]*x[0] + theta[1]*x[1] + theta[2]*x[2];
}

auto hypothesisNormalise(double x[3], double theta[3], double moy, double eT){
        return theta[0]*x[0] + theta[1]*x[1] + theta[2] * ((x[2] - moy)/eT);
}

auto computeCost(double x[m][3], double y[m], double theta[3]){
        double res = 0.0, temp = 0.0;
        for(int i = 0; i<m; i++) {
                temp = hypothesis(x[i], theta) - y[i];
                res += temp * temp;
        }
        res *= 1.0/(2.0*m);
        return res;
}

auto moyenne(double x[m][3], int j){
        double u = 0;
        for(int i = 0; i<m; i++) {
                u += x[i][j];
        }
        u *= (1.0/m);
        return u;
}

auto ecartType(double x[m][3], int j){
        double sigma = 0;
        double moy = moyenne(x, j);

        for(int i = 0; i<m; i++) {
                sigma += (x[i][j] - moy)*(x[i][j] - moy);
        }

        sigma *= 1.0/(m-1.0);
        sigma = sqrt(sigma);
        return sigma;
}

void normalisation(double x[m][3], int j){
        double moy = moyenne(x, j);
        double ET = ecartType(x, j);
        for(int i = 0; i<m; i++) {
                x[i][j] = (x[i][j] - moy)/ET;
        }
}

void gradientDescent(double x[m][3], double y[m], double theta[3], double alpha, int iteration) //Minimisation de J(theta)
{
        std::ofstream fichier("cost.txt", std::ios::out | std::ios::trunc);

        if(!fichier) {
                std::cerr << "Erreur d'ouverture de fichier costm.txt"<<std::endl;
                exit(1);
        }
        double c = alpha / m, h;
        double u0, u1, u2;
        for(int k = 0; k<iteration; k++) {
                u0 = 0; u1 = 0; u2 = 0;
                for(int i = 0; i<m; i++) {
                        h = hypothesis(x[i], theta) - y[i];
                        u0 += c*h;
                        u1 += c*h*x[i][1];
                        u2 += c*h*x[i][2];
                }
                theta[0] = theta[0] - u0;
                theta[1] = theta[1] - u1;
                theta[2] = theta[2] - u2;
                //Sauvegarder theta dans un fichier : costm.txt
                fichier << computeCost(x, y, theta)<< std::endl;
        }
        fichier.close();
}

int main()
{
        double x[m][3], y[m];
        //x[0][0] = 1, x[0][1] = sexe, x[0][2]=  taille, y[0] = poids
        separation_donnees(x, y);
        // affichageX(x);
        // affichageY(y);

        //Déclaration des theta de test
        double theta1[] = {1.0, 2.0, 3.0};
        double theta2[] = {2.0, 2.5, 3.5};
        double theta3[] = {0.5, 2.9, 3.9};
        double theta4[] = {4.9, 2.2, 1.1};

        //Test pour l'hypothèse
        std::cout<<"verification hypothesis(x[11],theta1) = "<<hypothesis(x[11], theta1)<<std::endl;
        std::cout<<"verification hypothesis(x[33],theta1) = "<<hypothesis(x[33], theta2)<<std::endl;
        std::cout<<"verification hypothesis(x[55],theta1) = "<<hypothesis(x[55], theta3)<<std::endl;
        std::cout<<"verification hypothesis(x[77],theta1) = "<<hypothesis(x[77], theta4)<<std::endl;

        //Test pour computeCost
        std::cout<<"verification computeCost(x,y,theta1) = "<<computeCost(x, y, theta1)<<std::endl;
        std::cout<<"verification computeCost(x,y,theta2) = "<<computeCost(x, y, theta2)<<std::endl;
        std::cout<<"verification computeCost(x,y,theta3) = "<<computeCost(x, y, theta3)<<std::endl;
        std::cout<<"verification computeCost(x,y,theta4) = "<<computeCost(x, y, theta4)<<std::endl;

        //Test pour la moyenne d'une caractéristique
        std::cout<<"La moyenne pour la taille est "<<moyenne(x, 2)<<std::endl;

        //Test pour l'écart type
        std::cout<<"L'écart type pour la taille est "<<ecartType(x, 2)<<std::endl;

        double moy = moyenne(x, 2);
        double eT = ecartType(x, 2);

        //Normalisation des tailles
        normalisation(x, 2);

        double theta[] = {0.0, 0.0, 0.0};
        gradientDescent(x, y, theta, 0.1, 50);

        std::cout<<"Theta[0] = "<<theta[0]<<", Theta[1] = "<<theta[1]<<", Theta[2] = "<<theta[2]<<std::endl;

        //Question 8 : prédictions
        double femme1[] = {1.0, 0.0, 150.0};
        double femme2[] = {1.0, 0.0, 175.0};
        double homme1[] = {1.0, 1.0, 168.0};
        double homme2[] = {1.0, 1.0, 195.0};

        //Calcul moyenne et écart type pour les valeurs normalisés


        std::cout<<"Le poids d'une femme de 150cm est "<<hypothesisNormalise(femme1, theta, moy, eT) <<std::endl;
        std::cout<<"Le poids d'une femme de 175cm est "<<hypothesisNormalise(femme2, theta, moy, eT) <<std::endl;
        std::cout<<"Le poids d'un homme de 168cm est "<<hypothesisNormalise(homme1, theta, moy, eT) <<std::endl;
        std::cout<<"Le poids d'un homme de 195cm est "<<hypothesisNormalise(homme2, theta, moy, eT) <<std::endl;

        return 0;
}
