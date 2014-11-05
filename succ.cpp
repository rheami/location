#include "succ.h"
#include <map>
#include <assert.h>
using namespace std;

string Succursale::getName() const{
    return nomSuccursale;
}

bool Succursale::operator==(const Succursale &autre) const {
    return nomSuccursale.compare(autre.getName()) == 0;
}

bool Succursale::verifierDisponibiliteEtRetour(Date prise, Date retour){
    bool dispo=true;
    int nbVoit = nbVoitures;
    int nbLibre = nbPlacesLibres;
    clog << "verifier disponibilite " << nomSuccursale << " " << prise << " " << retour << ": V = " << nbVoit << ", L = " << nbPlacesLibres << endl;

    if (evenements.empty()) {
        dispo = nbVoitures > 0;
        // et au moins une place libre celle quon vient de liberer;
    } else {

        // la voiture doit etre disponible pour la duree !!
        //it = evenements.begin();
        map<Date,int>::iterator it = evenements.begin();
        for (; it->first < prise && it != evenements.end(); ++it) {
            nbVoit += it->second;
            clog << it->first << "V = " << nbVoit << ", L = " << nbPlaces - nbVoit << endl;
            assert(nbVoit >= 0);
        }

        // commence a verifier ici
        clog << "commence a verifier" << endl;
        if (it == evenements.end()){
            dispo = nbVoit > 0;
        } else { // verifie jusqua retour arrete si dispo faux ou rendu a la fin
            for (;dispo && retour < it->first && it != evenements.end();++it){
                nbVoit += it->second;
                clog << it->first << "V = " << nbVoit << ", L = " << nbPlaces - nbVoit << endl;
                dispo = nbVoit > 0;
            }
        }
        if (dispo) {
            ++nbLibre; // la prise de possesion libère une place

            // la place doit etre disponible a partir de retour jusqua la fin des evenements actuels  !!
            for (; it->first < retour && it != evenements.end(); ++it) {
                nbLibre -= it->second;
                clog << it->first << "V = " << nbPlaces - nbLibre << ", L = " << nbLibre << endl;
                assert(nbLibre >= 0);
            }

            // commence a verifier ici
            clog << "commence a verifier" << endl;
            if (it == evenements.end()) {
                dispo = nbLibre > 0;
            } else { // verifie jusqua la fin, arrete si dispo faux
                for (;dispo && it != evenements.end();++it){
                    nbLibre -= it->second;
                    clog << it->first << "V = " << nbPlaces - nbLibre << ", L = " <<  nbLibre << endl;
                    dispo = nbLibre > 0;
                }
            }
        }
    }

    return dispo;
}

bool Succursale::verifierDisponibilite(Date prise, Date retour){
    bool dispo=true;
    int nbVoit = nbVoitures;
    clog << "verifier disponibilite " << nomSuccursale << " " << prise << " " << retour << ": V = " << nbVoit << ", L = " << nbPlacesLibres << endl;

    if (evenements.empty()) {
        dispo = nbVoitures > 0;
    } else {

        // la voiture doit etre disponible pour la duree !!
        //it = evenements.begin();
        map<Date,int>::iterator it = evenements.begin();
        for (; it->first < prise && it != evenements.end(); ++it) {
            nbVoit += it->second;
            clog << it->first << "V = " << nbVoit << ", L = " << nbPlaces - nbVoit << endl;
            assert(nbVoit >= 0);
        }

        // commence a verifier ici
        clog << "commence a verifier" << endl;
        if (it == evenements.end()){
            dispo = nbVoit > 0;
        } else { // verifie jusqua retour arrete si dispo faux ou rendu a la fin
            for (;dispo && retour < it->first && it != evenements.end();++it){
                nbVoit += it->second;
                clog << it->first << "V = " << nbVoit << ", L = " << nbPlaces - nbVoit << endl;
                dispo = nbVoit > 0;
            }
        }
    }

    return dispo;
}


bool Succursale::verifierRetourPossible(Date retour){
    bool retourOk = true;
    int nbLibre = nbPlacesLibres;
    clog << "verifier retour " << nomSuccursale << " " << retour << ": V = " << nbVoitures << ", L = " << nbLibre << endl;

    if (evenements.empty()) {
        retourOk = nbPlacesLibres > 0;
    } else {
        map<Date, int>::iterator it = evenements.begin();
        // la place doit etre disponible a partir de retour jusqua la fin des evenements actuels  !!
        for (; it->first < retour && it != evenements.end(); ++it) {
            nbLibre -= it->second;
            clog << it->first << "V = " << nbPlaces - nbLibre << ", L = " << nbLibre << endl;
            assert(nbLibre >= 0);
        }

        // commence a verifier ici
        clog << "commence a verifier" << endl;
        if (it == evenements.end()) {
            retourOk = nbLibre > 0;
        } else { // verifie jusqua la fin, arrete si dispo faux
            for (;retourOk && it != evenements.end();++it){
                nbLibre -= it->second;
                clog << it->first << "V = " << nbPlaces - nbLibre << ", L = " <<  nbLibre << endl;
                retourOk = nbLibre > 0;
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