# Makefile pour TP2.
# Adaptez ce fichier au besoin.

# Options standard.
#OPTIONS = -Wall

# L'option -g permet de générer les infos de débogage.
# Décommentez la ligne suivante si vous désirez utiliser un débogueur.
#OPTIONS = -g -O0 -Wall

# Les options -O, -O1, -O2, -O3 permetent d'optimiser le code binaire produit.
# Décommentez la ligne suivante si avant la remise finale
OPTIONS = -I ../../../lib3105/ -O2 -Wall -std=c++11

all: tp2

# Syntaxe : cible : dépendance1 dépendance2 ...
# Ensuite, la ou les ligne(s) débutant par une tabulation (\t) donne les commandes pour construire une cible
tp2: tp2.cpp succ.o date.o
	g++ $(OPTIONS) -o tp2 tp2.cpp date.o succ.o

date.o: date.h date.cpp
	g++ $(OPTIONS) -c -o date.o date.cpp

succ.o: succ.h succ.cpp date.h
	g++ $(OPTIONS) -c -o succ.o succ.cpp

testdate : testdate.cpp date.o
	g++ $(OPTIONS) -o testdate testdate.cpp date.o

clean :
	rm -f *.o
	rm -f tp2 testdate
	rm -f *~

