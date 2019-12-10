//
//  NeuralNet.h
//  Projet C++
//
//  Created by EL BAZ on 10/06/2019.
//  Copyright © 2019 EL BAZ. All rights reserved.
//

#ifndef NeuralNet_h
#define NeuralNet_h
/// NN1 ///

class Perceptron_cache : public Perceptron{
    private:
    std::vector<Perceptron*> percep_pointeur;
    public :
    Perceptron_cache(int ,Fonction_activation *, char , std::vector<Perceptron *> &);
    double calcul_delta( Input &);
    void backprop(Input &, double mu);
    
    
};

Perceptron_cache::Perceptron_cache(int taille_input, Fonction_activation *fc, char lab, std::vector<Perceptron*> &percept_sortie) : Perceptron(taille_input, fc, lab){
    // COMMENT construire le nouveau vecteur
    percep_pointeur=percept_sortie;
    // Le label est géré directement par le constructeur, pas besoin d'utiliser un fonction membre statique
    
    // par contre attention à l'allocation du veteur de pointeurs
    
    
}
double Perceptron_cache::calcul_delta(Input & inp){
    double prod_temp = 0 ;
    double delta = 0, res = 0;
    double z = 0;
    
    for(std::vector<double>::iterator it = poids.begin() + 1 ;it != poids.end();it++)z += *(it) * inp[int(it-poids.begin())];
    // Rappel : on effectue le produit scalaire dans le poids 0 que l'on ajoute simplement dans le fc->prim()

    
    for(std::vector<Perceptron*>::iterator it = percep_pointeur.begin() ;it != percep_pointeur.end();it++){
        delta = (*it)->get_delta();
        
        prod_temp += delta * ( (*it)->get_poids(int (label)));
        // Remarque : on utilise label ici, car on veut avoir le poids associé à ce perceptron spécifique de la couche cachée. La seule information pour connaitre le petit s dans la formule, c'esst d'utiliser l'indice du perceptron grâce au label.
        
        //delta*((it->get_poids[int(it - percep_pointeur.begin())]));

    }
    res = fc->prim( poids[0] +z) * prod_temp ;
    delta_prec = res;
    return res ;
}
void Perceptron_cache::backprop(Input & inp, double mu){
    poids[0]=poids[0] - mu*(this->get_delta());
    for(std::vector<double>::iterator it = poids.begin() + 1 ;it != poids.end();it++){
        *(it)= *(it) - mu * (this->get_delta()) * inp[int(it-poids.begin())];
    }
}



class Input_intermediaire : public Input{
    private :
    std::vector<double> a_1;
    public :
    Input_intermediaire(char);
    void add(double);
    double& operator[](int );
    
};
// Créer enventuellement un constructeur vide
Input_intermediaire::Input_intermediaire(char lab){
    this->label=lab;
    
    
    
}
void Input_intermediaire::add(double val){
    a_1.push_back(val);
}

double& Input_intermediaire::operator[](int idx){
    return a_1[idx];
}



class NN2{
    private :
    std::vector<Perceptron*> percep;
    std::vector<Perceptron_cache> percep_cache;
    
    public :
    NN2(int , int , int , Fonction_activation *);
    char evaluation(Input &);
    void apprentissage(Input &, double mu);
    
};
NN2::NN2(int taille_input, int nbr_categorie, int nbr_perc_cache, Fonction_activation *fc_act){
    // Dans un premier temps, on va créer les perceptrons de la couche sortie
    // On leur assigne le label correspondant, et la taille de l'input est le nombre de perceptrons de la couche cahchée
    for (int i(0); i < nbr_categorie ; i++){
        percep.push_back(new Perceptron(nbr_perc_cache, fc_act, '0'+i));
    }
    // Ensuite on doit créer les perceptrons de la couche cachée
    // La taille des inputs est celle initiale et le label associé est l'indice du percep caché
    for (int i(0); i < nbr_perc_cache ; i++){
        percep_cache.push_back(Perceptron_cache(taille_input, fc_act, '0' + i, percep));
    }
}

char NN2::evaluation(Input & inp){
    char res;
    int maxElementIndex = 0;
    Input_intermediaire a_temp(inp.get_label());
    std::vector<double> vals_sortie;
    //std::vector<double> a_temp;
    for(std::vector<Perceptron_cache>::iterator it = percep_cache.begin() ;it != percep_cache.end();it++){
        a_temp.add(it->forward(inp));
    }
    for(std::vector<Perceptron*>::iterator it = percep.begin() ;it != percep.end();it++){
        vals_sortie.push_back((*it)->forward(a_temp));
    }
    maxElementIndex = std::max_element(vals_sortie.begin(),vals_sortie.end()) - vals_sortie.begin();
    res= percep[maxElementIndex]->label;
    
    return res;
}
void NN2::apprentissage(Input & inp, double mu){
    Input_intermediaire a_temp(inp.get_label());
    // Input intermédiaire pour effectuer la MAJ sur la couche sortie d'abord
    for(std::vector<Perceptron_cache>::iterator it = percep_cache.begin(); it != percep_cache.end(); it++ ){
        a_temp.add(it->forward(inp));
    }
    // MAJ COUCHE SORTIE
    for(std::vector<Perceptron*>::iterator it = percep.begin(); it != percep.end(); it++ ){
        (*it)->calcul_delta(a_temp);
        (*it)->backprop(a_temp, mu);
    }
    // PROPAGATION
    for(std::vector<Perceptron_cache>::iterator it = percep_cache.begin(); it != percep_cache.end(); it++ ){
        it->calcul_delta(inp);
        it->backprop(inp, mu);
    }
    
    // détruire l'objet a_temp ?
    
}




#endif /* NeuralNet_h */
