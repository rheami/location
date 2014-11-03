#include "succ.h"
#include <map>
#include <assert.h>
// À compléter...

using namespace std;

string Succursale::getName() const{
    return nomSuccursale;
}

bool Succursale::verifierDisponibilite(Date prise, Date retour){
    bool dispo=true;
    int nbVoit = nbVoitures;

    map<Date,int>::iterator it;
    // la voiture doit etre disponible pour la duree !!
    for (it = evenements.begin(); it != evenements.end() && retour < it->first; ++it) {
        nbVoit += it->second;
        cout << nbVoit << " ";
        if (it->first < prise) {
            assert(nbVoit >= 0);
        } else if (nbVoit < 1) {
            dispo = false;
            break;
        } else if ( retour < it->first ) {
            break;
        }
    }

    return dispo;
}


bool Succursale::verifierRetourPossible(Date retour){
    bool dispo=true;
    int nbLibre = nbPlacesLibres;

    map<Date,int>::iterator it;
    // la place doit etre disponible a partir de retour jusqua la fin des evenements actuels  !!
    for (it = evenements.begin(); it != evenements.end() && it->first < retour; ++it) {
        nbLibre -= it->second;
        assert(it->second >= 0);
    }
    for (; it != evenements.end(); ++it) {
        nbLibre -= it->second;
        if (nbLibre < 1) {
            dispo = false;
            break;
        }
    }

    return dispo;
}

void Succursale::ajouterEvenementDepart(Date date) {
    evenements[date] -= 1;
}
void Succursale::ajouterEvenementRetour(Date date){
    evenements[date] += 1;
}


istream& operator >> (istream& is, Succursale& succursale) {
    is >> succursale.nomSuccursale >> succursale.nbVoitures >> succursale.nbPlacesLibres;
    succursale.nbPlaces = succursale.nbVoitures + succursale.nbPlacesLibres;
    return is;
}

ostream& operator << (ostream& os, const Succursale succursale) {
    os << " succ " << succursale.nomSuccursale << " voitures disponibles = " << succursale.nbVoitures << " Stat Libres = " << succursale.nbPlacesLibres;
    return os;
}