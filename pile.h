/*  INF3105 - Structures de données et algorithmes
    Auteur : Eric Beaudry
*/

#if !defined(__PILE_H__)
#define __PILE_H__
#include "tableau.h"
template<class T>
class Pile {
public:
    Pile();

    Pile(const Pile &);

    ~Pile();

    void empiler(const T &);

    void depiler(T &out);  // Depiler et copier le sommet dans out.
    T depiler();

    bool vide() const {
        return Table.taille() ==0;
    }

    void vider();

    const Pile<T> &operator=(const Pile<T> &);

private:
    //Pile(const Pile&); // on pourrait préférer mettre le constructeur par copie privé.

	Tableau<T> Table;
};

/*
 Puisque Pile<T> est une classe générique, toutes ses définitions doivent être
 inclues après les déclarations. On peut quand même séparer les déclarations et
 les définitions en deux fichiers (pile.h et pile.hcc), à condition d'inclure le
 deuxième (pile.hcc) à la fin du premier (pile.h). Ainsi, un fichier source
 (.cc, .cpp, c++) qui inclut pile.h inclura indirectement aussi pile.hcc.
*/
//#include "pile.hcc"
/**** Début des définitions pouvant être mises dans pile.hcc. ****/
// Les deux directives suivante sont utiles lorsqu'un fichier pile.hcc est utilisé.
#if !defined(__PILE_CPP__)
#define __PILE_CPP__

#include "assert.h"
#include "pile.h"

template<class T>
Pile<T>::Pile() {
}

template<class T>
Pile<T>::~Pile() {
    vider();
}

template<class T>
Pile<T>::Pile(const Pile<T> &autre) {
	Table(autre.Table)
}


template<class T>
void Pile<T>::vider() {
    while (!vide())
        depiler();
}


template<class T>
void Pile<T>::empiler(const T &e) {
	Table.ajouter(e);
}

template<class T>
T Pile<T>::depiler() {
	T Sortie = Table[Table.taille() - 1];
	Table.enlever_dernier();
		return Sortie;
}

template<class T>
void Pile<T>::depiler(T &e) {
	e = Table[Table.taille() - 1];
	Table.enlever_dernier();
}

template<class T>
const Pile<T> &Pile<T>::operator=(const Pile<T> &autre) {
	this->Table = autre.Table;

    return *this;
}

#endif
// Les deux directives #endif sont utiles lorsqu'un fichier pile.hcc est utilisé.
#endif
