#include <stdio.h>
#include "sandpiles.h"

#define ROWS 3
#define COLS 3
int main(){
    int **silo= initSilo(ROWS, COLS); 
    silo[1][1]=4;
    printf("test:%i\n", silo[1][1]);
    // printSiloInfo(silo, ROWS, COLS);
    printSilo(silo, ROWS, COLS);
    freeSilo(silo, ROWS, COLS);
    return 0;
}
