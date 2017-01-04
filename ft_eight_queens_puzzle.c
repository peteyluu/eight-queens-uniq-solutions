#include "header.h"

int ft_eight_queens_puzzle(void)
{
	int num, **grid;

	num = 0;
	curr_soln_coords = (point*)malloc(sizeof(point) * DIM);
	num_queens = 0;
	queen_coords = (point*)malloc(sizeof(point) * DIM);
	queen_coord_pos = 0;
	grid = (int**)malloc(sizeof(int*) * DIM);
	init_grid(grid);
	if (solve_queens(grid, 0))
	{
		copy_coords(queen_coords, curr_soln_coords);
		num++;
	}
	free(queen_coords);
	free_array(grid);

	while (1)
	{
		curr_soln_pos = 0;
		num_queens = 0;
		queen_coords = (point*)malloc(sizeof(point) * DIM);
		queen_coord_pos = 0;
		grid = (int**)malloc(sizeof(int*) * DIM);
		init_grid(grid);
		if (permute_queens(grid, curr_soln_coords))
		{
			num++;
			copy_coords(queen_coords, curr_soln_coords);
		}
		else
			break;
		free(queen_coords);
		free_array(grid);
	}
	free(curr_soln_coords);
	return (num);
}

int permute_queens(int **grid, point *coords)
{
	int row, col;

	if (num_queens == N_QUEENS)
		return (1);
	if (curr_soln_pos < DIM)
		row = coords[curr_soln_pos].x;
	else
		row = queen_coords[queen_coord_pos - 1].x + 1;
	while (row < DIM)
	{
		if (curr_soln_pos < DIM)
		{
			col = coords[curr_soln_pos].y;
			if (curr_soln_pos == DIM - 1)
				col++;
			curr_soln_pos++;
		}
		else
			col = 0;
		while (col < DIM)
		{
			if (queen_safe(row, col))
			{
				grid[row][col] = 1;
				num_queens++;
				create_coord(row, col);
				queen_coord_pos++;
				if (!permute_queens(grid, coords))
				{
					grid[row][col] = 0;
					num_queens--;
					queen_coord_pos--;
				}
				else
					return (1);
			}
			col++;
			if (col == DIM && num_queens != N_QUEENS)
				return (0);
		}
		if (col == DIM && num_queens != N_QUEENS)
			return (0);
		row++;
	}
	return (1);
}

int solve_queens(int **grid, int row)
{
	int col;

	if (num_queens == N_QUEENS)
		return (1);
	while (row < DIM)
	{
		col = 0;
		while (col < DIM)
		{
			if (queen_safe(row, col))
			{
				grid[row][col] = 1;
				num_queens++;
				create_coord(row, col);
				queen_coord_pos++;
				if (!solve_queens(grid, row + 1))
				{
					grid[row][col] = 0;
					num_queens--;
					queen_coord_pos--;
				}
				else
					return (1);
			}
			col++;
			if (col == DIM && num_queens != N_QUEENS)
				return (0);
		}
		row++;
	}
	return (1);
}

int queen_safe(int row, int col)
{
	int tmp;

	tmp = 0;
	while (tmp < queen_coord_pos)
	{
		if (row == queen_coords[tmp].x)
			return (0);
		else if (col == queen_coords[tmp].y)
			return (0);
		else
		{	
			if ((col - row) == (queen_coords[tmp].y - queen_coords[tmp].x))
				return (0);
			if ((row + col) == (queen_coords[tmp].x + queen_coords[tmp].y))
				return (0);
		}
		tmp++;
	}
	return (1);
}

void copy_coords(point *queen_coords, point *curr_soln_coords)
{
	int i;
	
	i = 0;
	while (i < DIM)
	{
		curr_soln_coords[i].x = queen_coords[i].x;
		curr_soln_coords[i].y = queen_coords[i].y;
		i++;
	}
}

void print_coords(point *coords)
{
	int i;
	
	i = 0;
	while (i < DIM)
	{
		printf("[%d, %d]\n", coords[i].x, coords[i].y);
		i++;
	}
}

void create_coord(int row, int col)
{
	queen_coords[queen_coord_pos].x = row;
	queen_coords[queen_coord_pos].y = col;
}

void init_grid(int **grid)
{
	int i, j;

	i = 0;
	while (i < DIM)
	{
		grid[i] = (int*)malloc(sizeof(int) * DIM);
		j = 0;
		while (j < DIM)
			grid[i][j++] = 0;
		i++;
	}
}

void render(int **grid)
{
	int i, j;

	i = 0;
	while (i < DIM)
	{
		j = 0;
		while (j < DIM)
			printf("%d%c", grid[i][j++], ' ');
		printf("%c", '\n');
		i++;
	}

}

void free_array(int **grid)
{
	int i;

	i = 0;
	while (i < DIM)
		free(grid[i++]);
	free(grid);
}
