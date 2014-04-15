
MAKE = make
RM = rm -f
CFLAGS = -std=c99 -lm
CC = mpicc
RUN = mpirun

.c.o:
	$(CC) -c $(CFLAGS) $<

		
NP = 4
EXEC = loto-statique

EXECS = loto-dynamique loto-seq loto-statique

default: $(EXEC)

compile: $(EXEC)

tests: $(EXEC)
	${RUN} -np $(NP) $(EXEC) 10000000


# CLEAN

TMPFILES = $(EXECS)\
           TAGS \
           *~ *.o \

clean:
	@$(RM) $(TMPFILES)



		 
