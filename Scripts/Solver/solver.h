#ifndef SOLVER_H
#define SOLVER_H

void print();
int is_column_solved(int x);
int is_line_solved(int y);
int is_square_solved(int x, int y);
int is_solved();
int already_in_column(int x,int val);
int already_in_line(int y,int val);
int already_in_square(int x,int y, int val);
int valid_column(int x,int val);
int valid_line(int y, int val);
int valid_square(int x,int y,int val);
int solve_rec(int x, int y);
void solve();
int valid_sudoku();
void read(FILE *gridtxt);
void write(FILE *gridres);
char* concatF(const char *s1, const char *s2);
int solveMain(char * path);

#endif

