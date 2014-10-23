#if !defined(__SUCC_H__)
#define __SUCC_H__
#include <string>
//#include <arbreavl.h>
#include <set>
#include <map>
//#include <arbremap.h>
#include "date.h"

using namespace std;

class Succursale{
  public:
    // À compléter...

    Succursale(std::string _nom, int _nbVoitures, int _nbPlacesLibres) {
        nomSuccursale = _nom;
        nbVoitures = _nbVoitures;
        nbPlacesLibres = _nbPlacesLibres;
        nbPlaces = nbVoitures + nbPlacesLibres;
    }
    ~Succursale() {
    }



private:
// À compléter...
    std::string nomSuccursale;
    int nbVoitures;
    int nbPlacesLibres;
    int nbPlaces;
};

#endif

