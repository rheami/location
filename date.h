/*
  INF3105 - Structures de données et algorithmes
  UQAM / Département d'informatique
  Automne 2014
  
  Squelette de départ. Vous pouvez modifier ce fichier à votre guise.
  Vous n'êtes pas obligés de l'utiliser.
*/

#if !defined(_DATE__H_)
#define _DATE__H_

#include <iostream>

class Date{
  public:
    Date();
	Date(int min);
	inline bool operator <(const Date& d) const{
		return minutes < d.minutes;
	}

	inline bool operator <=(const Date& d) const{
		return minutes <= d.minutes;
	}
  
  private:
    int minutes;
    
  friend std::ostream& operator << (std::ostream&, const Date& date);
  friend std::istream& operator >> (std::istream&, Date& date);
};

#endif

