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
}

bool Date::operator <(const Date& d) const{
    return minutes < d.minutes;
}

bool Date::operator <=(const Date& d) const{
    return minutes <= d.minutes;
}

std::ostream& operator << (std::ostream& os, const Date& d){
    int jours, heures, minutes;

    jours = d.minutes / (60 * 24);
    heures = (d.minutes % (60 * 24)) /60;
    minutes = d.minutes % 60;

    char chaine[40];
    sprintf(chaine, "%dj_%02dh%02dm", jours, heures, minutes);
    os << chaine;
    return os;
}

std::istream& operator >> (std::istream& is, Date& d){
    // char chaine[40];
    int jours, heures, minutes;
    char j, m, h, underscore;
    is >> jours >> j >> underscore >> heures >> h >> minutes >> m;
    assert(j=='j');
    assert(underscore=='_');
    assert(h=='h' && m=='m');
    d.minutes = minutes + heures * 60 + jours * 60 * 24;
    return is;
}

