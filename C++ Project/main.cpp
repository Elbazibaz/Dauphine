//
//  main.cpp
//  Projet C++
//
//  Created by EL BAZ on 08/06/2019.
//  Copyright © 2019 EL BAZ. All rights reserved.
//
#include <algorithm>
#include <fstream>
#include <iostream>
#include <math.h>
#include <time.h>
#include <vector>
#include "Extraction.h"
#include "Fonct_activation.h"
#include "Perceptron.h"
#include "NeuralNet1.h"
#include "NeuralNet2.h"

int main(int argc, const char * argv[]) {


    int Resultat_NN2_image_sigmo;
    //int Resultat_NN1_image_tanh;
    int Resultat_NN2_iris_sigmo;
    //int Resultat_NN1_iris_tanh;
    
    // Fonctions d'activation
    
    Tanh * fonction_tanh = new Tanh;
    //Sigmoide *fonction_sigmo = new Sigmoide;

    // Neural networks
    
    NN1 *net_image = new NN1(784,10, fonction_tanh);
    NN1 *net_iris = new NN1(4, 3, fonction_tanh);
    
    //NN2 *net2_image = new NN2(784,10,10,fonction_tanh);
    //NN2 *net2_iris = new NN2(4,3,10,fonction_tanh);
    
    
    // NN IMAGE
    Apprentissage<Image,NN1, 60000> app_fonc(net_image);
    app_fonc.apprendre_base(10000, 0.01);
    Resultat_NN2_image_sigmo= app_fonc.evaluer();
    std::cout<<Resultat_NN2_image_sigmo<<std::endl;
    std::cout<<double(Resultat_NN2_image_sigmo)/60000<<std::endl;
    
    
    /// NN IRIS
    Apprentissage<Iris,NN1, 150> app_fonc_iris(net_iris);
    app_fonc_iris.apprendre_base(15000, 0.1);
    Resultat_NN2_iris_sigmo= app_fonc_iris.evaluer();
    std::cout<<Resultat_NN2_iris_sigmo<<std::endl;
    std::cout<<double(Resultat_NN2_iris_sigmo)/150<<std::endl;
    delete fonction_tanh;
    //delete net2_image;
    //delete net2_iris;
    delete net_image;
    delete net_iris;
    
    
    
    return 0;
}
