FLAGS = -std=c99
GCC = mpicc
RUN = mpirun
.SUFFIXES: .c .out
.c.out:l
		$(GCC) $(FLAGS) $*.c
		
CLASSES = \
		main.c
		

default: classes

compile: classes

classes: $(CLASSES:.c=.out)

clean: 
		$(RM) *.out

run: classes 
	${RUN} -np 2 a.out 10000000

		 
