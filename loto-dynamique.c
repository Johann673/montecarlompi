#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "header.h"

#define MSG_NB_REPETITION	1
#define MSG_TERMINER      	2
#define MSG_REQUETE_TACHE 	3
#define MSG_RESULTAT		4


double play_dynamique(int repetition, int affiche) {
	int numProc;    // Numero d'idenfification du processus.
	int nbProcs;    // Nombre total de processus.
	MPI_Comm comm_travailleurs;
	  
	int nbParTache = 1000;
	int combinaison[6] = {1,2,3,4,5,6};
	
	MPI_Comm_rank( MPI_COMM_WORLD, &numProc );
	MPI_Comm_size( MPI_COMM_WORLD, &nbProcs );

	double tempsEcoule = -MPI_Wtime();

	if ( numProc == 0 ) {
		// Coordonnateur.
		MPI_Comm_split( MPI_COMM_WORLD, MPI_UNDEFINED, numProc, &comm_travailleurs );
		
		int resultatFinal[7] = {0};		
		coordonnateur(resultatFinal, repetition, nbParTache, nbProcs-1);

		tempsEcoule += MPI_Wtime();
		
		if(affiche) {
			for(int i = 0; i < 7; i++) {
				printf("%d -> %.3f%% \n", i, (100*((float)resultatFinal[i])/repetition));
			}
		}
		
		return tempsEcoule;
	} else {
		// Travailleurs.
		MPI_Comm_split( MPI_COMM_WORLD, 0, numProc, &comm_travailleurs );
		travailleur( combinaison, comm_travailleurs );
	}
	return 0;
}

void coordonnateur(int* resultatFinal, int repetition, int nbParTache, int nbTravailleurs) {
	int nbTravailleursActifs = nbTravailleurs;   // Le nombre de travailleurs qui n'ont pas encore termine.
	int nbTaches = repetition / nbParTache;
 	int nbTachesEnvoyes = 0;                       // Le nombre de taches qui ont deja ete envoyes.

	

	while (nbTravailleursActifs > 0) {
		MPI_Status statut;
    	MPI_Recv(NULL, 0, MPI_BYTE, MPI_ANY_SOURCE, MSG_REQUETE_TACHE, MPI_COMM_WORLD, &statut);

		if (nbTachesEnvoyes < nbTaches) {
			MPI_Send( &nbParTache, 1, MPI_INT, statut.MPI_SOURCE, MSG_NB_REPETITION, MPI_COMM_WORLD );
			nbTachesEnvoyes++;
		} else {
			MPI_Send( NULL, 0, MPI_BYTE, statut.MPI_SOURCE, MSG_TERMINER, MPI_COMM_WORLD );
      		nbTravailleursActifs -= 1;
		}
	}

	MPI_Status statut;
	MPI_Recv(resultatFinal, 7, MPI_INT, MPI_ANY_SOURCE, MSG_RESULTAT, MPI_COMM_WORLD, &statut);

}

void travailleur(int* combinaison, MPI_Comm comm) {
	int ID_travailleur;
	int resultat[7] = {0};
  	MPI_Comm_rank(comm, &ID_travailleur);

	// On indique qu'on veut une tache.
  	MPI_Send(NULL, 0, MPI_BYTE, 0, MSG_REQUETE_TACHE, MPI_COMM_WORLD);

	for (;;) {
		int repetition = 0;
		MPI_Status statut; 
		MPI_Recv( &repetition, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &statut );
		
		if ( statut.MPI_TAG == MSG_TERMINER ) 
			break;
		
		MPI_Send( NULL, 0, MPI_BYTE, 0, MSG_REQUETE_TACHE, MPI_COMM_WORLD );
		tirage(combinaison, resultat, repetition, ID_travailleur);
	}

	int resultatFinal[7] = {0};
	MPI_Reduce(resultat, resultatFinal, 7, MPI_INT, MPI_SUM, 0, comm);

	// On transmet la table finale au coordonnateur.
	if (ID_travailleur == 0) {
		MPI_Send( resultatFinal, 7, MPI_INT, 0, MSG_RESULTAT, MPI_COMM_WORLD );
	}
}


