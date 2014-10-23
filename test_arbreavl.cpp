/*
  INF3105 - Structures de données et algorithmes
  
  Auteur : Éric Beaudry (beaudry.eric@uqam.ca)

  Pour compilter : g++ test_arbreavl.cpp
*/

#include <iostream>
#include "arbreavl.h"

bool test1();
bool test2();
bool test3();
bool test4();
bool test5a();
bool test5b();
bool test6();
bool test7();
bool test8();

int main(int argc, const char** argv)
{
    bool testsreussis =
        true // Cette ligne est uniquement là afin de pouvoir mettre la ligne suivante en commentaire sans enlever le && de la 2e ligne suivante!
        && test1()
        && test2()
        && test3()
     //   && test4()
        && test5a()
        && test5b()
        && test6()
        && test7()
        && test8()
        ;

    if(testsreussis){
        std::cout << " ==> BRAVO, tous les tests ont été réussis!" << std::endl;
        std::cout << " ==> Toutefois, cela ne veut pas dire qu'il n'y a pas de bogues. Soyez vigilant!" << std::endl;
    }else{
        std::cout << " ==> Au moins un test n'a pas été réussi." << std::endl;
        std::cout << " ==> Lâchez pas!" << std::endl;
    }   
    return testsreussis ? 0 : 1;
}

/*
  Les itérateurs ont besoin de la classe Pile.
*/
bool test1()
{
    std::cout << "Test #1 : Test de la pile (opérations de base)" << std::endl;
    int nberreurs=0;
    Pile<int> pile1;
    pile1.empiler(1);
    pile1.empiler(4);
    pile1.empiler(2);
    if(pile1.depiler() != 2){
        std::cout << "1 >> Erreur" << std::endl;
        nberreurs++;
        }
    if(pile1.depiler() != 4){
        std::cout << "2 >> Erreur" << std::endl;
        nberreurs++;
        }
    if(pile1.depiler() != 1){
        std::cout << "3 >> Erreur" << std::endl;
        nberreurs++;
        }
    if(!pile1.vide()){
        std::cout << "4 >> Erreur" << std::endl;
        nberreurs++;
        }

    pile1.empiler(13);
    if(pile1.vide()){
        std::cout << "5 >> Erreur" << std::endl;
        nberreurs++;
        }
    if(pile1.depiler() != 13){
        std::cout << "6 >> Erreur" << std::endl;
        nberreurs++;
        }
    if(!pile1.vide()){
        std::cout << "7 >> Erreur" << std::endl;
        nberreurs++;
        }

    Pile<int> pile2;
    pile2.empiler(13);
    if(pile2.vide()){
        std::cout << "8 >> Erreur" << std::endl;
        nberreurs++;
        }
    if(pile2.depiler() != 13){
        std::cout << "9 >> Erreur" << std::endl;
        nberreurs++;
        }
    if(!pile2.vide()){
        std::cout << "10 >> Erreur" << std::endl;
        nberreurs++;
        }
    if(nberreurs==0)
        std::cout << " ==> Test #1  :  OK" << std::endl;
    std::cout << "-------- Fin #1 --------------" << std::endl;
    return nberreurs==0;
}

bool test2()
{
    int nberreurs=0;
    std::cout << "Test #2 : Test de la pile (opérateur =)" << std::endl;
    Pile<int> pile1;
    pile1.empiler(1);
    pile1.empiler(4);
    pile1.empiler(2);
    Pile<int> pile2;
    pile2.empiler(20);
    pile2.empiler(21);
    pile2 = pile1;
    pile1.empiler(10);
    if(pile1.depiler() != 10){
        std::cout << "1 >> Erreur" << std::endl;
        nberreurs++;
        }
    if(pile1.depiler() != 2){
        std::cout << "2 >> Erreur" << std::endl;
        nberreurs++;
        }
    if(pile1.depiler() != 4){
        std::cout << "3 >> Erreur" << std::endl;
        nberreurs++;
        }
    if(pile1.vide()){
        std::cout << "4 >> Erreur" << std::endl;
        nberreurs++;
        }
    pile2 = pile1;
    if(pile2.depiler() != 1){
        std::cout << "5 >> Erreur" << std::endl;
        nberreurs++;
        }
    if(!pile2.vide()){
        std::cout << "6 >> Erreur" << std::endl;
        nberreurs++;
        }
    if(pile1.vide()){
        std::cout << "7 >> Erreur" << std::endl;
        nberreurs++;
        }
    
    if(nberreurs==0)
        std::cout << " ==> Test #2  :  OK" << std::endl;
    std::cout << "-------- Fin #2 --------------" << std::endl;
    return nberreurs==0;
}

int fib(int i){
    if(i<=0) return 0;
    if(i==1) return 1;
    return fib(i-2) + fib(i-1);
}

bool test3()
{
    int nberreurs=0;
    std::cout << "Test #3 : ArbreAVL AVL (insertion + test d'appartenance)" << std::endl;
    ArbreAVL<int> arbre;
    for(int i=0;i<20;i+=2){
       arbre.inserer(i);
    }
    for(int i=0;i<20;i++)
        if(arbre.contient(i) != ((i%2)==0)){
            std::cout << i << " >> Erreur #1 i=" << i << std::endl;
            nberreurs++;
        }
    for(int i=1;i<20;i+=2)
       arbre.inserer(i);

    for(int i=0;i<20;i++)
        if(!arbre.contient(i)){
            std::cout << i << " >> Erreur #2 i=" << i << std::endl;
            nberreurs++;
        }


    ArbreAVL<int> arbre2;
    for(int i=0;i<20;i+=2)
       arbre2.inserer(-i);
    for(int i=1;i<20;i+=2)
       arbre2.inserer(-i);

    for(int i=0;i<20;i++)
        if(!arbre2.contient(-i)){
            std::cout << i << " >> Erreur #3 i=" << i << std::endl;
            nberreurs++;
        }

    ArbreAVL<int> arbre3;
    for(int n=1;n<=500;n++){
      arbre3.inserer(n);
      int h = arbre3.hauteur();
      int nbmin = fib(h);
      //std::cout << "h=" << h << " i=" << i << " nbmin=" << nbmin << std::endl;
      if(n<nbmin){
          std::cout << "Erreur : la hauteur de l'arbre est trop élevé pour le nombre d'éléments"
                    << std::endl
                    << "\th=" << h << "\tn=" << n << " nbmin=" << nbmin << std::endl;
          nberreurs++;
      }
    }
    if(nberreurs==0)
        std::cout << " ==> Test #3  :  OK" << std::endl;
    std::cout << "-------- Fin #3 --------------" << std::endl;
    return nberreurs==0;
}

bool test4()
{
    int nberreurs=0;
    std::cout << "Test #4 : ArbreAVL AVL (insertion + suppresion)" << std::endl;
    ArbreAVL<int> arbre;
    for(int i=0;i<20;i+=2)
        arbre.inserer(i);
    for(int i=1;i<20;i+=2)
        arbre.inserer(i);
    for(int i=0;i<20;i++)
        arbre.enlever(i);
    for(int i=0;i<20;i++)
        if(arbre.contient(i)){
            std::cout << i << "+ >> Erreur" << std::endl;
            nberreurs++;
        }
    if(nberreurs==0)
        std::cout << " ==> Test #4  :  OK" << std::endl;
    std::cout << "-------- Fin #4 --------------" << std::endl;
    return nberreurs==0;
}

bool test5a()
{
    int nberreurs=0;
    std::cout << "Test #5a : ArbreAVL AVL (opérateur =)" << std::endl;
    ArbreAVL<int> arbre1;
    for(int i=0;i<20;i++)
        arbre1.inserer(i);
    ArbreAVL<int> arbre2;
    arbre2 = arbre1;
    for(int i=0;i<20;i++)
        if(!arbre2.contient(i)){
            std::cout << i << " >> Erreur" << std::endl;
            nberreurs++;
        }
    ArbreAVL<int> arbre3;
    arbre2 = arbre3;
    for(int i=0;i<20;i++)
        if(arbre2.contient(i)){
            std::cout << i << "+ >> Erreur" << std::endl;
            nberreurs++;
        }
    if(nberreurs==0)
        std::cout << " ==> Test #5  :  OK" << std::endl;
    std::cout << "-------- Fin #5 --------------" << std::endl;
    return nberreurs==0;
}

bool test5b()
{
    int nberreurs=0;
    std::cout << "Test #5b : ArbreAVL / constructeur par copie" << std::endl;
    ArbreAVL<int> arbre1;
    for(int i=0;i<20;i++)
        arbre1.inserer(i);
    ArbreAVL<int> arbre2(arbre1);
    for(int i=0;i<20;i++)
        if(!arbre2.contient(i)){
            std::cout << i << " >> Erreur !arbre2.contient(i)" << std::endl;
            nberreurs++;
        }
    ArbreAVL<int> arbre3(arbre2);
    for(int i=0;i<20;i++)
        if(!arbre3.contient(i)){
            std::cout << i << "+ >> Erreur !arbre3.contient(i)" << std::endl;
            nberreurs++;
        }
    arbre3.vider();
    for(int i=0;i<20;i++)
        if(arbre3.contient(i)){
            std::cout << i << "+ >> Erreur arbre3.contient(i)" << std::endl;
            nberreurs++;
        }    
    for(int i=0;i<20;i++)
        if(!arbre2.contient(i)){
            std::cout << i << "+ >> Erreur !arbre2.contient(i)" << std::endl;
            nberreurs++;
        }
    if(nberreurs==0)
        std::cout << " ==> Test #5b  :  OK" << std::endl;
    std::cout << "-------- Fin #5b --------------" << std::endl;
    return nberreurs==0;
}

bool test6()
{
    int nberreurs=0;
    std::cout << "Test #6 : ArbreAVL AVL (itérateurs)" << std::endl;
    ArbreAVL<int> arbre1;
    for(int i=0;i<20;i++)
        arbre1.inserer(i);

    ArbreAVL<int>::Iterateur iter = arbre1.debut();

    for(int i=0;i<20;i++)
    {
        if(iter){
            int v1 = *iter;
            int v2 = arbre1[iter];
            if(v1!=v2 || v1!= i){
                std::cout << i << " >> Erreur" << std::endl;
                nberreurs++;
            }
            ++iter;
        }else{
            std::cout << i << "+ >> Erreur" << std::endl;
            nberreurs++;
        }
     }

    if(nberreurs==0)
        std::cout << " ==> Test #6  :  OK" << std::endl;
    std::cout << "-------- Fin #6 --------------" << std::endl;
    return nberreurs==0;
}


bool test7()
{
    int nberreurs=0;
    std::cout << "Test #7 : ArbreAVL AVL (recherche égal + précédent/suivant)" << std::endl;
    ArbreAVL<int> arbre;
    for(int i=0;i<10;i+=2)
        arbre.inserer(i);
  
    for(int i=-2;i<12;i++)
    {
        ArbreAVL<int>::Iterateur iter = arbre.rechercherEgalOuSuivant(i);   
    
        if(i>=9){
            if(iter){
                std::cout << "Erreur rechercherEgalOuSuivant(" << i << ") : " << *iter << std::endl;
                nberreurs++;
            }
        }
        else if(!iter){
            std::cout << "Erreur rechercherEgalOuSuivant(" << i << ") = fin!" << std::endl;
            nberreurs++;
        }
        else{
            int bi = arbre[iter];
            int ebi = i+1;
            ebi -= ebi%2;
            if(ebi<0) ebi = 0;
            if(ebi != bi){
                std::cout << "Erreur rechercherEgalOuSuivant(" << i << ")=" << bi << " != " << ebi << std::endl;
                nberreurs++;
            }
        }
    
    
        iter = arbre.rechercherEgalOuPrecedent(i);
        if(i<0){
            if(iter){
                std::cout << "Erreur rechercherEgalOuPrecedent(" << i << ") : " << *iter << std::endl;
                nberreurs++;
            }
        }
        else if(!iter){
            std::cout << "Erreur rechercherEgalOuPrecedent(" << i << ") = fin!" << std::endl;
            nberreurs++;
        }else{
            int bs = arbre[iter];
            int ebs = i;
            ebs -= ebs%2;
            if(ebs>8) ebs = 8;
       
            if(ebs != bs){
                std::cout << "Erreur rechercherEgalOuPrecedent(" << i << ")=" << bs << " != " << ebs << std::endl;
                nberreurs++;
            }
        }
    }
    if(nberreurs==0)
        std::cout << " ==> Test #7  :  OK" << std::endl;
    std::cout << "-------- Fin #7 --------------" << std::endl;
    return nberreurs==0;
}

bool test8()
{
    int nberreurs=0;
    std::cout << "Test #8 : ArbreAVL AVL (Itérateurs sur recherche égal + précédent/suivant)" << std::endl;
    ArbreAVL<int> arbre;
    for(int i=0;i<10;i++)
        arbre.inserer(i);
  
    for(int cible=0;cible<10;cible++){
        ArbreAVL<int>::Iterateur iter = arbre.rechercher(cible);
        for(int i=cible;i<10;i++)
            if(*iter++ != i){
                std::cout << " Erreur itérateur rechercher : " << i << std::endl;
                nberreurs++;
            }
        if(iter){
            std::cout << " Erreur fin itérateur : " << std::endl;
            nberreurs++;
        }
         
        iter = arbre.rechercherEgalOuPrecedent(cible);
        for(int i=cible;i<10;i++)
            if(*iter++ != i){
                std::cout << " Erreur itérateur rechercherEgalOuPrecedent : " << i << std::endl;
                nberreurs++;
            }
        if(iter){
             std::cout << " Erreur fin rechercherEgalOuPrecedent : " << std::endl;
             nberreurs++;
        }
         
        iter = arbre.rechercherEgalOuSuivant(cible);
        for(int i=cible;i<10;i++)
            if(*iter++ != i){
                std::cout << " Erreur itérateur rechercherEgalOuSuivant : " << i << std::endl;
                nberreurs++;
            }
        if(iter){
            std::cout << " Erreur fin rechercherEgalOuSuivant : " << std::endl;
            nberreurs++;
        }
    }
  
    if(nberreurs==0)
        std::cout << " ==> Test #8  :  OK" << std::endl;
    std::cout << "-------- Fin #8 --------------" << std::endl;
    return nberreurs==0;
}
