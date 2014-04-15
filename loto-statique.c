#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "header.h"

double play_statique(int repetition, int affiche) {
	int numProc;    // Numero d'idenfification du processus.
	int nbProcs;    // Nombre total de processus.
	  
	int combinaison[6] = {1,2,3,4,5,6};
	
	MPI_Comm_rank( MPI_COMM_WORLD, &numProc );
	MPI_Comm_size( MPI_COMM_WORLD, &nbProcs );

	// On démarre la minuterie
	MPI_Barrier( MPI_COMM_WORLD );
	double tempsEcoule = -MPI_Wtime();


	// Résultat locaux
	int mon_resultat[7] = {0};
	int nbElements = nbElementsParTache(numProc+1, repetition, nbProcs);
	// Effectue le tirage
	tirage(combinaison, mon_resultat, nbElements, numProc);

	// Regroupe les résultats dans le résultat final
	int resultatFinal[7] = {0};
	MPI_Reduce(mon_resultat, resultatFinal, 7, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	tempsEcoule += MPI_Wtime();
 

	if ( numProc == 0 ) {
		if(affiche) {
			for(int i = 0; i < 7; i++) {
				printf("%d -> %.3f%% \n", i, (100*((float)resultatFinal[i])/repetition));
			}
		}
		return tempsEcoule;
	}
	return 0;
}

int nbElementsParTache(int position, int nbTachesTotales, int nbThreads) {
	int nbParThread = (int)floor(ceil(nbTachesTotales / nbThreads));
	if((position * nbParThread) > nbTachesTotales) {
		nbParThread = nbTachesTotales - (nbParThread * (position-1));
	}
	return nbParThread;
}

