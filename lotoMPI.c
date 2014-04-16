#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "header.h" 

<<<<<<< HEAD

=======
// Fonction effectuant les mesures de temps d'exécution
void mesures() {
}
>>>>>>> 95ae1de0373fa460ba2a78f3f06c1e043ba6d2bd

// Fonction effectuant les tests
void test(int repetition, int numProc) {
	double tempsEcoule = 0;
	tempsEcoule = play_seq(repetition, 1); 
	if(numProc == 0) {
		printf("Sequentiel = %6.1f ms\n", 1000.0 * tempsEcoule);
	}
	tempsEcoule = play_statique(repetition, 1); 
	if(numProc == 0) {
		printf("Statique = %6.1f ms\n", 1000.0 * tempsEcoule);
	}
	tempsEcoule = play_dynamique(repetition, 1); 
	if(numProc == 0) {
		printf("Dynamique = %6.1f ms\n", 1000.0 * tempsEcoule);
	}
}

// Fonction principale du programme
int main(int argc, char *argv[]) {
	MPI_Init( &argc, &argv );
	int numProc;
	double tempsEcoule = 0;
	MPI_Comm_rank(MPI_COMM_WORLD, &numProc);
	int repetition = atoi(argv[1]);
	if(argc > 2) {
    	int type = atoi(argv[2]);
		if(type) {
			test(repetition, numProc);
		}
	} else {
<<<<<<< HEAD

		// Mesures :
=======
>>>>>>> 95ae1de0373fa460ba2a78f3f06c1e043ba6d2bd
		tempsEcoule = play_seq(repetition, 0); 
		if(numProc == 0) {
			printf("Temps requis = %6.1f ms\n", 1000.0 * tempsEcoule);
		}
		tempsEcoule = play_statique(repetition, 0); 
		if(numProc == 0) {
			printf("Temps requis = %6.1f ms\n", 1000.0 * tempsEcoule);
		}
		tempsEcoule = play_dynamique(repetition, 0); 
		if(numProc == 0) {
			printf("Temps requis = %6.1f ms\n", 1000.0 * tempsEcoule);
		}
	}
	MPI_Finalize();
}
