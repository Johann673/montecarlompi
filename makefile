
MAKE = make
RM = rm -f
CFLAGS = -std=c99
CC = mpicc
RUN = mpirun

.c.o:
	$(CC) -c $(CFLAGS) $<

		
MAIN = lotoMPI

NP = 4
EXEC = loto-statique

EXECS = loto-dynamique loto-seq loto-statique

default: $(EXEC)

compile: 
	$(CC) common.c loto-dynamique.c loto-seq.c loto-statique.c lotoMPI.c -o lotoMPI $(CFLAGS)

tests: $(EXEC)
	${RUN} -np $(NP) $(EXEC) 10000000

mesures: compile
	${RUN} -np $(NP) $(MAIN) 10000000


# CLEAN

TMPFILES = $(EXECS)\
           TAGS \
           *~ *.o \

clean:
	@$(RM) $(TMPFILES)



		 
