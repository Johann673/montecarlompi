#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include<time.h>

int find_index(int a[], int num_elements, int value);

int main(int argc, char *argv[]) {
	int numProc;    // Numero d'idenfification du processus.
	int nbProcs;    // Nombre total de processus.
	  
	int range = 36;
	int repetition;
	int combinaison[6] = {1,2,3,4,5,6};
	//MPI_Status statut;
	
	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &numProc );
	MPI_Comm_size( MPI_COMM_WORLD, &nbProcs );

	// Récupère les arguments
	repetition = atoi(argv[1]); 

	// Initialise le tableau de résultat
	int resultat[7] = {0};
		// numéro aléatoire en fonction du numéro du thread
		srand(time(NULL) ^ numProc);
		for (int i = 0; i < repetition; i++) {
			int nbGagnants = 0;
			int tirageTmp[6] = {};
			for(int j = 0; j < 6; j++) {
				int number = 0;
				do {
					number = rand() % range;
				} while(find_index(tirageTmp, 6, number) > -1);
				// Vérifie si bon numéro dans le tirage
				if(find_index(combinaison, 6, number) > -1) {
					nbGagnants++;
				}
			}
			//Tirage terminé, enregistre les résultats
			resultat[nbGagnants]++;
		}
	

    for(int i = 0; i < 7; i++) {
        printf("%d -> %d \n", i, resultat[i]);
    }

	MPI_Finalize();
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
