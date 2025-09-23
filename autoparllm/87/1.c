//***************************************************************************************//
// Game of Life - Serial, OpenMP Implementation in C
// Nikos Lazaridis, M1485
// University of Athens (UoA), Department of Informatics (DIT),
// Parallel Computing Systems semester project
//***************************************************************************************//
//////////////////////////////////////////////////////////////////
//////////////////////////// Includes ////////////////////////////
#include <omp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#ifdef _OPENMP
#include "omp.h"
#endif
#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h> // for Sleep()
#define clock
#define sleep Sleep
// Measure wall-clock time elapsed
#elif defined(__unix__) || defined(__linux__)
#include <unistd.h> // for usleep()
#define sleep(ms) usleep(ms * 1000)
#define BILLION 1e9 // 1e9 = 1000000000.0
static struct timespec begin;
static struct timespec finish;

void startTiming() { clock_gettime(1, &begin); }
// Measure wall-clock time elapsed

double getWallTime() {
    clock_gettime(1, &finish);
    // secs
    return (finish.tv_sec - begin.tv_sec) +
           (finish.tv_nsec - begin.tv_nsec) / 1e9;
    // nanos
}
#endif
//////////////////////////////////////////////////////////////////
//////////////////////////// Globals ////////////////////////////
// default values
static int rows = 24;
static int columns = 36;
static _Bool periodic = 1;
static int timeStep = 500;
// timeStep for the simulation (in ms)
//////////////////////////////////////////////////////////////////
///////////////////// Function Declarations //////////////////////
#ifdef DISPLAY_RESULTS
#define updateScreen() printf("\033[H")
#endif
#if defined(_DEBUG) || defined(DEBUG)
#endif
void copyGhostCells(char **grid);
int countNeighbors(char **grid, int y, int x);
void playGame(int ngenerations, double density);
char **createGameGrid(double density);

void help() {
    printf("Call like so:\n./[programName] [rows] [columns] [ngenerations] "
           "[density] [periodic]\n\n");
}

char **allocContiguous2dArr(char *gridData) {
    gridData = ((char *)(malloc((rows * columns) * sizeof(char))));
    char **grid = (char **)(malloc(rows * sizeof(char *)));
    int i;
    dummyMethod3();

#pragma omp parallel for private(i) firstprivate(rows, columns)
    // #pragma rose_outline
    for (i = 0; i <= rows - 1; i += 1) {
        grid[i] = &gridData[i * columns];
    }
    dummyMethod4();
    return grid;
}

void deallocContiguous2dArr(char **grid, char *gridData) {
    free(gridData);
    free(grid);
}

int main(int argc, char *argv[]) {
    int ngenerations = 1000;
    double density = 0.25;
    _Bool pause = 0;
    printf("\n");
    // weird segfault occurs if i don't add that
    if (argc < 5) {
        help();
        pause = 1;
    }
    // process command line arguments //
    if (argc < 2)
        printf("Row count muct be greater than zero. Setting to 24\n");
    else
        rows = atoi(argv[1]);
    if (argc < 3)
        printf("Column count must be greater than zero. Setting to 36\n");
    else
        columns = atoi(argv[2]);
    if (argc < 4)
        printf("Setting ngenerations to 1000\n");
    else
        ngenerations = atoi(argv[3]);
    if (argc < 5)
        printf("Setting density to 0.25\n");
    else
        density = ((double)(atof(argv[4])));
    if (argc < 6)
        printf("Periodic grid\n");
    else
        periodic = (atoi(argv[5]));
    if (pause)
        usleep((4000 * 1000));
#ifdef DISPLAY_RESULTS
#endif
    // Adding two ghost rows and columns to cover the edges
    rows += 2;
    columns += 2;
    playGame(ngenerations, density);
}
///////////////////////////////////////////////////////////////////////////////
#ifdef DISPLAY_RESULTS
// place cursor to Home position (top left)
// clear / flush specified buffer before the next operation
#endif
#if defined(_DEBUG) || defined(DEBUG)
#endif
// counts alive cells in the Moore neighborhoud of the central cell in the grid
// central cell position = pivot

int countNeighbors(char **grid, int y, int x) {
    int aliveNeighbors = 0;
    // int pivot = y * columns + x;
    char c;
    /*
            . . . . .
            . X X X .
            . X X X .
            . X X X .
            . . . . .
            */
    dummyMethod3();

    for (int i = -1; i <= 1; i += 1) {

#pragma omp parallel for private(c) reduction(+ : aliveNeighbors)
        // #pragma rose_outline
        for (int j = -1; j <= 1; j += 1) {
            c = grid[y + i][x + j];
            if (c == '#')
                aliveNeighbors++;
        }
    }
    dummyMethod4();
    // we don't want to include the current cell in the count
    if (grid[y][x] == '#')
        aliveNeighbors--;
    if (aliveNeighbors > 8) {
        puts("Alive neighbors are more than 8. - Impossible!\n");
        exit(2);
    }
    return aliveNeighbors;
}
// process grid for the next generation according to the rules of the game

char **evolve(char **grid) {
    char *newGridData = ((void *)0);
    char **newGrid = allocContiguous2dArr(newGridData);
    // local array for next gen
    ;
    int nliving;
    char cell;
    char *newCell;
    // skipping the first and last rows (y) and columns (x) of the grid
    dummyMethod3();
    for (int y = 1; y <= rows - 1 - 1; y += 1) {
        for (int x = 1; x <= columns - 1 - 1; x += 1) {
            // determine alive neighbours of cell
            cell = grid[y][x];
            nliving = countNeighbors(grid, y, x);
            // determine the state of the cell in the new grid
            newCell = &newGrid[y][x];
            if (nliving == 3 || nliving == 2 && cell == '#')
                *newCell = '#';
            else
                *newCell = '.';
        }
    }
    // O(rows * columns) // O(rows * columns)
    dummyMethod4();
    if (periodic)
        copyGhostCells(newGrid);
    return newGrid;
}

void playGame(int ngenerations, double density) {
    unsigned int turn = 0;
    char *gridData = ((void *)0);
    // needed to create contiguous 2d array
    char **grid = allocContiguous2dArr(gridData);
    // local array
    char **newGrid = ((void *)0);
    srand((time(0)));
    ;
    dummyMethod3();
    for (int y = 1; y <= rows - 1 - 1; y += 1) {
        for (int x = 1; x <= columns - 1 - 1; x += 1) {
            if (((double)(rand())) / 2147483647 <= density)
                grid[y][x] = '#';
            else
                // alive organism
                grid[y][x] = '.';
            // empty cell
        }
    }
    dummyMethod4();
    if (periodic)
        copyGhostCells(grid);
    startTiming();
    // main game loop
    while (turn < ngenerations) {
#ifdef DISPLAY_RESULTS
#endif
        newGrid = evolve(grid);
        deallocContiguous2dArr(grid, gridData);
        grid = newGrid;
        // now pointing to the newly created grid
        turn++;
    }
    double wallTime = getWallTime();
    printf("\nSimulation ended @gen #%d.\n", turn);
    printf("Elaped time: %fs\n", wallTime);
#if defined(_DEBUG) || defined(DEBUG)
// write last grid state to a file
#endif
}
// if the array is periodic copy the following:
// 	Top real row -> bottom ghost row
// 	Bottom real row -> top ghost row
// 	Left-most real column -> right ghost column
// 	Right-most real column -> left ghost column
// 	Copy 4 grid corners in opposite side corners

void copyGhostCells(char **grid) {
    dummyMethod1();

#pragma omp parallel for
    // #pragma rose_outline
    for (int y = 1; y <= rows - 1 - 1; y += 1) {
        grid[y][0] = grid[y][columns - 2];
        // left side = right side
        grid[y][columns - 1] = grid[y][1];
        // right side = left
    }
    dummyMethod2();
    dummyMethod1();

#pragma omp parallel for
    // #pragma rose_outline
    for (int x = 1; x <= columns - 1 - 1; x += 1) {
        grid[0][x] = grid[rows - 2][x];
        // top row = bottom row
        grid[rows - 1][x] = grid[1][x];
        // bottom row = top row
    }
    dummyMethod2();
    // copy corners
    grid[0][0] = grid[rows - 2][columns - 2];
    // upper left = lower right
    grid[0][columns - 1] = grid[rows - 2][1];
    // upper right = lower left
    grid[rows - 1][0] = grid[1][columns - 2];
    // lower left = upper right
    grid[rows - 1][columns - 1] = grid[1][1];
    // lower right = upper left
}

int dummyMethod1() { return 0; }

int dummyMethod2() { return 0; }

int dummyMethod3() { return 0; }

int dummyMethod4() { return 0; }
