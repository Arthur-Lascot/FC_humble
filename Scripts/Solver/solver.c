#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <string.h>

int grid[9][9]; 
/* =
{
	{5,3,0,0,7,0,0,0,0},
	{6,0,0,1,9,5,0,0,0},
	{0,9,8,0,0,0,0,6,0},
	{8,0,0,0,6,0,0,0,3},
	{4,0,0,8,0,3,0,0,1},
	{7,0,0,0,2,0,0,0,6},
	{0,6,0,0,0,0,2,8,0},
	{0,0,0,4,1,9,0,0,5},
	{0,0,0,0,8,0,0,7,9},
};
*/

//To print a sudoku in the console 
void print()
{
        for (int y = 0; y < 9; y++)
        {
                if (y%3 == 0)
                        printf("-------------------------------\n");
                for (int x = 0; x < 9; x++)
                {
                        if (x%3== 0)
                                printf("|");
                        int c = grid[y][x];
                        if (c == 0)
                                printf("   ");
                        else
                                printf(" %i ",grid[y][x]);
                }
                printf("|\n");
        }
        printf("-------------------------------\n");

}


//Return True (1) if the column is done
int is_column_solved(int x)
{
	for (int i = 1; i <= 9; i++)
	{
		int found = 0;
		for (int y = 0; !found && y < 9 ; y++)
		{
			if (grid[y][x] == i)
				found = 1;

		}
		if (!found)
			return 0; //False
	}	
	return 1; //True
}

//Return True (1) if the line is done
int is_line_solved(int y)
{
	for (int i = 1; i <= 9; i++)
	{
		int found = 0;
		for (int x = 0; !found && x < 9; x++)
		{
			if (grid[y][x] == i)
				found = 1;
		}
		if (!found )
			return 0; // False
	}
	return 1; // True
}

//Return True(1) if the square is done
int is_square_solved(int x, int y)
{
	x /= 3;
	y /= 3;
	for (int i = 1; i <=9;i++)
	{
		int found = 0;
		for (int Y = 0; !found && Y<3; Y++)
		{
			for (int X = 0; !found && X<3; X++)
			{
				if (grid[Y+y*3][X+x*3] == i)
					found = 1;
			}
		}
		if (!found)
			return 0; //False
	}
	return 1; // True

}

//Return True (1) if the Sudoku is done
int is_solved()
{
	for(int i = 0; i < 9; i++)
	{
		if(!is_column_solved(i)||!is_line_solved(i)||is_square_solved(i/3,i%3))
			return 0; //False
	}
	return 1; //True
}

//Return True (1) if a value is already in the X column	
int already_in_column(int x,int val)
{
	for (int y = 0; y < 9; y++)
	{
		if (grid[y][x] == val)
			return 1;
	}
	return 0;
}

//Return True(1) if a value is already in the Y column 
int already_in_line(int y,int val)
{
	for (int x = 0; x < 9 ; x++)
	{
		if (grid[y][x] == val)
			return 1; //True
	}
	return 0; //False
}

//Return True (1) if a value is already in the X,Y square
int already_in_square(int x,int y, int val)
{
	x /= 3;
	y /= 3;
	for (int Y = 0; Y < 3; Y++)
	{
		for (int X = 0; X < 3; X++)
		{
			if (grid[Y+y*3][X+x*3] == val)
				return 1; //True
		}
	}
	return 0; //False
}

//Check if the column is not wrong
int valid_column(int x,int val)
{
    int count = 0;
    for (int y = 0; y < 9; y++)
	{
		if (grid[y][x] == val)
	    {
            count++;
        }
        if (count >= 2)
        {
            return 0; //Not valid
        }
	}
	return 1; //Valid
}

//Check if the line is not wrong
int valid_line(int y, int val)
{
    int count = 0;
    for (int x = 0; x < 9 ; x++)
	{
		if (grid[y][x] == val)
		    count++;
        if (count >= 2)
            return 0; //Not valid
	}
	return 1; //Valid

}

//Check if the square is not wrong
int valid_square(int x,int y,int val)
{
	x /= 3;
	y /= 3;
	int count = 0;
    for (int Y = 0; Y < 3; Y++)
	{
		for (int X = 0; X < 3; X++)
		{
			if (grid[Y+y*3][X+x*3] == val)
				count++;
            if (count >= 2)
                return 0; //Not valid
		}
	}
	return 1; //Valid

}

//Solve by a recursion the Sudoku
int solve_rec(int x, int y)
{
	if (y>=9)
		return 1;

	int nextX = x + 1;
	int nextY = y;
	
	if (nextX >= 9)
	{
		nextX = 0;
		nextY++;
	}

	if (grid[y][x] != 0)
		return solve_rec(nextX,nextY);

	for (int i = 1; i <= 9; i++)
	{
		int al_in_c = already_in_column(x,i);
		//printf("already in column %i %i => %i \n",x,i,al_in_c);

		int al_in_l = already_in_line(y,i);
		//printf("already in line %i %i => %i \n",y,i,al_in_l);

		int al_in_s = already_in_square(x,y,i);
		//printf("already in square(y = %i,x = %i) %i => %i \n",y,x,i,al_in_s);

		//printf("\n");
		if (!al_in_c && !al_in_l && !al_in_s)
		{
			grid[y][x] = i;
			if (solve_rec(nextX,nextY))
				return 1; //True
			grid[y][x] = 0;
		}
	}
	return 0;
}

void solve()
{
	solve_rec(0,0);
}

int valid_sudoku()
{
    for (int x = 0; x < 9 ; x++)
    {
        //printf("Line / Column : %i\n",x);
        for (int i = 1 ; i <= 9 ; i++)
        {

            //printf(" -- Number %i\n",i);
            int val_c = valid_column(x,i);
            if (!val_c)
                return 0;
            
            int val_l = valid_line(x,i);
            if (!val_l)
                return 0; 

            if( x % 3 == 0) //New square
            {
                int y = x;
                
                int val_s = valid_square(x,y,i);
                if(!val_s)
                   return 0;

                for (int j = 0 ; j < y ; j++)
                {
                    val_s = valid_square(x,j,i);
                    if (!val_s)
                        return 0;
                    val_s = valid_square(j,x,i);
                    if (!val_s)
                        return 0;
                }
            }
        }
    }
    return 1;
}


//Read the file with a grid
void read_sudo(FILE *gridtxt)
{
	int ch;
	int y = 0;
	int x = 0;
    while ((ch = fgetc(gridtxt)) != EOF) //EOF = End Of a File
    {
                //printf("char = %d \n",ch);
		
		//Grid too large
		if (y >= 9 && x >= 1)
			errx(1,"Error : The grid is too large");	
		
		
		if (ch >= 48 && ch <= 57)
		{
			grid[y][x] = ch - 48;
			x++;
		}
		else if (ch == 46)
		{
			grid[y][x] = 0;
			x++;
		}
		
		//Check the size of the line
		else if (ch == 10 && x != 0)
			errx(1,"Error : Line %i is not valid",y);
		
		//Invalid character
		else if (ch != 32 && ch != 10)
			errx(1,"Error :  The grid contains an invalid character");


		if (x == 9)
		{
			y++;
			x = 0;
		}
		
    }

	//Grid too small
	if (y != 9)
		errx(1,"Error : The grid is too small");

	//!\ IMPORTANT 
	fclose(gridtxt);
}

//Write a file with the result
void write_sudo(FILE *gridres)
{
	for (int y = 0; y < 9 ; y++)
	{
		if (y%3 == 0 && y != 0)
			fputs("\n",gridres);

		for (int x = 0; x < 9 ; x++)
		{
			if (x%3 ==0 && x!=0)
				fputs(" ",gridres);
			char c = grid[y][x] + '0';
			fputc(c,gridres);
		}
		fputs("\n",gridres);
	}
	
	fclose(gridres);
}

//Function to concat a string
char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); 
    // +1 for the null-terminator
    
    if(result==NULL)                     
    {
        errx(1,"Error : Memory not allocated");
    }
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

//Main function 
int solveMain(char * path)
{
	FILE *gridtxt = fopen(path,"r");
	if (gridtxt == NULL)
		errx(1,"Error : Could not open file %s",path);

	read_sudo(gridtxt);
    
    
    if (!valid_sudoku())
    {
        return 404;
    }

	solve();

	char *fileres = concat(path,".result");
	FILE *gridres = fopen(fileres,"w");
	if (gridres == NULL)
		errx(1,"Error : Could not write the result file");

	write_sudo(gridres);
	free(fileres);
	
    //print();

    return EXIT_SUCCESS;
}
