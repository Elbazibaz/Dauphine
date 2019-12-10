//
//  Header.h
//  Projet C++
//
//  Created by EL BAZ on 08/06/2019.
//  Copyright © 2019 EL BAZ. All rights reserved.
//
# include <string.h>

#ifndef Header_h
#define Header_h
class Input{
protected:
    char label;
public:
    char get_label();
    virtual double& operator[](int) = 0;  
};

char Input::get_label(){
    return label;
}
                    /// CLASSE IRIS ///
class Iris : public Input{
private :
    double tab[4];
public:
    Iris(int);
    double& operator[](int);
    void afficher();
    
};
void Iris::afficher(){
    std::cout<<tab[0]<<std::endl<<tab[1]<<std::endl<<tab[2]<<std::endl<<tab[3]<<std::endl<<label<<std::endl;
}
Iris::Iris(int index) {
    // Dans cette partie on charge les données provenant du fichier iris_training.tar.gz
    std::string fichier, temp5;
    //int temp5bis;
    char c,c1,c2;
    double temp1,temp2,temp3,temp4;
    fichier="iris"+std::to_string(index);
    //std::cout<<fichier<<std::endl;
    std::ifstream in("/Users/adrian/Desktop/data/iris_training/"+fichier,std::ios::in);
    //in.seekg(10)

    in >>temp1>>c>>temp2>>c1>>temp3>>c2>>temp4;
    if((in) && c==',' && c1==',' && c2==','){
        tab[0]=temp1;
        tab[1]=temp2;
        tab[2]=temp3;
        tab[3]=temp4;
    }
    in>>c>>temp5;
    //std::cout<<"LABEL : "<<temp5<<std::endl;
    if((in) && c ==','){
        if(!temp5.compare("Iris-setosa"))label='0';
        else if (!temp5.compare("Iris-virginica")) label='1';
        else label='2';
    }
    //this.label= "?";
    in.close();
    
    /// CODE /// SETOSA : label 0 ; VIRGINICA : label 1 ; VERSICOLOR : label 2;
}

double& Iris::operator[](int index){
    // on peut ajouter un traitement d'exception pour que l'indice corresponde; encore faut il que cette méthode soit accessible à un utilisateur
    return tab[index];
}


                    /// CLASSE IMAGE ///

class Image : public Input{
    private:
        double tab[28*28]; // mettre des entiers
    public:
        Image(int);
        double& operator[](int);
        void afficher();
    
    
};
Image::Image(int index){
    std::string fichier;
    unsigned char c2;
    int tmpdb;
    //std::cout<<c3<<std::endl;
    //double temp1,temp2,temp3,temp4;
    fichier="training"+std::to_string(index);
    //std::cout<<fichier<<std::endl;
    std::ifstream in("/Users/adrian/Desktop/data/MNIST_training/"+fichier,std::ios::binary);
    in.seekg(1078, std::ios::beg);
    if(in){
        for (int i(0); i < 28*28; i++){
            in.read((char *)&c2, sizeof(unsigned char));
            tab[i]=int(c2);
        }
    }

    
    in.close();
    
    /// ATTENTION CETTE PARTIE N'EST PAS GERE ENCORE. TOUT LE RESTE OUI, MAIS CETTE EXTRACTION DE LABEL NON.
    std::ifstream in1("/Users/adrian/Desktop/data/train-labels-idx1-ubyte", std::ios::binary);
    // le fichier est bien ouvert
    in1.seekg(8+index,std::ios::beg);
    if(in1){
        tmpdb = in1.get();
        //std::cout<<tmpdb<<std::endl;
        //std::cout<<in1.get()<<std::endl;
        //std::cout<<char(c3)<<std::endl;
        //in1.read((char *)&c3, sizeof(char));
        label= '0' + tmpdb;
        //std::cout<<label<<std::endl;
    }
    //c3=c2;
    //std::cout<<c3<<std::endl;
    in1.close();
    
}

void Image::afficher(){
    std::cout<<label<<std::endl;
    
    
}

double& Image::operator[](int index){
    return tab[index];
}


#endif /* Header_h */
