#include <time.h>
#include "maze.h"

void CreateMaze(struct room []);
void PrintMaze(struct room []);
int SolveMaze1(struct room []);
int SolveMaze2(struct room []);
int SolveMaze3(struct room []);

int main(void)
{
        struct room maze[NR_ROOM];
        srand((unsigned)time(NULL));
		do {
				system("cls");
				printf("Generating Maze...Please wait...\n\n");
				printf("Entrance: Room 0, Exit: Room %d\n", NR_ROOM - 1);
				CreateMaze(maze);     
				PrintMaze(maze);             /* 输出生成的迷宫 */
				printf("\n*Divide and Conquer: \t%d-admissible maze!\n", SolveMaze1(maze));
				printf("*Modified Bellman-Ford: %d-admissible maze!\n", SolveMaze2(maze));
                    printf("*DFS:\t\t\t%d-admissible maze!\n", SolveMaze3(maze));
		} while(getchar() != 'q');
        return(0);
}
