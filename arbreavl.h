/*
  INF3105 - Structures de données et algorithmes
  
  Squelette pour Lab6 + TP2
*/

#if !defined(__ARBREAVL_H__)
#define __ARBREAVL_H__

#include <assert.h>
#include <stdio.h>
#include "pile.h"

template<class T>
class ArbreAVL {
public:
    ArbreAVL();

    ArbreAVL(const ArbreAVL &);

    ~ArbreAVL();

    void inserer(const T &);

    void enlever(const T &);

    bool contient(const T &) const;

    bool vide() const;

    void vider();

    int hauteur() const;

    ArbreAVL &operator=(const ArbreAVL &);

    // Puisque les fonctions suivantes retournent des itérateurs, il faut *annoncer* la décalaration classe Iterateur
    // On ne peut pas déclarer Iterateur tout de suite, car Iterateur a besoin de Noeud.
    class Iterateur;

    Iterateur debut() const;

    Iterateur fin() const;

    Iterateur rechercher(const T &) const;

    Iterateur rechercherEgalOuSuivant(const T &) const;

    Iterateur rechercherEgalOuPrecedent(const T &) const;

    const T &operator[](const Iterateur &) const;

    T &operator[](const Iterateur &);

private:
    class Noeud;

    Noeud *racine;

    bool inserer(const T &, Noeud *&);

    bool enlever(const T &e, Noeud *&n);

    void rotationDroite(Noeud *&);

    void rotationGauche(Noeud *&);

    void vider(Noeud *&);

    void copier(const Noeud *, Noeud *&) const;

    void copier(Noeud *&, const T &);

    const T &max(Noeud *) const;

    int  hauteur(Noeud *) const;

public:
    class Iterateur {
    public:
        Iterateur(const ArbreAVL &a);

		Iterateur(const Iterateur &a)
			: arbre_associe(a.arbre_associe) {
			courant = a.courant;
			chemin = a.chemin;
		}

        Iterateur(const ArbreAVL &a, Noeud *c);


        operator bool() const;

        bool operator!() const;

        bool operator==(const Iterateur &) const;

        bool operator!=(const Iterateur &) const;

        const T &operator*() const;

        Iterateur &operator++();

        Iterateur operator++(int);

        Iterateur &operator=(const Iterateur &);

    private:
        const ArbreAVL &arbre_associe;
        Noeud *courant;
        Pile<Noeud *> chemin;

        friend class ArbreAVL;
    };

private:
    class Noeud {
    public:
        Noeud(const T &);

        Noeud *gauche;
        Noeud *droite;
        int equilibre;
        T contenu;
    };
};


//-----------------------------------------------------------------------------

template<class T>
ArbreAVL<T>::Noeud::Noeud(const T &c) :
        gauche(NULL), droite(NULL), equilibre(0), contenu(c) {
}

template<class T>
ArbreAVL<T>::ArbreAVL() : racine(NULL) {
}

template<class T>
ArbreAVL<T>::ArbreAVL(const ArbreAVL<T> &autre) : racine(NULL) {
    copier(autre.racine, racine);
}

template<class T>
ArbreAVL<T>::~ArbreAVL() {
    vider(racine);
}

template<class T>
void ArbreAVL<T>::inserer(const T &element) {
    inserer(element, racine);
}

template<class T>
bool ArbreAVL<T>::inserer(const T &element, Noeud *&noeud) {
    if (noeud == NULL) {
        // creation d'une nouvelle feuille
        noeud = new Noeud(element);
        //std::cout << "insersion de " << element << std::endl;
        return true; // la hauteur a augmentee dans cette feuille
    }
    if (element < noeud->contenu) { // inserer a gauche
        if (inserer(element, noeud->gauche)) {
            noeud->equilibre++; // +1 a gauche = +1
            //std::cout << "equilibre = " << noeud->equilibre << std::endl;
            if (noeud->equilibre == 0) return false; // le sous-arbre n a la meme hauteur
            if (noeud->equilibre == 1) return true; // le sous-arbre n a grandi en hauteur
            assert(noeud->equilibre == 2); // reequilibrage requis
            if (noeud->gauche->equilibre == -1) // cas double rotation
                rotationGauche(noeud->gauche); // rotation gauche du fils gauch
            rotationDroite(noeud); // rotation droite pour equilibrer n
        }
        return false;
    }
    else if (noeud->contenu < element) { // inserer a droite
        if (inserer(element, noeud->droite)){
            noeud->equilibre--; // +1 a droite = -1
            //std::cout << "equilibre = " << noeud->equilibre << std::endl;
            if (noeud->equilibre == 0) return false; // le sous-arbre n a la meme hauteur
            if (noeud->equilibre == -1) return true; // le sous-arbre n a grandi en hauteur
            assert(noeud->equilibre == -2); // reequilibrage requis
            if (noeud->droite->equilibre == 1) // cas double rotation
                rotationDroite(noeud->droite);
            rotationGauche(noeud); // rotation gauche pour equilibrer n
        }
        return false;
    }
    else { // element == noeud->contenu
        noeud->contenu = element;  // Mise à jour
        return false; // le sous-arbre n conserve sa hauteur
    }
}


template<class T>
void ArbreAVL<T>::enlever(const T &element) {
    enlever(element, racine);
}

template<class T>
bool ArbreAVL<T>::enlever(const T &element, Noeud *&noeud) { // todo a debugger
    if (element < noeud->contenu) {  // chercher a gauche
        if (enlever(element, noeud->gauche)) {
            noeud->equilibre--;
            if (noeud->equilibre == 0) return false;
            if (noeud->equilibre == -1) return true;
            assert(noeud->equilibre == -2); // reequilibrage requis
            if (noeud->droite->equilibre == 1) // cas double rotation
                rotationDroite(noeud->droite);
            rotationGauche(noeud); // rotation gauche pour equilibrer n
        }
        return false;
    }
    else if (element > noeud->contenu) { // chercher a droite
        if (enlever(element, noeud->droite)) {
            noeud->equilibre++; // +1 a gauche = +1
            //std::cout << "equilibre = " << noeud->equilibre << std::endl;
            if (noeud->equilibre == 0) return false; // le sous-arbre n a la meme hauteur
            if (noeud->equilibre == 1) return true; // le sous-arbre n a grandi en hauteur
            assert(noeud->equilibre == 2); // reequilibrage requis
            if (noeud->gauche->equilibre == -1) // cas double rotation
                rotationGauche(noeud->gauche); // rotation gauche du fils gauch
            rotationDroite(noeud); // rotation droite pour equilibrer n
        }
        return false;
    }
    else if (element == noeud->contenu) { // enlever le noeud
        // cas 1 : pas d'enfants
        if (noeud->gauche == NULL && noeud->droite == NULL) {
            delete noeud;
            return true;
        }
        // cas 2 : un enfant a droite
        else if (noeud->gauche == NULL) {
            Noeud *temp = noeud;
            noeud = temp->droite;
            delete temp;
            return true;
        }
        // cas 3 : un enfant a gauche
        else if (noeud->droite == NULL) {
            Noeud *temp = noeud;
            noeud = temp->gauche;
            delete temp;
            return true;
        }
        // cas 4 : deux enfants
        else {
            // cherche le plus grand a gauche//todo
            Noeud *temp = noeud->gauche;
            while (temp->droite != NULL)
                temp = temp->droite;
            // echanche les deux noeuds
            T &element =  noeud->contenu;
            noeud->contenu = temp->contenu;
            temp->contenu = element;
            // enlever le noeud (pas delete car on doit ajuster les equilibres des parents)
            enlever(element, noeud);
            return true;
        }
    }

}

template<class T>
void ArbreAVL<T>::rotationDroite(Noeud *&racine) {
    Noeud *temp = racine->gauche;
    int eg = temp->equilibre;
    int er = racine->equilibre;

    //std::cout << "rotation droite de " << racine->contenu << " avec " << racine->gauche->contenu << std::endl;
    int new_er = -(eg > 0 ? eg : 0) - 1 + er;
    int new_eg = eg + (new_er < 0 ? new_er : 0) - 1;
    //assert(new_er > -1 && new_er < 1);
    //assert(new_eg > -1 && new_eg < 1);
    if (new_er < -1 && new_er > 1) std::cerr << new_er << std::endl;
    if (new_eg < -1 && new_er > 1) std::cerr << new_eg << std::endl;

    temp->equilibre = new_eg;
    racine->equilibre = new_er;
    racine->gauche = temp->droite;
    temp->droite = racine;
    racine = temp;
}

template<class T>
void ArbreAVL<T>::rotationGauche(Noeud *&racine) {

    Noeud *temp = racine->droite;
    int ed = temp->equilibre;
    int er = racine->equilibre;

   // std::cout << "rotation gauche de " << racine->contenu << " avec " << racine->droite->contenu << std::endl;

    int new_er = er - (ed > 0 ? 0 : ed) + 1;
    int new_ed = ed + (new_er < 0 ? 0 : new_er) + 1;
    //assert(new_er > -1 && new_er < 1);
    //assert(new_ed > -1 && new_ed < 1);
    if (new_er < -1 && new_er > 1) std::cerr << new_ed << std::endl;
    if (new_ed < -1 && new_ed > 1) std::cerr << new_ed << std::endl;

    temp->equilibre = new_ed;
    racine->equilibre = new_er;
    racine->droite = temp->gauche;
    temp->gauche = racine;
    racine = temp;
}

template<class T>
bool ArbreAVL<T>::vide() const {
    return racine == NULL;
}

template<class T>
void ArbreAVL<T>::vider() {
    vider(racine);
    racine = NULL;
}

template<class T>
void ArbreAVL<T>::vider(Noeud *&noeud) {
    if (noeud == NULL) return;
    vider(noeud->gauche);
    vider(noeud->droite);
    delete noeud; // Facultatif : n=NULL;
}

template<class T>
void ArbreAVL<T>::copier(const Noeud *source, Noeud *&noeud) const {

    if (source == NULL) return;

    assert(noeud == NULL);
    noeud = new Noeud(source->contenu);
    noeud->equilibre = source->equilibre;

    if (source->gauche != NULL) {
        copier(source->gauche, noeud->gauche);
    }
    if (source->droite != NULL) {
        copier(source->droite, noeud->droite);
    }
}




template<class T>
bool ArbreAVL<T>::contient(const T &element) const {
    return rechercher(element);
}

template<class T>
int  ArbreAVL<T>::hauteur() const {

    return hauteur(racine);
    // todo : evaluer si preferable d<utiliser une variable hauteur
}
template<class T>
int  ArbreAVL<T>::hauteur(Noeud *sracine) const {
    if(sracine == NULL)
        return 0;
    int a = hauteur(sracine->gauche);
    int b = hauteur(sracine->droite);
    return (a < b ? b : a) + 1;
    // todo : evaluer si preferable d<utiliser une variable hauteur
}

template<class T>
const T &ArbreAVL<T>::max(Noeud *n) const {
    Iterateur iter(*this);

    iter.courant = racine;
    if (iter.courant != NULL)
        while (iter.courant->droite!= NULL){
            iter.courant = iter.courant->droite;
        }

    return iter.courant->contenu;
}

template<class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::debut() const {
    Iterateur iter(*this);

    iter.courant = racine;
    if (iter.courant != NULL)
        while (iter.courant->gauche!= NULL){
            iter.chemin.empiler(iter.courant);
            iter.courant = iter.courant->gauche;
        }
    return iter;
}

template<class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::fin() const {
    return Iterateur(*this);
}

template<class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercher(const T &e) const {
    Iterateur iter(*this);
    Noeud* n = racine;
    while(n){
        if(e < n->contenu){
            iter.chemin.empiler(n);
            n = n->gauche;
        }
        else if(n->contenu < e)
            n = n->droite;
        else{
            iter.courant = n;
            return iter;
        }
    }
    iter.chemin.vider();
    return iter;
}

template<class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercherEgalOuSuivant(const T &e) const {

    Noeud* n = racine;
    Noeud* dernier = NULL;

    while(n){
        if(e < n->contenu){
            dernier = n;
            n = n->gauche;
        }
        else if(n->contenu < e) {
            n = n->droite;
        }
        else{
            return rechercher(e); // pourquoi ??
        }
    }
    if(dernier!= NULL)
        return rechercher(dernier->contenu);
    return Iterateur(*this);
}

template<class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercherEgalOuPrecedent(const T &e) const {
    Noeud* n = racine;
    Noeud* dernier = NULL;

    while(n){
        if(e < n->contenu){
            n = n->gauche;
        }
        else if(n->contenu < e) {
            dernier = n;
            n = n->droite;
        }
        else{
            return rechercher(e);  // pourquoi ??
        }
    }
    if(dernier!= NULL)
        return rechercher(dernier->contenu);  // pourquoi ??
    return Iterateur(*this);
}

template<class T>
const T &ArbreAVL<T>::operator[](const Iterateur &iterateur) const {
    assert(&iterateur.arbre_associe == this);
    assert(iterateur.courant);
    return iterateur.courant->contenu;
}

template<class T>
T &ArbreAVL<T>::operator[](const Iterateur &iterateur) {
    assert(&iterateur.arbre_associe == this);
    assert(iterateur.courant);
    return iterateur.courant->contenu;
}

template<class T>
ArbreAVL<T> &ArbreAVL<T>::operator=(const ArbreAVL &autre) {
    if (this == &autre) return *this;
    vider();
    copier(autre.racine, racine);

    return *this;
}

//-----------------------
template<class T>
ArbreAVL<T>::Iterateur::Iterateur(const ArbreAVL &a)
        : arbre_associe(a), courant(NULL) {
}


// Pré-incrément
template<class T>
inline typename ArbreAVL<T>::Iterateur &ArbreAVL<T>::Iterateur::operator++() {

    assert(courant);
    Noeud* suivant = courant->droite;
    while(suivant) {
        chemin.empiler(suivant);
        suivant = suivant->gauche;
    }
    if (!chemin.vide())
        courant = chemin.depiler();
    else
        courant = NULL;
    return *this;
}

// Post-incrément
template<class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::Iterateur::operator++(int) {
    Iterateur copie(*this);
    operator++();
    return copie;
}

template<class T>
ArbreAVL<T>::Iterateur::operator bool() const {
    return courant != NULL;
}

template<class T>
bool ArbreAVL<T>::Iterateur::operator!() const {
    return courant == NULL;
}

template<class T>
bool ArbreAVL<T>::Iterateur::operator==(const Iterateur &o) const {
    assert(&arbre_associe == &o.arbre_associe);
    return courant == o.courant;
}

template<class T>
bool ArbreAVL<T>::Iterateur::operator!=(const Iterateur &o) const {
    assert(&arbre_associe == &o.arbre_associe);
    return courant != o.courant;
}

template<class T>
const T &ArbreAVL<T>::Iterateur::operator*() const {
    assert(courant != NULL);
    return courant->contenu;
}

template<class T>
typename ArbreAVL<T>::Iterateur &ArbreAVL<T>::Iterateur::operator=(const Iterateur &autre) {
    assert(&arbre_associe == &autre.arbre_associe);
    courant = autre.courant;
    chemin = autre.chemin;
    return *this;
}

#endif


