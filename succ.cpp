#include "succ.h"
#include <map>
#include <assert.h>
using namespace std;

string Succursale::getName() const{
    return nomSuccursale;
}

bool Succursale::verifierDisponibilite(Date prise, Date retour){
    bool dispo=true;
    int nbVoit = nbVoitures;
    //cout << "verifier diponibilite " << nomSuccursale << prise << retour << ": V = " << nbVoit << ", L = " << nbPlacesLibres << endl;

    if (evenements.size() == 0) {
        dispo = nbVoitures > 0;
    } else {
        map<Date, int>::iterator it;
        // la voiture doit etre disponible pour la duree !!
        for (it = evenements.begin(); it != evenements.end(); ++it) {
            nbVoit += it->second;
            //cout << "V = " << nbVoit << ", L = " << nbPlaces - nbVoit << endl;
            if (it->first < prise) {
                assert(nbVoit >= 0);
            } else if (nbVoit < 1) {
                dispo = false;
                break;
            } else if (retour < it->first) {
                break;
            }
        }
    }

    return dispo;
}


bool Succursale::verifierRetourPossible(Date retour){
    bool retourOk = true;
    int nbLibre = nbPlacesLibres;
    //cout << "verifier retour " << nomSuccursale << retour << ": V = " << nbVoitures << ", L = " << nbLibre << endl;

    if (evenements.size() == 0) {
        retourOk = nbPlacesLibres > 0;
    } else {

        map<Date, int>::iterator it;
        // la place doit etre disponible a partir de retour jusqua la fin des evenements actuels  !!
        for (it = evenements.begin(); it != evenements.end(); ++it) {
            nbLibre -= it->second;
            //cout << "V = " << nbPlaces - nbLibre << ", L = " << nbLibre << endl;
            if (it->first < retour) {
                assert(nbLibre >= 0);
            } else if (nbLibre < 1) {
                    retourOk = false;
                    break;
            }
        }
    }

    return retourOk;
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