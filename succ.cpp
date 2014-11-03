#include "succ.h"
#include <map>
// À compléter...

using namespace std;

string Succursale::getName() const{
    return nomSuccursale;
}

bool Succursale::verifierDisponibilite(Date debut, Date fin){
    bool dispo;

    map::iterator it = evenements.lower_bound(debut);
    if(it != evenements.begin()) {
        --it; // commence a verifier avant debut
    } else { // pas d evenement avant debut
    }
    // la voiture doit etre disponible pour la duree !!
    for (;it != evenements.lower_bound(fin); ++it) {
        if ((it->second).V = 0) {
            dispo = false;
            break;
        }
    }

    return dispo;
}

void Succursale::ajouterEvenementDepart(Date date) {
    // evenements[date] = Etat::V
}
void Succursale::ajouterEvenementRetour(Date date){

}

bool Succursale::verifierRetourPossible(Date fin){
    // on doit verifier tout les retours prevus

    return false;
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