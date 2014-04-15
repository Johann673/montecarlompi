#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "header.h" 


double play_seq(int repetition, int affiche) {
	int numProc;    // Numero d'idenfification du processus.

	
	MPI_Comm_rank( MPI_COMM_WORLD, &numProc );

	if(numProc == 0) {

		int combinaison[6] = {1,2,3,4,5,6};

		// Le processus maitre alloue la mémoire pour le résultat
		int resultat[7] = {0};

		// On démarre la minuterie
		double tempsEcoule = -MPI_Wtime();

		// Effectue le tirage
		tirage(combinaison, resultat, repetition, numProc);

		tempsEcoule += MPI_Wtime();

		if(affiche) {
			for(int i = 0; i < 7; i++) {
				printf("%d -> %.3f%% \n", i, (100*((float)resultat[i])/repetition));
			}
		}

		return tempsEcoule;

	}

	
	return 0;
	
}


