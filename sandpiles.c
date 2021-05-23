#include <stdio.h>
#include <stdlib.h>

#define HOLDING_CAPACITY 4
#define GRID_X 7
#define GRID_Y GRID_X
// define GRID_Y with something else for non-square grids
// using odd values to ensure that there is a single "middle"
// for the sake of symmetry

const char* colors[7] = {
    "\x1b[31m",
    "\x1b[32m",
    "\x1b[33m",
    "\x1b[34m",
    "\x1b[35m",
    "\x1b[36m",
    "\x1b[37m"
};

int grid[GRID_X][GRID_Y];

/* the following function is a little opaque in why ints are
 being returned to determine the type of a cell.
 picture an XxY grid, the returns should be fairly self explanatory

		0			 6			3
		 0,0  ...	 X,0
		  .         .
		2 .    8    . 5
		  .         .
		 0,Y  ...  X,Y
		1      7      4

 is there a better way to assign cells a type and
 direction/neighbors? almost certainly, but thats for the 
 2nd draft. */

int cornerEdgeOrBody(int x, int y) {
    if (x == 0) {
      if (y == 0) {
            return 0;
        } else if (y == (GRID_Y-1)) {
            return 1;
        } else {
            return 2;
        }
    } else if (x == (GRID_X-1)) {
        if (y == 0) {
            return 3;
        } else if (y == (GRID_Y-1)) {
            return 4;
        } else {
            return 5;
        }
    } else if (y == 0) {
        return 6;
    } else if (y == (GRID_Y-1)) {
        return 7;
    } else {
        return 8;
    }
};

// a large amount of optimization can be done here,
// instead of strict switch cases, some kind of char check
// that allows me to cut down the number of cases down to 4
// for each possible neighbor. optimization will certainly
// be required as grids get larger
int topple(int *value, int x, int y) {
    if (*value >= HOLDING_CAPACITY) {
			int cellType = cornerEdgeOrBody(x, y);
			*value -= 4;
			switch(cellType) {
				case 0:
					++*(value + 1);
					++*(value + GRID_X);
				case 1:
					++*(value + 1);
					++*(value - GRID_X);
				case 2:
					++*(value + 1);
				case 3:
					++*(value - 1);
					++*(value + GRID_X);
				case 4:
					++*(value - 1);
					++*(value - GRID_X);
				case 5:
					++*(value - 1);
				case 6:
					++*(value + GRID_X);
				case 7:
					++*(value - GRID_X);
				case 8:
					++*(value - 1);
					++*(value + 1);
					++*(value - GRID_X);
					++*(value + GRID_X);
			}
			return 1;
    } else {
			return 0;
		}
};

void printGrid() {
	for (int i = 0; i < GRID_X;)
  {
      for (int j = 0; j < GRID_Y;)
      {
          int *cellPointer = &grid[i][j];
          printf("%s%d", colors[*cellPointer], *cellPointer);
          ++j;
      }
      printf("\n");
      ++i;
  }
};

int main() {
    grid[1][1] = 6;
		grid[2][1] = 3;
		grid[1][2] = 3;
		grid[3][2] = 5;
		grid[2][5] = 2;
		grid[1][3] = 3;
		grid[2][3] = 1;
		grid[6][6] = 3;
		grid[6][5] = 3;
		grid[6][4] = 3;
		grid[5][6] = 3;
		grid[5][5] = 4;
		grid[5][4] = 3;
		grid[4][6] = 3;
		grid[4][5] = 3;
		grid[4][4] = 3;
    printf("INITIAL GRID CONFIGURATION\n");
		printGrid();
		int toppleCheck = 1;
		while (toppleCheck == 1) {
			printf("\x1b[0mTOPPLING. . .\n");
			for (int i = 0; i < GRID_X;)
			{
				for (int j = 0; j < GRID_Y;)
				{
					int *cellPointer = &grid[i][j];
					toppleCheck = topple(cellPointer, i, j);
					++j;
				}
				++i;
			};
			printGrid();
		};
    printf("\x1b[0mGRID AFTER TOPPLING\n");
		printGrid();
    puts("\x1b[0m");
    return 0;
};
