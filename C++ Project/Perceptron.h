//
//  Perceptron.h
//  Projet C++
//
//  Created by EL BAZ on 09/06/2019.
//  Copyright © 2019 EL BAZ. All rights reserved.
//


#ifndef Perceptron_h
#define Perceptron_h

class NN1;
class NN2;

class Perceptron{
 
protected: // ensemble des poids
    Fonction_activation *fc; // ici le pointeur va permettre la conversion de pointeurs de la classe dérivée !
    char label;
    std::vector<double> poids;// on utilise le conteneur vector, l'accès est en o(1)
    double delta_prec;
public:
    Perceptron(int, Fonction_activation*, char);
    double get_poids(int);
    double forward(Input & );
    double calcul_delta(Input &);
    double get_delta();
    void backprop(Input &, double mu);
    friend class NN1;
    friend class NN2;
    // Ces déclarations d'amitié sont pour les fonctions evaluer des deux classes NN1 et NN2. En effet, on a besoin d'accéder au label d'un perceptron pour renvoyer le label dont la valeur du forward du perceptron associé est max.
    
    
};
Perceptron::Perceptron(int taille_input, Fonction_activation *fc_act, char lab){
    // Fonction activation
    fc=fc_act;
    // Initialisation des poids entre -1 et 1 aléatoirement
    for (int i(0); i<taille_input;i++){
        //poids.push_back((rand()/(double)RAND_MAX)*(1+1)-1);
        poids.push_back(rand()%3 -1);
    }
    // Initialisation label
    label=lab;
}
double Perceptron::get_poids(int index){
    return poids[index];
}

double Perceptron::forward(Input &inp){
    double prod_sca =0;
    for(std::vector<double>::iterator it = poids.begin() + 1 ;it != poids.end();it++)prod_sca += *(it) * inp[int(it-poids.begin())];
    return fc->operator()(poids[0] + prod_sca);
}
double Perceptron::calcul_delta(Input &inp){
    double test_label=0;
    double res = 0, prod_sca=0;
    for(std::vector<double>::iterator it = poids.begin() + 1 ;it != poids.end();it++){
        prod_sca += *(it) * inp[int(it-poids.begin())];
        //std::cout<<prod_sca<<std::endl;
    }
    if(label==inp.get_label()){
        test_label=1;
    }
    //std::cout<<prod_sca<<std::endl;
    res= fc->prim(poids[0] + prod_sca) * (fc->operator()(poids[0] + prod_sca) - test_label);
    //std::cout<<fc->prim(poids[0] + prod_sca)<<std::endl;

    this->delta_prec=res;
    return res;
}


double Perceptron::get_delta(){
    return delta_prec;
}

void Perceptron::backprop(Input & inp, double mu){
    poids[0]=poids[0] - mu*(this->get_delta());
    for(std::vector<double>::iterator it = poids.begin() + 1 ;it != poids.end();it++){
        *(it)= *(it) - mu * (this->get_delta()) * inp[int(it-poids.begin())];
    }
    
}

/// NN1 ///


#endif /* Perceptron_h */
