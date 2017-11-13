#include <iostream>
#include <fstream>

// jeu de données (poids, taille)
// pour un ensemble de 50 femmes
double data[] = {
        149.633,46.3073,
        165.684,64.0963,
        160.957,59.4404,
        163.779,58.1386,
        156.954,58.8688,
        167.559,71.1254,
        159.64,52.15,
        166.756,74.8816,
        157.201,50.6563,
        161.742,47.2431,
        172.977,75.5587,
        156.969,48.1876,
        160.964,58.1144,
        149.596,46.1232,
        148.433,44.5402,
        154.457,57.5689,
        178.127,68.6089,
        158.134,52.5257,
        156.807,48.9284,
        160.171,66.0396,
        158.209,63.2875,
        157.042,55.6867,
        168.523,71.388,
        165.914,65.789,
        167.904,67.4255,
        163.899,60.184,
        143.632,38.498,
        159.358,62.8374,
        156.426,62.3361,
        157.542,56.5203,
        165.891,63.625,
        155.461,49.1204,
        170.244,68.1394,
        152.936,53.9954,
        162.408,63.2754,
        160.929,56.9782,
        161.76,60.0036,
        153.134,59.168,
        161.055,58.4456,
        154.004,49.7689,
        171.129,66.2362,
        169.857,72.0567,
        152.52,51.9842,
        162.952,60.3916,
        161.193,58.4922,
        170.799,69.8823,
        168.183,63.0509,
        164.32,62.9056,
        168.146,81.9648,
        167.268,67.6402
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
        std::ofstream fichier("costf.txt", std::ios::out | std::ios::trunc);

        if(!fichier) {
                std::cerr << "Erreur d'ouverture de fichier costf.txt"<<std::endl;
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

        { // prédictions
                std::cout<<"Pour une femme de taille 168cm, on prédit un poids de " <<hypothesis(168.0, theta)<< "kg." <<std::endl;
                std::cout<<"Pour une femme de taille 195cm, on prédit un poids de " <<hypothesis(195.0, theta)<< "kg." <<std::endl;
        }

        std::ofstream file("dataf.txt");
        for(auto i = 0; i < m; ++i) {
                file << x[i] << " " << y[i] << std::endl;
        }

        return 0;
}
