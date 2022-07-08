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
// 1. initializes grid and returns the first pile
int **initSilo(int rows, int cols);
// 2. frees the memory blocs allocated for said silo
void freeSilo(int **silo, int rows, int cols);

// 3. scans through silo to see if any piles are at topple threshold
// returns an array with the index of each pile to topple, with index
// given as (row)*(COLS) + col, where COLS is m of n x m rather than
// the column of incidence
int *scanSilo(int **silo, int rows, int cols, int pileMax);

// debug function prototypes
// 4. prints out the silo to console in a pretty gridded format
void printSilo(int **silo, int rows, int cols);
// 5. prints out the addresses of the silo to console, should print 
// out (rows + 1) addresses, 1 for the double int pointer holding
// the (rows) int pointers
void printSiloInfo(int **silo, int rows, int cols);

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

int *scanSilo(int **silo, int rows, int cols, int pileMax){
    int *indices=malloc(sizeof(int));
    indices[0]=0;
    int value=0;
    int numIndices=0;
    for (int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            value = *( *(silo+i) + j);
            if (value >= pileMax){
                printf("toTopple (%i) found at %i\n", value, (i*cols)+j);
                numIndices++;
                printf("numIndices (%i)\n", numIndices);
                indices=realloc(indices, sizeof(int)*(1 + numIndices));
                indices[numIndices]=(i*cols)+j;
                indices[0]=numIndices;
            }
        }
    }
    printf("numIndices (%i)\n", indices[0]);
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
#endif
