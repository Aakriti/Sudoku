#include<stdio.h>
#include<stdlib.h>

#define true 1
#define false 0

int resolved_cells;
int recursion_count;
int grid[9][9];
int choice[9][9][9];

void init();
void input();
void file_input();
void display();
void first_pass();
void row_column_clear(int i, int j);
void sub_grid_clear(int i, int j);
int update_cell(int i, int j);
void update_grid();
void eliminate_row(int i, int j);
void eliminate_col(int i, int j);
void eliminate_subgrid(int i, int j);
int eliminate();

int main()
{
  init();
  file_input();
  printf("\nSudoku Puzzle:\n");
  display();
  first_pass();
}

void init()
{
  int i, j, k;
  resolved_cells = 0;
  recursion_count = 0;
  for(i=0; i<9; i++)
  {
    for(j=0; j<9; j++)
    {
      for(k=0; k<9; k++)
        choice[i][j][k] = true;
    }
  }
}

void eliminate_row(int i, int val)
{
  int flag = false, k, index;
  for(k=0; k<9; k++)
  {
    if(grid[i][k] == val+1)
      return;

    if(grid[i][k] == 0)
    {
      if(choice[i][k][val] == true)
      {
        if(flag == true)
          return;
        flag = true;
        index = k;
      }
    }
  }
  grid[i][index] = val+1;
  resolved_cells++;
  sub_grid_clear(i,index);
  row_column_clear(i,index);
}

void eliminate_col(int i, int val)
{
  int flag = false, k, index;
  for(k=0; k<9; k++)
  {
    if(grid[k][i] == val+1)
      return;

    if(grid[k][i] == 0)
    {
      if(choice[k][i][val] == true)
      {
        if(flag == true)
          return;
        flag = true;
        index = k;
      }
    }
  }
  grid[index][i] = val+1;
  resolved_cells++;
  sub_grid_clear(index,i);
  row_column_clear(index,i); 
}

void eliminate_subgrid(int i, int j)
{
  return;
}

int eliminate()
{
  int i, j, change = resolved_cells;
  for(i=0; i<9; i++)
  {
    for(j=0; j<9; j++)
    {
       eliminate_row(i,j);
       eliminate_col(i,j);
       eliminate_subgrid(i,j);
    }
  }
  change = resolved_cells - change;
  if(change > 0)
    return true;
  return false;
}

int update_cell(int i, int j)
{
  int k, flag = false, value;
  for(k=0; k< 9; k++)
  {
    if(choice[i][j][k] == true)
    {
      if(flag == true)
        return false;
      flag = true;
      value = k + 1;
    }
  }
  grid[i][j] = value;
  sub_grid_clear(i,j);
  row_column_clear(i,j);
  resolved_cells++;
  return true;
}

void update_grid()
{
  int i, j;
  int count = 0;
  recursion_count++;
  for(i=0; i<9; i++)
  {
    for(j=0;j<9;j++)
    {
      if(grid[i][j] == 0)
      {
        count += update_cell(i,j);
      }
    }
  }

  if(count > 0)
    update_grid();

  else
  {
    if(resolved_cells == 81)
    {
      printf("\nSolution:\n");
      display();
    }
    else
    {
      if(eliminate())
        update_grid();
      else
      {
        display();
        printf("\nAfter %d recursive steps cells resolved: %d.\n\n", recursion_count, resolved_cells);
      }
    }
  }
}

void sub_grid_clear(int i, int j)
{
  int grid_i, grid_j, value;
  value = grid[i][j] - 1;

  if(i < 3)
    grid_i = 0;
  else if(i < 6)
    grid_i = 3;
  else
    grid_i = 6;

  if(j < 3)
    grid_j = 0;
  else if(j < 6)
    grid_j = 3;
  else
    grid_j = 6;

  for(i=grid_i; i< grid_i+3; i++)
    for(j=grid_j; j< grid_j+3; j++)
    {
      choice[i][j][value] = false;
    }
}

void row_column_clear(int i, int j)
{
  int k, value = grid[i][j] - 1;
  for(k=0; k<9; k++)
  {
    choice[i][k][value] = false;
    choice[k][j][value] = false;
  }
}

void first_pass()
{
  int i,j,k;
  for(i=0; i<9; i++)
  {
    for(j=0; j<9; j++)
    {
      if(grid[i][j] != 0)
      {
         sub_grid_clear(i,j);
         row_column_clear(i,j);        
      }
    }
  }
  update_grid();
}

void file_input()
{
  int i, j;
  FILE *f;
  f = fopen("puzzle_1.txt","r");
  for(i=0;i<9;i++)
    for(j=0;j<9;j++)
    {
      fscanf(f,"%d ",&grid[i][j]);
      if(grid[i][j] != 0)
        resolved_cells++;
    }
}

void display()
{
  int i, j;
  printf("\n- - - - - - -   - - - - - - -   - - - - - - -\n");
  for(i=0; i<9; i++)
  {
    printf("| ");
    for(j=0;j<9;j++)
    {
       if(grid[i][j] > 0)
         printf("%d | ", grid[i][j]);
       else
         printf("* | ");

       if(j == 2 || j == 5)
         printf("  | ");
    }
    printf("\n- - - - - - -   - - - - - - -   - - - - - - -\n");
    if(i == 2 || i == 5)
      printf("\n- - - - - - -   - - - - - - -   - - - - - - -\n");
    
  }
}
