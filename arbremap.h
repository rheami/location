/*
  INF3105 - Structures de données et algorithmes
  Squelette pour Lab7 + TP2
*/


#if !defined(__ARBRE_MAP_H__)
#define __ARBRE_MAP_H__

#include "arbreavl.h"

template<class K, class V>
class ArbreMap {
private:
    // À compléter : voir la Section 8.11 (Arbres associatifs (Mapping Trees)) des notes de cours.

    class Entree {
    public:
        Entree(const K &c) : cle(c), valeur() {
        }

        K cle;
        V valeur;

        bool operator<(const Entree &e) const {
            return cle < e.cle;
        }
        bool operator==(const Entree &e) const {
            return cle == e.cle;
        }
    };

    ArbreAVL<Entree> entrees;
    //Liste<Entree> entrees; // temporairement car ArbreAVL non fonctionnel

public:
    bool contient(const K &) const;

    void enlever(const K &);

    void vider();

    bool vide() const;

    const V &operator[](const K &) const;

    V &operator[](const K &);
};

template<class K, class V>
void ArbreMap<K, V>::vider() {
    entrees.vider();
}

template<class K, class V>
bool ArbreMap<K, V>::vide() const {
    return entrees.vide();
    //return entrees.estVide();
}

template<class K, class V>
void ArbreMap<K, V>::enlever(const K &cle) {
    // À compléter
    std::cout << "enlever n<est pas implemente" << std::endl;

    //entrees.enlever(entrees.trouver(Entree(cle)));
}

template<class K, class V>
bool ArbreMap<K, V>::contient(const K &cle) const {
    return entrees.contient(cle) != NULL;
    //return entrees.contient(Entree(cle))!=NULL; // equivalent
}

template<class K, class V>
const V &ArbreMap<K, V>::operator[](const K &cle) const {
    typename ArbreAVL<Entree>::Iterateur iter = entrees.rechercher(cle);
    return entrees[iter].valeur;
}

template<class K, class V>
V &ArbreMap<K, V>::operator[](const K &cle) {
   typename ArbreAVL<Entree>::Iterateur iter = entrees.rechercher(Entree(cle));

    if (!iter) {
        entrees.inserer(Entree(cle));
        iter = entrees.rechercher(cle);
    }
    return entrees[iter].valeur;
}


#endif

