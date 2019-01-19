//yasin isse 11240548 cmpt 214 assignment 3


// The Standard Headers
#include <assert.h>     // for assert()
#include <stdio.h>      // for printf(), etc.
#include <stdlib.h>     // for EXIT_SUCCESS, abs(), etc.
#include <string.h>     // for strcpy(), strlen(), etc.

// The Local Headers
#include "vehicle.h"
#include "reports.h"



void printAllVehicles() {
    int numVehicles = 0;
    
    printf("Printing all vehicles in the system:\n");
    for (int r = 0; r < MAX_VEHICLE_ROW; r++) {
        for (int c = 0; c < MAX_VEHICLE_COL; c++) {
            if (NULL != Garage[r][c]) {
                // Found a vehicle
                printf("%d. ---\n",numVehicles+1);
                printVehicle(Garage[r][c]);
                numVehicles++;
                printf("=======\n");
                
            }
        }
    }
    printf("Total number of vehicles: %d\n", numVehicles);
}





void printRefuelReport() {
    int numVehicles = 0;
    
    printf("The following vehicles have less than 50%% fuel:\n");
    for (int r = 0; r < MAX_VEHICLE_ROW; r++) {
        for (int c = 0; c < MAX_VEHICLE_COL; c++) {
            if ((NULL != Garage[r][c]) && (calcFuel(Garage[r][c]) < 50)) {
                // Found a vehicle matching criteria
                printf("-----\n");
                printVehicle(Garage[r][c]);
                printf("-----\n");
            }
        }
    }
    printf("Total number of vehicles on report: %d\n", numVehicles);
}


void printGarageMap() {
    
    printf("Printing graphical representation of parking lot:\n");
    for (int r = 0; r < MAX_VEHICLE_ROW; r++) {
        for (int c = 0; c < MAX_VEHICLE_COL; c++) {
            if (NULL != Garage[r][c]) {
                // Found a vehicle
                switch(Garage[r][c]->type) {
                   case CAR:
                      printf("C ");
                      break;
                   case TRUCK:
                      printf("T ");
                      break;
                   case SUV:
                      printf("S ");
                      break;
                   default :
                      return; // error
                }
            } else {
                // Represent a blank stall
                printf(". ");
            }
        }
        putchar('\n');
    }
    putchar('\n');
}

