#if !defined(__SUCC_H__)
#define __SUCC_H__
#include <string>
#include <map>
#include "date.h"

using namespace std;

class Succursale{
  public:
    // À compléter...
    Succursale(){}
    Succursale(std::string _nom, int _nbVoitures, int _nbPlacesLibres) {
        nomSuccursale = _nom;
        nbVoitures = _nbVoitures;
        nbPlacesLibres = _nbPlacesLibres;
        nbPlaces = nbVoitures + nbPlacesLibres;

    }

    bool verifierDisponibilite(Date, Date);
    bool verifierRetourPossible(Date);


    string getName() const;

    ~Succursale() {
    }



private:
// À compléter...
    string nomSuccursale;
    int nbVoitures;
    int nbPlacesLibres;
    int nbPlaces;
    class Etat {

    public:
        int V;
        int L;
    };
    map<Date, Etat> evenements; // ne fnctne pas il y a plusieur evements de meme date

    void ajouterEvenementDepart(Date);
    void ajouterEvenementRetour(Date);

    friend istream& operator >> (istream& is, Succursale&);
    friend ostream& operator << (ostream& os, const Succursale);

};

#endif

