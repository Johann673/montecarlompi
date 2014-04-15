#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "header.h" 

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
