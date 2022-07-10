#ifndef sandpiles
#define sandpiles
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/* n x m grid composed of cells that hold up to A "grains," where
   A is \geq 4, then said cell "topples" into nearby cells,
   with each cell recieving floor(S/4) where S is the number of
   grains in said cell, then the number of grains remaining in the
   cell is S - floor(S/4).
   example grid:
   [0] [0] . . . . [0]
   [0]   .
    .      .
    .        .
    .          .
    .            .
   [0]             [0] */

/* DISREGARD *********************************************************
 * how best to represent this? a linked list? sure, cant think of any
   more efficient data structure to implement this, as a standard
   multidimensional array will have similar complexity (i believe).
   a singly linked list will accomplish my main objective of being
   able to output the final grid as an image or .bin file or whatever,
   but ill have to see whether this is sufficient to store each
   iteration and output a gif/set of images, as doing a single pass
   might have some parts of the grid mid collapse/change/etc.
   DISREGARD ********************************************************/
// just stick to multidimensional int arrays

/* BEGIN FUNCTION PROTOTYPES ****************************************/
// initializes grid and returns the first pile
int **initSilo(int rows, int cols);

// frees the memory blocs allocated for said silo
void freeSilo(int **silo, int rows, int cols);

// scans through silo to see if any piles are at topple threshold
// returns an array with the index of each pile to topple, with index
// given as (row)*(COLS) + col, where COLS is m of n x m rather than
// the column of incidence, and the very first element is the num
// of piles to topple
int *indicesOfToTopple(int **silo, int rows, int cols, int pileMax);

// prints out the silo to console in a pretty gridded format
void printSilo(int **silo, int rows, int cols);

// prints out the addresses of the silo to console, should print 
// out (rows + 1) addresses, 1 for the double int pointer holding
// the (rows) int pointers
void printSiloInfo(int **silo, int rows, int cols);

// prints indices of piles to be toppled, if any
void printIndices(int **silo, int rows, int cols, int *indices);

// topples silo according to a pileMax, given an array populated w/ indices
// of piles to topple within said silo
void toppleSilo(int **silo, int rows, int cols, int *indices, int pileMax);

// returns whether a given index has neighbors with 4 bits (essentially)
// cells to the NESW? 0000 to 1111. requires the # of rows, cols.
int pileNeighbors(int index, int rows, int cols);
/* END FUNCTION PROTOTYPES ******************************************/

/* BEGIN FUNCTION DEFINITIONS ***************************************/
int **initSilo(int rows, int cols){
    int **silo=malloc(sizeof(int*)*rows);
    int *temp=NULL;
    for (int i=0; i<rows; i++){
        *(silo+i)=malloc(sizeof(int)*cols);
        for (int j=0; j<cols; j++){
            // below is expanded just to make visually parsing
            // it slightly easier
            *( *(silo+i) + j) = 0; 
        }
    }
    return silo;
}

void freeSilo(int **silo, int rows, int cols){
    for (int i=0; i<rows; i++){
        free(*(silo+i));
    }
    free(silo);
}

int *indicesOfToTopple(int **silo, int rows, int cols, int pileMax){
    int *indices=malloc(sizeof(int));
    indices[0]=0;
    int value=0;
    int numIndices=0;
    for (int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            value = *( *(silo+i) + j);
            if (value >= pileMax){
                numIndices++;
                indices=realloc(indices, sizeof(int)*(1 + numIndices));
                indices[numIndices]=(i*cols)+j;
                indices[0]=numIndices;
            }
        }
    }
    return indices;
}
// debug function definitions
void printSilo(int **silo, int rows, int cols){
    for (int i=0; i<rows; i++){
        for (int j=0; j<cols; j++){
            printf("[%-2i] ", *( *(silo+i) + j) ); 
        }
        printf("\n");
    }
}
void printSiloInfo(int **silo, int rows, int cols){
    printf("silo address:%li\n", silo);
    for (int i=0; i<rows; i++){
        printf("row_%i address:%li\n", i, *(silo+i));
    }
}

// FIX THIS SEE pileNeighbors comment
void printIndices(int **silo, int rows, int cols, int *indices){
    int bound=indices[0];
    int index=0;
    if (bound == 0){
        printf("no piles to topple. . .\n");
    } else {
        printf("indices to be toppled w/ value\n");
        for (int i=0; i<bound; i++){ // TO FINISH
            index = indices[i+1];
            pileNeighbors(index, rows, cols);
        }
    }
}

void toppleSilo(int **silo, int rows, int cols, int *indices, int pileMax){
    int numToTopple=indices[0];
    /* method: take a given index and convert into 2-component index
       using (rows) and (cols). use (rows) and (cols) to determine whether
       given pile will topple into a sink (off the grid) or into a
       cell, updating said cell if the latter. */ 
    for (int i=0; i<numToTopple; i++){
        // to finish
    }
}

// FIX THIS just return a 2 element array instead of an int
// to skip all this index to component nonsense
int pileNeighbors(int index, int rows, int cols){
    // first, turn index into row and col components.
    int neighbors = 0;
    int ind_row=0;
    int ind_col=0;
    int i=0;
    int hold=index;
    while ( hold > 0 ){
        hold -= i*(cols);
        if (hold == 0){
            ind_row = i;
            ind_col = 0;
        } else if (hold < 0){
            ind_row = i + 1;
            ind_col = hold + cols;
        } else {
            i++;
        }
    }
    // then, store whether or not there are neighbors
    // in cardinal directions NESW as 4 bits, for 
    // NESW respectively (0000/0 to 1111/15)
    if (ind_row - 1 >= 0){
        neighbors =+ 8; // add 0b1000
    }
    if (ind_col + 1 <= cols){
        neighbors =+ 4; // add 0b0100
    }
    if (ind_row + 1 <= rows){
        neighbors =+ 2; // add 0b0010
    }
    if (ind_col - 1 >= 0){
        neighbors =+ 1; // add 0b0001
    }
    printf("neighbors of (%i, %i):%i\n", ind_row, ind_col, neighbors);
    return neighbors;
}
#endif
