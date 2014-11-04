#!/bin/bash
##########################################################################
# UQAM - Département d'informatique
# INF3105 - Structures de données et algorithmes
# TP2 - Arbres AVL + ArbreMap appliqués à la location de voitures
# http://ericbeaudry.ca/INF3105/tp1/
#
# Script d'évaluation du TP2
#
# Instructions:
# 1. Déposer ce script avec les fichiers problèmes dans un répertoire 
#    distinct (ex: tests).
# 2. Se placer dans le répertoire contenant votre programme ou contenant
#    la liste des soumissions Oto (*.tp_oto).
# 3. Lancer ce script (ex: ../tests/evaluer.sh).
##########################################################################

# Obtenir le chemin du répertoire contenant le présent script et les fichiers tests
pushd `dirname $0`
repertoire_tests=`pwd`
# Lister les fichier test*.txt disponibles
tests=`ls test[CDG]???.txt`
popd

# Exécutable du programme à évaluer
programme="tp2"

if [ `pwd` -ef $repertoire_tests ];
then
    echo "Ce script doit être dans un répertoire différent de celui contenant votre ${programme}."
    echo "Ce script a été arrêté afin de ne pas écraser les fichiers test_[CDG]*.resultat!"
    exit -2;
fi

# Exécutable du programme de validation
OS=`uname`
valideur="${repertoire_tests}/valideur"

if [ -x ${valideur}-${OS} ]
then
    valideur=${valideur}-${OS}
fi

echo "Évaluation des temps d'exécution de ${programme} sur les jeux de tests."

# Détection si l'utilitaire time sous Linux est disponible (peut afficher 0.00)
/usr/bin/time -f %U echo 2>&1 > /dev/null
souslinux=$?

# Fixer les limites : 60 s, 2048Mo mémoire et 20Mo fichier
ulimit -t 60 -v 2097152 -f 20480
echo "Limites :"
ulimit -t -v -f

date=`date +%Y%m%d_%H%M%S`


##### La fonction qui évalue un TP ######
function EvaluerTP
{
    ## Forcer la recompilation.
    #rm $programme *.o
    #make clean   
    
    logfile="log-${date}.txt"
	echo "Les résultats sont déposés dans $logfile."

	echo "Machine : " `hostname` "."
	echo "#Machine : " `hostname` "."  > $logfile
	echo "Date début : $date."
	echo "#Date début : $date."  >> $logfile
	echo "Limite de `ulimit -t` secondes par test."
	echo "#Limite de `ulimit -t` secondes par test."  >> $logfile

    # Pour statistiques : nombre de lignes de code...
    echo "Taille des fichiers source :" >> ${logfile}
    wc *.{c*,h*}  >> ${logfile}

    taille=`wc *.{c*,h*} | grep total`
    sommaire="$taille"
    
    make $programme
    
    # Vérification de l'existance du programme.
    if [ ! -e ${programme} ]
	    then
	    echo "  ERREUR : le programme ${programme} est inexistant!"
	    return
    fi
    if [ ! -x ${programme} ]
	    then
	    echo "  ERREUR : l'executable ${programme} n'est pas exécutable!"
	    return
    fi


	echo 
	echo "#" >> $logfile

	echo -e "Test    \tTaille\tOpt?\tCPU\tMém.(k)"
	echo -e "Test    \tTaille\tOpt?\tCPU\tMém.(k)" >> $logfile

	for test in $tests;
	do
    	requete="${requete#*_}"
    	args=`echo $requete | sed s/'-'/' '/g`
    
	    fichiertest=$repertoire_tests/$test
    	tailletest=`cat $fichiertest | wc -l`
    
	    fichierresultat="${test%.txt}.resultat"
    	fichiersolution="$repertoire_tests/${test%.txt}.resultat"
    
        if [ $souslinux -eq 0 ]; then
            tcpu="`(/usr/bin/time -f "%U\t%Mk" ./$programme $fichiertest > $fichierresultat) 2>&1 | tail -n 1`"
    	else
        	tcpu=`(time -p ./$programme $fichiertest $args > $fichierresultat) 2>&1 | egrep user | cut -f 2 -d " "`
        fi
    
    	score="?"
	    optimal="?"
    	if ( [ -x ${valideur} ] && [ -e $fichierresultat ] )
	    then
        	score=`$valideur $fichiertest $fichierresultat`
        	if( [ -e $fichiersolution ] )
	        then
    	        scoresolution=`$valideur $fichiertest $fichiersolution`
        	    [ "$score" != "$scoresolution" ];
            	optimal=$?
        	fi
    	else
        	if( [ -e $fichiersolution ] )
        	then
            	diff -tibw $fichierresultat $fichiersolution 2>&1 > /dev/null
        		if [ $? -eq 0 ];
        		then
        	    	optimal="OK"
         		else
         	    	optimal="Echec"
        		fi
        	fi
    	fi

    	echo -e "$test\t$tailletest\t$optimal\t$tcpu"
    	echo -e "$test\t$tailletest\t$optimal\t$tcpu" >> $logfile
    	sommaire="${sommaire}\t${optimal}\t${tcpu}"
	done
}

# Lister les soumissions Oto (répertoires terminant par .tp_oto)
tps=`ls -1 | grep .tp_oto`
if [ ! -n "$tps" ]; then
  echo "allo"
  tps="."
fi

echo "#Rapport de correction" > "rapport-${date}.txt"
echo "#Date: ${date}" >> "rapport-${date}.txt"
echo -e -n "#\t" >> "rapport-${date}.txt"
for test in ${tests}; do
   echo -e -n "\t${requete}\t\t" >> "rapport-${date}.txt"
done
echo >> "rapport-${date}.txt"
echo -e -n "#Soumission\tTaille sources" >> "rapport-${date}.txt"
for test in ${tests}; do
   echo -e -n "\tOpt?\tCPU\tMem" >> "rapport-${date}.txt"
done
echo >> "rapport-${date}.txt"

    
for tp in $tps; do
    sommaire=""
    echo "## CORRECTION : $tp"
    pushd $tp
    	EvaluerTP
    popd
    #echo -e ">> ${sommaire}"
    echo -e "${tp}\t${sommaire}" >> "rapport-${date}.txt"
done



