/*
  INF3105 - Structures de données et algorithmes
  UQAM / Département d'informatique
  Automne 2014
  
  Squelette de départ. Vous pouvez modifier ce fichier à votre guise.
  Vous n'êtes pas obligés de l'utiliser.
*/

#include "date.h"
#include <cstdio>
#include <iomanip>
#include <assert.h>

Date::Date()
{
  // À compléter
}

bool Date::operator <(const Date& d) const{
    // À compléter : comparer *this (l'objet courant) < d.
    return false;
}

bool Date::operator <=(const Date& d) const{
    // À compléter : comparer *this (l'objet courant) <= d.
    return false;
}

std::ostream& operator << (std::ostream& os, const Date& d){
    int jours, heures, minutes;
    // À compléter
    // jours = ...
    // heures = ...
    // minutes = ...
    char chaine[40];
    sprintf(chaine, "%dj_%02dh%02dm", jours, heures, minutes);
    os << chaine;
    return os;
}

std::istream& operator >> (std::istream& is, Date& d){
    char chaine[40];
    int jours, heures, minutes;
    char j, m, h, underscore;
    is >> jours >> j >> underscore >> heures >> h >> minutes >> m;
    assert(j=='j');
    assert(underscore=='_');
    assert(h=='h' && m=='m');

    // À compléter : utiliser les variable jours,heures,minutes pour modifier l'objet d.


    return is;
}

std::ostream& operator << (std::ostream& os, const Intervalle& i){
  os << i.debut  << i.fin;
  return os;
}

std::istream& operator >> (std::istream& is, Intervalle& i){
  char crochetgauche, crochetdroit, virgule;
  is >> crochetgauche >> i.debut >> virgule >> i.fin >> crochetdroit;
  assert(crochetgauche=='[' && virgule==',' && crochetdroit==']');
  return is;
}

