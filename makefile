
MAKE = make
RM = rm -f
CFLAGS = -std=c99
CC = mpicc
RUN = mpirun

.c.o:
	$(CC) -c $(CFLAGS) $<

		
MAIN = lotoMPI

NP = 4
EXEC = sequentiel
#sequentiel statique dynamique

default: compile

compile: 
	$(CC) common.c loto-dynamique.c loto-seq.c loto-statique.c lotoMPI.c -o lotoMPI $(CFLAGS)

tests: compile
	${RUN} -np $(NlP) $(MAIN) 10000000 1

mesures: compile
	${RUN} -np $(NP) $(MAIN) 10000000


# CLEAN

TMPFILES = $(MAIN)\
           TAGS \
           *~ *.o \

clean:
	@$(RM) $(TMPFILES)



		 
