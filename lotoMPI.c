#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "header.h" 

void mesures() {

}

void test(int file, int repetition, int numProc) {
	double tempsEcoule = 0;
	if(file == 0) {
		tempsEcoule = play_seq(repetition, 1); 
		if(numProc == 0) {
			printf( "Temps requis = %6.1f ms\n", 1000.0 * tempsEcoule );
		}
	} else if(file == 1) {
		tempsEcoule = play_statique(repetition, 1); 
		if(numProc == 0) {
			printf( "Temps requis = %6.1f ms\n", 1000.0 * tempsEcoule );
		}
	} else if(file == 2) {
		tempsEcoule = play_dynamique(repetition, 1); 
		if(numProc == 0) {
			printf( "Temps requis = %6.1f ms\n", 1000.0 * tempsEcoule );
		}
	}
}

int main(int argc, char *argv[]) {
	MPI_Init( &argc, &argv );
	int numProc;
	double tempsEcoule = 0;
	int repetition = 10000000; 
	
	MPI_Comm_rank( MPI_COMM_WORLD, &numProc );

	tempsEcoule = play_seq(repetition, 0); 
	if(numProc == 0) {
		printf( "Temps requis = %6.1f ms\n", 1000.0 * tempsEcoule );
	}

	tempsEcoule = play_statique(repetition, 0); 
	if(numProc == 0) {
		printf( "Temps requis = %6.1f ms\n", 1000.0 * tempsEcoule );
	}

	tempsEcoule = play_dynamique(repetition, 0); 
	if(numProc == 0) {
		printf( "Temps requis = %6.1f ms\n", 1000.0 * tempsEcoule );
	}

	MPI_Finalize();
}
