#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <math.h>
#include <string.h>

int find_index(int a[], int num_elements, int value);
void tirage(int combinaison[], int resultat[], int nbElements, int numProc);



int main(int argc, char *argv[]) {
	int numProc;    // Numero d'idenfification du processus.

	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &numProc );

	if(numProc == 0) {

		int repetition;
		int combinaison[6] = {1,2,3,4,5,6};

		// Récupère les arguments
		repetition = atoi(argv[1]); 

		// Le processus maitre alloue la mémoire pour le résultat
		int resultat[7] = {0};

		// On démarre la minuterie
		double tempsEcoule = -MPI_Wtime();

		// Effectue le tirage
		tirage(combinaison, resultat, repetition, numProc);

		tempsEcoule += MPI_Wtime();

		for(int i = 0; i < 7; i++) {
			printf("%d -> %.3f%% \n", i, (100*((float)resultat[i])/repetition));
		}

		printf( "Temps requis = %6.1f ms\n", 1000.0 * tempsEcoule );

	}

	MPI_Finalize();

	return( 0 );
}

void tirage(int combinaison[], int resultat[], int nbElements, int numProc) {
	// numéro aléatoire
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

int find_index(int a[], int num_elements, int value) {
	int i;
	for (i=0; i<num_elements; i++) {
		if (a[i] == value) {
			return(value);
		}
	}
	return(-1);
}
