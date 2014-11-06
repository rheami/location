/*
  INF3105 - Structures de données et algorithmes
  UQAM / Département d'informatique
  Automne 2014
  Squelette de départ pour le TP2.
*/

#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include "arbremap.h"
#include "succ.h"
#include "date.h"
using namespace std;

int tp2(istream& entree){
    cerr << "tp2" << endl;
    ArbreMap<std::string, Succursale> succursales; // todo utiliser arbremap
    //map<string, Succursale> succursales;
    
    int id=1;
    while(entree){ // todo enlever && id < 1000200
        Succursale succursale;
        std::string commande;
        entree >> commande >> ws;
        if(!entree) break;
        cout << id << " : ";
       
        if(commande=="creer"){
            entree >> succursale;
            succursales[succursale.getName()] = succursale;
            cout << "Creee" << endl;
        }else if(commande=="reserver"){
            string origine, destination;
            Date debut, fin;
            entree >> origine >> destination >> debut >> fin;
            //cerr << endl << id << " " << commande << " " << origine <<  " " << destination << " " << debut << " " << fin << endl;
            bool ok = false;
            if (fin < debut) {
                cout << "Commande '" << commande << " " << debut << " " << fin << "' invalide!" << endl;
                return 2;
            }
            Succursale &succursaleO = succursales[origine];
            Succursale &succursaleF = succursales[destination];
            //todo tester si elles existent

            if (succursaleO==succursaleF) {
                if (succursaleO.verifierDisponibiliteEtRetour(debut, fin)) {
                    succursaleO.ajouterEvenementDepart(debut);
                    succursaleF.ajouterEvenementRetour(fin);
                    ok = true;
                }
            } else {
                if (succursaleO.verifierDisponibilite(debut, fin) &&
                        succursaleF.verifierRetourPossible(fin)) {
                    succursaleO.ajouterEvenementDepart(debut);
                    succursaleF.ajouterEvenementRetour(fin);
                    ok = true;
                }
            }



            cout << (ok ? "Acceptee" : "NonDispo") << endl;
        }else{
            cout << "Commande '" << commande << "' invalide!" << endl;
            return 2;
        }

        char pointvigule=0;
        entree >> pointvigule >> ws;
        if(pointvigule!=';'){
            cout << "Fichier d'entrée invalide!" << endl;
            return 3;
        }
        id++;
    }
    return 0;
}
// syntaxe d'appel : ./tp2 [nomfichier.txt]
int main(int argc, const char** argv){
    // Gestion de l'entrée :
    //  - lecture depuis un fichier si un argument est spécifié;
    //  - sinon, lecture depuis std::cin.
    if(argc>1){
         std::ifstream entree_fichier(argv[1]);
         if(entree_fichier.fail()){
             std::cerr << "Erreur d'ouverture du fichier '" << argv[1] << "'" << std::endl;
             return 1;
         }
         return tp2(entree_fichier);
    }else
         return tp2(std::cin);

    return 0;
}

