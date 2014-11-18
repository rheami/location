#include "succ.h"
#include <map>
#include <assert.h>
using namespace std;

string Succursale::getName() const{
    return nomSuccursale;
}


bool Succursale::verifierDisponibiliteEtRetour(const Date prise, const Date retour){
	bool dispo = true;
	
	if (derniereDate<prise && 1>nbVoitureDerniereDate)
	{
		dispo = false;

	}
	else if (derniereDate < prise && nbVoitureDerniereDate>1)
	{

	}
	else
	{
		int nbVoit = nbVoitures;
		int nbLibre;
		//cerr << "verifier disponibilite " << nomSuccursale << " " << prise << " " << retour << ": V = " << nbVoit << ", L = " << nbPlacesLibres << finl;

		if (evenements.vide())
			return nbVoitures > 0;
		// et au moins une place libre celle qu on vient de liberer;

		// 1- la voiture doit etre disponible pour la duree

		//itere du debut a prise (calcule etat a prise)
		ArbreMap<Date, int>::Iterateur it = evenements.debut();
		ArbreMap<Date, int>::Iterateur fin = evenements.fin();
		for (; it != fin && it.cle() <= prise; ++it) {
			nbVoit += it.valeur();
			//  cerr << it->first << "V = " << nbVoit << ", L = " << nbPlaces - nbVoit << finl;
			//assert(nbVoit >= 0);
		}

		// continue a calculer jusqua retour et verifie la disponibilite ( dispo = nbVoit > 0)
		//cerr << "commence a verifier disponibilite" << finl;
		
			if (it == fin){
				dispo = nbVoit > 0;
			}
			else { // verifie jusqua retour arrete si dispo faux ou rfinu a la fin
				dispo = nbVoit > 0;
				for (; dispo && it != fin && it.cle() < retour; ++it){
					nbVoit += it.valeur();
					// cerr << it->first << "V = " << nbVoit << ", L = " << nbPlaces - nbVoit << finl;
					dispo = nbVoit > 0;
				}
			}
			if (derniereDate < retour && (nbVoitureDerniereDate - 1) < nbPlaces)
			{

			}
			else if (derniereDate < retour)
			{
				dispo = false;
			}
			else
			{
			if (dispo) {
				//if (dispo) cerr << "ok" << finl;

				nbLibre = (nbPlaces - nbVoit) + 1; // la prise de possesion libère une place

				// la place doit etre disponible a partir de retour jusqua la fin des evenements actuels

				// continue a calculer jusqua fin et verifie si place libres
				//cerr << "commence a verifier retour" << finl;
				if (it == fin) {
					dispo = nbLibre > 0;
				}
				else { // verifie jusqua la fin, arrete si dispo faux
					dispo = nbLibre > 0;
					for (; dispo && it != fin; ++it){
						nbLibre -= it.valeur();
						//cerr << it->first << "V = " << nbPlaces - nbLibre << ", L = " <<  nbLibre << finl;
						dispo = nbLibre > 0;
					}
				}
			}
		}
		// if (dispo) cerr << "ok" << finl;
	}
	return dispo;
}

bool Succursale::verifierDisponibilite(const Date prise,const Date retour){
    bool dispo=true;

	if (derniereDate<prise && 1>nbVoitureDerniereDate)
	{
		dispo = false;

	}
	else if (derniereDate<prise && nbVoitureDerniereDate>1)
	{
		
	}
	else
	{
		int nbVoit = nbVoitures;
		// cerr << "verifier disponibilite " << nomSuccursale << " " << prise << " " << retour << ": V = " << nbVoit << ", L = " << nbPlacesLibres << finl;

		if (evenements.vide())
			return nbVoitures > 0;
		// 1- la voiture doit etre disponible de prise a la fin (pas de retour ici)

		//itere du debut a prise (calcule etat a prise)
		ArbreMap<Date, int>::Iterateur it = evenements.debut();
		ArbreMap<Date, int>::Iterateur fin = evenements.fin();
		for (; it != fin && it.cle() <= prise; ++it) {
			nbVoit += it.valeur();
			//    cerr << it->first << "V = " << nbVoit << ", L = " << nbPlaces - nbVoit << finl;
			assert(nbVoit >= 0);
		}

		// continue a calculer jusqua fin et verifie la disponibilite ( dispo = nbVoit > 0)
		//cerr << "commence a verifier disponibilite" << finl;
		if (it == fin){
			dispo = nbVoit > 0;
		}
		else { // verifie jusqua retour arrete si dispo faux ou rfinu a la fin
			dispo = nbVoit > 0;
			for (; dispo && it != fin; ++it){
				nbVoit += it.valeur();
				//cerr << it->first << "V = " << nbVoit << ", L = " << nbPlaces - nbVoit << finl;
				dispo = nbVoit > 0;
			}
		}

		// if (dispo) cerr << "ok" << finl;
	}
    return dispo;
}


bool Succursale::verifierRetourPossible(const Date retour){
    bool retourOk = true;
	
	if (derniereDate<retour &&nbVoitureDerniereDate<nbPlaces)
	{
		
	}
	else if (derniereDate<retour)
	{
		retourOk = false;
	}
	else 
	{
		int nbLibre = nbPlacesLibres;
		//cerr << "verifier retour " << nomSuccursale << " " << retour << ": V = " << nbVoitures << ", L = " << nbLibre << finl;

		if (evenements.vide())
			return  nbPlacesLibres > 0;

		ArbreMap<Date, int>::Iterateur it = evenements.debut();
		ArbreMap<Date, int>::Iterateur fin = evenements.fin();
		// la place doit etre disponible a partir de retour jusqua la fin des evenements actuels  !!
		for (; it != fin && it.cle() <= retour; ++it) {
			nbLibre -= it.valeur();
			// cerr << it->first << "V = " << nbPlaces - nbLibre << ", L = " << nbLibre << finl;
			assert(nbLibre >= 0);
		}

		// commence a verifier ici
		//cerr << "commence a verifier" << finl;
		if (it == fin) {
			retourOk = nbLibre > 0;
		}
		else { // verifie jusqua la fin, arrete si dispo faux
			retourOk = nbLibre > 0;
			for (; retourOk && it != fin; ++it){
				nbLibre -= it.valeur();
				//  cerr << it->first << "V = " << nbPlaces - nbLibre << ", L = " <<  nbLibre << finl;
				retourOk = nbLibre > 0;
			}
		}
	}
   // if (retourOk) cerr << "ok" << finl;

    return retourOk;
}



istream& operator >> (istream& is, Succursale& succursale) {
    is >> succursale.nomSuccursale >> succursale.nbVoitures >> succursale.nbPlacesLibres;
    succursale.nbPlaces = succursale.nbVoitures + succursale.nbPlacesLibres;
	succursale.nbVoitureDerniereDate = succursale.nbVoitures;
    return is;
}

ostream& operator << (ostream& os, const Succursale succursale) {
    os << " succ " << succursale.nomSuccursale << " voitures disponibles = " << succursale.nbVoitures << " Stat Libres = " << succursale.nbPlacesLibres;
    return os;
}