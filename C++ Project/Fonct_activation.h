//
//  NN.h
//  Projet C++
//
//  Created by EL BAZ on 09/06/2019.
//  Copyright © 2019 EL BAZ. All rights reserved.
//
#ifndef NN_h
#define NN_h
                    /// CLASSE ABSTRAITE ///
class Fonction_activation{

public:
    virtual double operator()(double) = 0;
    virtual double prim(double) = 0;
     // On définit les 2 en virtuelles, car on veut pouvoir utiliser le polymorphisme sur ces deux fonctions
};



                    /// CLASSE TANH ///

class Tanh : public Fonction_activation{

public:
    double operator()(double);
    double prim(double);
};
double Tanh::operator()(double d){
    return (exp(d)-exp(-d))/(exp(d) + exp(-d));
    // ON A CHANGE EN DOUBLE LA VALEUR DE RETOUR ET NON PLUS double&
}

double Tanh::prim(double d){
    double temp = (*this).operator()(d);
    
    return (1- temp*temp); // peut faire mieux en stockant la valeur ou trouver la fonction carré dans math.h
    
}
// On peut utliser le this, mais this est un pointeur donc on utilise * pour avoir l'objet





                    /// CLASSE SIGMOIDE ///
class Sigmoide : public Fonction_activation{
public:
    double operator()(double);
    double prim(double);
    
};

double Sigmoide::operator()(double d){
    return (1/(1 + exp(-d)));
    
}
double Sigmoide::prim(double d){
    double temp =(*this)(d);
    return (1- temp)*temp; // peut faire mieux en stockant la valeur ou trouver la fonction carré dans math.h
    
}
#endif /* NN_h */
