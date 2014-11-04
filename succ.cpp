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
    clog << "verifier disponibilite " << nomSuccursale << " " << prise << " " << retour << ": V = " << nbVoit << ", L = " << nbPlacesLibres << endl;

    if (evenements.size() == 0) {
        dispo = nbVoitures > 0;
    } else {
        map<Date, int>::iterator it;
        // la voiture doit etre disponible pour la duree !!

        for (it = evenements.begin(); it->first < prise && it != evenements.end(); ++it) {
            nbVoit += it->second;
            clog << it->first << "V = " << nbVoit << ", L = " << nbPlaces - nbVoit << endl;
            assert(nbVoit >= 0);
        }

        // commence a verifier ici

        dispo = !(it == evenements.end() && nbVoit < 1); // rendu au dernier evenement

        if (dispo) {
            do {
                nbVoit += it->second;
                clog << it->first << "V = " << nbVoit << ", L = " << nbPlaces - nbVoit << endl;
                ++it;
                if (nbVoit < 1) dispo = false;
            } while (dispo && retour < it->first && it != evenements.end());
        }
    }

    return dispo;
}


bool Succursale::verifierRetourPossible(Date retour){
    bool retourOk = true;
    int nbLibre = nbPlacesLibres;
    clog << "verifier retour " << nomSuccursale << " " << retour << ": V = " << nbVoitures << ", L = " << nbLibre << endl;

    if (evenements.size() == 0) {
        retourOk = nbPlacesLibres > 0;
    } else {

        map<Date, int>::iterator it;
        // la place doit etre disponible a partir de retour jusqua la fin des evenements actuels  !!
        for (it = evenements.begin(); it->first < retour && it != evenements.end(); ++it) {
            nbLibre -= it->second;
            clog << it->first << "V = " << nbPlaces - nbLibre << ", L = " << nbLibre << endl;
            assert(nbLibre >= 0);
        }
        // commence a verifier ici

        retourOk = !(it == evenements.end() && nbLibre < 1); // rendu au dernier evenement

        if (retourOk) {
            do {
                nbLibre -= it->second;
                clog << it->first << "V = " << nbPlaces - nbLibre << ", L = " << nbLibre << endl;
                ++it;
                if (nbLibre < 1) retourOk = false;
            } while (retourOk && it != evenements.end());
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