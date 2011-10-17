CFLAGS = -Wall -g -lmcheck
maze: CreateMaze.o SolveMaze1.o SolveMaze2.o SolveMaze3.o maze.h main.c
	gcc $(CFLAGS) -o maze CreateMaze.o SolveMaze1.o SolveMaze2.o SolveMaze3.o main.c
CreateMaze.o: CreateMaze.c maze.h
	gcc $(CFLAGS) -o CreateMaze.o -c CreateMaze.c
SolveMaze1.o: SolveMaze1.c maze.h
	gcc $(CFLAGS) -o SolveMaze1.o -c SolveMaze1.c
SolveMaze2.o: SolveMaze2.c maze.h
	gcc $(CFLAGS) -o SolveMaze2.o -c SolveMaze2.c
SolveMaze3.o: SolveMaze3.c maze.h
	gcc $(CFLAGS) -o SolveMaze3.o -c SolveMaze3.c
clean:
	rm -f *.o *~ maze