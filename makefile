#Options de compilation

MAKE = make
RM = rm -f
CFLAGS = -std=c99
CC = mpicc
RUN = mpirun

.c.o:
	$(CC) -c $(CFLAGS) $<

MAIN = lotoMPI

#Paramètres d'exécution
I = 10000000
NP = 4

#sequentiel statique dynamique
default: compile

compile: 
	$(CC) common.c loto-dynamique.c loto-seq.c loto-statique.c lotoMPI.c -o lotoMPI $(CFLAGS)

tests: compile
	${RUN} -np $(NP) $(MAIN) $(I) 1

mesures: compile
	${RUN} -np $(NP) $(MAIN) $(I)

# CLEAN
TMPFILES = $(MAIN)\
           TAGS \
           *~ *.o \

clean:
	@$(RM) $(TMPFILES)
		 
