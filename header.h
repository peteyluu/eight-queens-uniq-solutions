#ifndef HDR
#define HDR

#include <stdio.h>
#include <stdlib.h>

#define DIM 8
#define N_QUEENS 8

typedef struct coord
{
	int x;
	int y;
} point;

point *curr_soln_coords;
int curr_soln_pos;
point *queen_coords;
int queen_coord_pos;
int num_queens;

void render(int **grid);
void init_grid(int **grid);
int solve_queens(int **grid, int row);
int queen_safe(int row, int col);
void create_coord(int row, int col);
void free_array(int **grid);
void print_coords(point *coords);
void copy_coords(point *, point *);
int permute_queens(int **grid, point *coords);
#endif
