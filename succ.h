#if !defined(__SUCC_H__)
#define __SUCC_H__
#include <string>
#include <map>
#include "date.h"
#include "arbremap.h"

using namespace std;

class Succursale{
  public:
    // À compléter...
    Succursale() :derniereDate(0){
	}
    Succursale(std::string _nom, int _nbVoitures, int _nbPlacesLibres) {
        nomSuccursale = _nom;
        nbVoitures = _nbVoitures;
        nbPlacesLibres = _nbPlacesLibres;
        nbPlaces = nbVoitures + nbPlacesLibres;
    }

    bool verifierDisponibilite(Date, Date);
    bool verifierRetourPossible(Date);
    bool verifierDisponibiliteEtRetour(Date, Date);
    void ajouterEvenementDepart(Date);
    void ajouterEvenementRetour(Date);

    bool operator==(const Succursale &) const;
    string getName() const;

    ~Succursale() {
    }

private:

    string nomSuccursale;
    int nbVoitures;
    int nbPlacesLibres;
    int nbPlaces;

	Date derniereDate;
	int nbVoitureDerniereDate;
    /*
     Une reservation = deux évenements :
      1) prendre voiture a une date : la valeur  est -1 : nbVoiture -1 et NbPlaceLibre +1
      2) raporter voiture a une date : la valeur est +1 : nbVoiture +1 et NbPlaceLibre -1
      Si un autre évènement a lieu pour la même date on ajoute ou retire 1 (devient +2 etc)

     */
    ArbreMap<Date, int> evenements; // todo utiliser arbremap

    //map<Date, int> evenements;

    friend istream& operator >> (istream& is, Succursale&);
    friend ostream& operator << (ostream& os, const Succursale);

};

#endif

