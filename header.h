// Versions de l'implémentation
double play_seq(int repetition, int affiche);
double play_statique(int repetition, int affiche);
double play_dynamique(int repetition, int nbParTache, int affiche);

// Fonction auxililaires
int nbElementsParTache(int position, int nbTachesTotales, int nbThreads);
int find_index(int a[], int num_elements, int value);

// Opérations appelées dans les différentes versions du programme
void tirage(int combinaison[], int resultat[], int nbElements, int numProc);
void coordonnateur(int* resultatFinal, int repetition, int nbParTache, int nbTravailleurs);
void travailleur(int* combinaison, MPI_Comm comm);
