//
//  Neural1.h
//  Projet C++
//
//  Created by EL BAZ on 11/06/2019.
//  Copyright © 2019 EL BAZ. All rights reserved.
//
#ifndef Neural1_h
#define Neural1_h
class Perceptron;
class NN1{
private:
    std::vector<Perceptron> percep;
    public :
    NN1(int , int, Fonction_activation*);
    char evaluation(Input &);
    void apprentissage( Input &, double);
    
};

NN1::NN1(int taille_input, int nbr_categorie, Fonction_activation *fc_act){
    
    for (int i(0); i<nbr_categorie;i++){
        percep.push_back(Perceptron(taille_input, fc_act, '0'+i));
    }
    
    
}

char NN1::evaluation(Input &inp){
    char res;
    long taille = percep.size();
    long maxElementIndex = 0;
    std::vector<double> val;
    //strcmp(typeid(inp).name(), "Iris") ( dans le if )
    if( taille== 3){ // le typeid().name contient IRIS mais autre chose, éventuellement utiliser regex mais valeur retour mal maitriser mieux vaut utiliser un compteur sur le vector
        //double val[3];
        //const int N= sizeof(val)/sizeof(double);
        for (int i(0); i<3;i++)val.push_back(percep[i].forward(inp));
        //percep[i].forward(inp);
        maxElementIndex = std::max_element(val.begin(),val.end()) - val.begin();

        res= percep[maxElementIndex].label;
    }
    else{
        //double val[10];
        //const int N= sizeof(val)/sizeof(double);
        for (int i(0); i<10; i++)val.push_back( percep[i].forward(inp));
        //idx= std::distance(val, std::max_element(val, val +N));
        maxElementIndex = std::max_element(val.begin(),val.end()) - val.begin();
        res= percep[maxElementIndex].label;
    }
    
    return res;
}

void NN1::apprentissage(Input &inp, double mu){
    double temp;
    for(std::vector<Perceptron>::iterator it = percep.begin() ;it != percep.end();it++){
        temp=it->calcul_delta(inp);
        it->backprop(inp, mu);
        
    }
    
}


template <class T,class U, int s> class Apprentissage{
private:
    U *neural_net;
public:
    Apprentissage(U *);
    void apprendre_base(int, double);
    int evaluer();
};

template <class T,class U, int s>Apprentissage<T,U,s>::Apprentissage(U * nn){
    neural_net=nn;
}
template <class T,class U, int s> void Apprentissage<T,U,s>::apprendre_base(int K, double mu){
    int idx_alea;
    for(int i(0);i<K;i++){
        idx_alea= rand()%(s+1) ;
        T temp(idx_alea);
        
        neural_net->apprentissage(temp, mu);
    }
}
template<class T,class U, int s> int Apprentissage<T,U,s>::evaluer(){
    int count=0;
    char tmp;
    for (int i(0); i<s; i++){
        T temp(i);
        
        //Input * input=T(i);
        tmp=neural_net->evaluation(temp);
        if(temp.get_label()== tmp)count+=1; 
    }
    return count;
}



#endif /* Neural1_h */
