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

public:
    bool contient(const K &) const;

    void enlever(const K &);

    void vider();

    bool vide() const;

    const V &operator[](const K &) const;
    V &operator[](const K &);

    class Iterateur {
    public:
        Iterateur(ArbreMap &a): iter(a.entrees.debut()){}
        Iterateur(typename ArbreAVL<Entree>::Iterateur i): iter(i){}
        operator bool() const {return iter.operator bool();};
        Iterateur& operator++() {++iter; return *this;}
        const K& cle() const {return ( *iter).cle;}
        const V& valeur() {return (V&) ( *iter).valeur;}
    private:
        typename ArbreAVL<Entree>::Iterateur iter;
    };
    Iterateur debut() { return Iterateur( *this); }
    Iterateur fin() { return Iterateur(entrees.fin());}
    Iterateur rechercher(const K& cle) { return Iterateur(entrees.rechercher(cle));}
    Iterateur rechercherEgalOuSuivant(const K& cle) {return
                Iterateur(entrees.rechercherEgalOuSuivant(cle));}
    Iterateur rechercherEgalOuPrecedent(const K& cle) {return
                Iterateur(entrees.rechercherEgalOuPrecedent(cle));}

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

