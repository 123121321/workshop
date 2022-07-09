// DEPRECIATED. LEFT FOR ARCHIVAL PURPOSES
#include <stdio.h>
#include <stdlib.h>

#define HOLDING_CAPACITY 4
#define GRID_HEIGHT 21
#define GRID_WIDTH GRID_HEIGHT
// define GRID_WIDTH with something else for non-square grids
// using odd values to ensure that there is a single "middle"
// for the sake of symmetry

// initiliaze array that will hold cell values.

int grid[GRID_HEIGHT][GRID_WIDTH];

const char* colors[4] = {
  "\x1b[1;37m",
  "\x1b[1;34m",
  "\x1b[1;93m",
  "\x1b[1;31m"
};

/* the following function is a little opaque in why ints are
 being returned to determine the type of a cell.
 picture an XxY grid, the returns should be fairly self explanatory

    0      2      1
     0,0  ...  0,Y
      .         .
    6 .    8    . 7
      .         .
     X,0  ...  X,Y
    3      5      4

 is there a better way to assign cells a type and
 direction/neighbors? almost certainly, but thats for the 
 2nd draft. */

int cornerEdgeOrBody(int x, int y) {
    if (x == 0) {
      if (y == 0) {
            return 0;
        } else if (y == (GRID_WIDTH-1)) {
            return 1;
        } else {
            return 2;
        }
    } else if (x == (GRID_HEIGHT-1)) {
        if (y == 0) {
            return 3;
        } else if (y == (GRID_WIDTH-1)) {
            return 4;
        } else {
            return 5;
        }
    } else if (y == 0) {
        return 6;
    } else if (y == (GRID_WIDTH-1)) {
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
      int cellValue = *value;
      int spillover = cellValue/4;
      *value -= (4 * spillover);
      switch(cellType) {
        case 0:
          *(value + 1) += spillover;
          *(value + GRID_WIDTH) += spillover;
          break;
        case 1:
          *(value - 1) += spillover;
          *(value + GRID_WIDTH) += spillover;
          break;
        case 2:
          *(value + 1) += spillover;
          *(value - 1) += spillover;
          *(value + GRID_WIDTH) += spillover;
          break;
        case 3:
          *(value + 1);
          *(value - GRID_WIDTH) += spillover;
          break;
        case 4:
          *(value - 1) += spillover;
          *(value - GRID_WIDTH) += spillover;
          break;
        case 5:
          *(value - 1) += spillover;
          *(value + 1) += spillover;
          *(value - GRID_WIDTH) += spillover;
          break;
        case 6:
          *(value + GRID_WIDTH) += spillover;
          *(value + 1) += spillover;
          *(value - GRID_WIDTH) += spillover;
          break;
        case 7:
          *(value - GRID_WIDTH) += spillover;
          *(value + GRID_WIDTH) += spillover;
          *(value - 1) += spillover;
          break;
        case 8:
          *(value - 1) += spillover;
          *(value + 1) += spillover;
          *(value - GRID_WIDTH) += spillover;
          *(value + GRID_WIDTH) += spillover;
      }
      return 0;
    } else {
      return 1;
    }
};

void printGrid() {
  for (int i = 0; i < GRID_HEIGHT;)
  {
      for (int j = 0; j < GRID_WIDTH;)
      {
          int *pCell = &grid[i][j];
          printf("%s%d  ", colors[*pCell%4], *pCell);
          ++j;
      }
      printf("\n");
      ++i;
  }
};

void printCell() {
  for (int i = 0; i < GRID_HEIGHT;)
  {
    for (int j = 0; j < GRID_WIDTH;)
    {
      int *pCell = &grid[i][j];
      int cellType = cornerEdgeOrBody(i, j);
      printf("cell at %d,%d is %d, value: %d\n", i, j, cellType, *pCell);
      ++j;
    }
    ++i;
  }
};

int main() {
  grid[GRID_HEIGHT/2][GRID_WIDTH/2]=(GRID_HEIGHT * GRID_WIDTH * 2);
  printf("INITIAL GRID CONFIGURATION\n");
  printGrid();
  int toppleCheck = 0;
  while (toppleCheck < (GRID_WIDTH * GRID_HEIGHT)) {
    toppleCheck = 0;
    printf("\x1b[0mTOPPLING. . .\n");
    for (int i = 0; i < GRID_HEIGHT;)
    {
      for (int j = 0; j < GRID_WIDTH;)
      {
        int *pCell = &grid[i][j];
        toppleCheck += topple(pCell, i, j);
        ++j;
      }
      ++i;

    };
    printGrid();
    if (toppleCheck == (GRID_WIDTH * GRID_HEIGHT)) {
      break;
    }
  };
  puts("\x1b[0m");
  return 0;
};
