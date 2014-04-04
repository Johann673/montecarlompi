#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include<time.h>
#include <math.h>
#include <string.h>

int nbElementsParTache(int position, int nbTachesTotales, int nbThreads);
int find_index(int a[], int num_elements, int value);
void tirage(int combinaison[], int resultat[], int nbElements, int numProc);



int main(int argc, char *argv[]) {
	int numProc;    // Numero d'idenfification du processus.
	int nbProcs;    // Nombre total de processus.
	  
	int repetition;
	int combinaison[6] = {1,2,3,4,5,6};
	//MPI_Status statut;
	
	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &numProc );
	MPI_Comm_size( MPI_COMM_WORLD, &nbProcs );

	// Récupère les arguments
	repetition = atoi(argv[1]); 

	// Le processus maitre alloue la mémoire pour le résultat
	int resultat[nbProcs][7];
	if ( numProc == 0 ) {
		memset(resultat, 0, sizeof resultat);
	}

	// On démarre la minuterie
	MPI_Barrier( MPI_COMM_WORLD );
	double tempsEcoule = -MPI_Wtime();

	// Résultat locaux
	int *mon_resultat;
	mon_resultat = (int *) malloc( 7 * sizeof(int) );

	MPI_Scatter( mon_resultat, 7, MPI_INT, mon_resultat, 7, MPI_INT, 0, MPI_COMM_WORLD );
	// Initialise les données à 0 pour chaque thread
	for(int i = 0; i < 7; i++) {
		mon_resultat[i] = 0;
	}
	int nbElements = nbElementsParTache(numProc+1, repetition, nbProcs);

	// Effectue le tirage
	tirage(combinaison, mon_resultat, nbElements, numProc);

	MPI_Gather( mon_resultat, 7, MPI_INT, resultat[numProc], 7, MPI_INT, 0, MPI_COMM_WORLD );

	tempsEcoule += MPI_Wtime();
 
	MPI_Finalize();
	if ( numProc == 0 ) {
		int resultatFinal[7] = {0};
		for(int k = 0; k < nbProcs; k++) {
			for(int i = 0; i < 7; i++) {
				resultatFinal[i] += resultat[k][i];
			}
		}
		
		for(int i = 0; i < 7; i++) {
			printf("%d -> %.3f%% \n", i, (100*((float)resultatFinal[i])/repetition));
		}

		printf( "Temps requis = %6.1f ms\n", 1000.0 * tempsEcoule );
	}
	return( 0 );
}

void tirage(int combinaison[], int resultat[], int nbElements, int numProc) {
	// numéro aléatoire en fonction du numéro du thread
	srand(time(NULL) ^ numProc);
	for (int i = 0; i < nbElements; i++) {
		int nbGagnants = 0;
		int tirageTmp[6] = {};
		for(int j = 0; j < 6; j++) {
			int number = 0;
			do {
				number = rand() % 36;
			} while(find_index(tirageTmp, 6, number) > -1);
			// Vérifie si bon numéro dans le tirage
			if(find_index(combinaison, 6, number) > -1) {
				nbGagnants++;
			}
		}
		//Tirage terminé, enregistre les résultats
		resultat[nbGagnants]++;
	}
}

int nbElementsParTache(int position, int nbTachesTotales, int nbThreads) {
	int nbParThread = (int)floor(ceil(nbTachesTotales / nbThreads));
	if((position * nbParThread) > nbTachesTotales) {
		nbParThread = nbTachesTotales - (nbParThread * (position-1));
	}
	return nbParThread;
}

int find_index(int a[], int num_elements, int value) {
	int i;
	for (i=0; i<num_elements; i++) {
		if (a[i] == value) {
			return(value);
		}
	}
	return(-1);
}
