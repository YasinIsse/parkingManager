//yasin isse 11240548 cmpt 214 assignment 3

// The Standard Headers
#include <assert.h>     // for assert()
#include <stdio.h>      // for printf(), etc.
#include <stdlib.h>     // for EXIT_SUCCESS, abs(), etc.
#include <string.h>     // for strcpy(), strlen(), etc.

// The Local Headers
#include "vehicle.h"



Vehicle* allocVehicle(char* model, char* plate, VType type, double curFuel, double maxFuel) {
    if ((NULL == model) || (NULL == plate)) {
        return NULL;
    }
    
    if ((curFuel < 0) || (maxFuel < 0) || (curFuel > maxFuel)) {
        return NULL;
    }
    
    // Allocate vehicle record - intialize type, fuel level, max fuel
    Vehicle* v = (Vehicle*)malloc( sizeof(Vehicle) );
    v->type = type;
    v->curFuel = curFuel;
    v->maxFuel = maxFuel;
    
    // Allocate strings for the model and plate
    v->model = (char*)malloc( sizeof(char) * (strlen(model)+1) );
    v->plate = (char*)malloc( sizeof(char) * (strlen(plate)+1) );
    
    // Copy the provided model and plate into the new vehicle record
    strcpy(v->model, model);
    strcpy(v->plate, plate);
    
    return v;
}



int deallocVehicle(Vehicle* v) {
    
    // Fail if v is NULL, no easy way to verify that the user definitely passed
    // in an address to a vehicle
    if (NULL == v) {
        return -1;
    }
    
    // Locate the vehicle's position in the garage, clear it if found
    for (int r = 0; r < MAX_VEHICLE_ROW; r++) {
        for (int c = 0; c < MAX_VEHICLE_COL; c++) {
            if (Garage[r][c] == v) {
                // Found the vehicle's position
                Garage[r][c] = NULL;
                // Allow loop to continue on the off-chance the vehicle is
                // listed in the garage multiple times
            }
        }
    }
    // Proceed with deletion even if vehicle was not found in Garage. This could
    // happen if the vehicle was allocated, but not placed in a stall
    
    // free() anything created with malloc() in allocVehicle()
    if (NULL != v->model) {
        free(v->model);
        v->model = NULL; // not strictly required
    }
    
    if (NULL != v->plate) {
        free(v->plate);
        v->plate = NULL;
    }
    
    free(v);
    
    return 0; //Success
}



int assignStall(Vehicle* v, int r, int c) {
    
    // Invalid pointer passed in
    if (NULL == v) {
        return -1; // error
    }
    
    // Stall already occupied
    if (NULL != Garage[r][c]) {
        return -1; // error
    }
    
    // New position out of bounds
    if ((r < 0) || (c < 0) || (r >= MAX_VEHICLE_ROW) || (c >= MAX_VEHICLE_COL)) {
        return -1; // error
    }
    
    // Clear vehicle's current position, if it has one
    for (int r = 0; r < MAX_VEHICLE_ROW; r++) {
        for (int c = 0; c < MAX_VEHICLE_COL; c++) {
            if (Garage[r][c] == v) {
                // Found the vehicle's position
                Garage[r][c] = NULL;
                // Allow loop to continue on the off-chance the vehicle is
                // listed in the garage multiple times
            }
        }
    }
    
    Garage[r][c] = v;
    
    return 0; // success
}



double calcFuel(Vehicle* v) {
    
    if (NULL == v) {
        return -1; // error
    }
    
    return v->curFuel / v->maxFuel * 100;
}



int refuelVehicle(Vehicle* v, double fuelAmount) {
    
    if (NULL == v) {
        return -1; // error
    }
    
    if (fuelAmount < 0) {
        return -1; // error
    }
    
    // Cannot fill the tank above capacity
    if (fuelAmount + v->curFuel > v->maxFuel) {
        v->curFuel = v->maxFuel;
    } else {
        v->curFuel += fuelAmount;
    }
    
    return 0; // success
}


void printfuel(Vehicle* v) {
    
    // Fail if an invalid vehicle pointer is entered
    if (NULL == v) {
        return;
    }
    
    printf("%s\n",v->model); 
    
    printf("\tCurrent fuel level: %.2fL out of %.2fL ",v->curFuel, v->maxFuel); 
    double fuelPerc = calcFuel(v);
    
    printf("[");
    for (int low = 0; low < 100; low += 10) {
        if (fuelPerc > low) {
            printf("▇");
        } else {
            printf("-");
        }
    }
    printf("]");
    
    printf(" (%.0f%%)\n",fuelPerc); 
}



void printVehicle(Vehicle* v) {
    
    // Fail if an invalid vehicle pointer is entered
    if (NULL == v) {
        return;
    }
    
    printf("%s\n",v->model); 
    
    printf("\tPlate: %s\n", v->plate);
    
    printf("\tType: ");
    switch(v->type) {
       case CAR:
          printf("Car\n");
          break;
       case TRUCK:
          printf("Truck\n");
          break;
       case SUV:
          printf("SUV\n");
          break;
       default :
          return; // error
    }
    
    // Locate the vehicle's position in the garage, print all occurences (should
    // only be 1)
    for (int r = 0; r < MAX_VEHICLE_ROW; r++) {
        for (int c = 0; c < MAX_VEHICLE_COL; c++) {
            if (Garage[r][c] == v) {
                // Found the vehicle's position
                printf("\tIn stall: row %d, column %d\n",r, c); 
                // Allow loop to continue on the off-chance the vehicle is
                // listed in the garage multiple times
            }
        }
    }
    
    printf("\tCurrent fuel level: %.2fL out of %.2fL ",v->curFuel, v->maxFuel); 
    double fuelPerc = calcFuel(v);
    
    printf("[");
    for (int low = 0; low < 100; low += 10) {
        if (fuelPerc > low) {
            printf("▇");
        } else {
            printf("-");
        }
    }
    printf("]");
    
    printf(" (%.0f%%)\n",fuelPerc); 
}

// Maximum number of characters per line of a file to be read in
const int MAX_READ_SIZE = 2000;


int importFromFile(char* file) {
    if (NULL == file){
        return 0;
    }
    
    // Open the file read-only and associate a stream with the file
    FILE* f = fopen(file,"r");
    
    if (NULL == f) {
        // Error opening file
        return 0;
    }
    
    // MAX_INPUT_LENGTH + 1 to account for null byte
    char inputString[MAX_READ_SIZE+1];
    int numVehicles = 0;
    
    char* token = NULL;
    char* vehicleModel = NULL;
    char* vehiclePlate = NULL;
    VType vehicleType;
    double vehicleCurFuel = 0;
    double vehicleMaxFuel = 0;
    int rPos = 0, cPos = 0;
    Vehicle *v = NULL;
    
    // Loop until a break or garage is full
    while(numVehicles < MAX_VEHICLE_COL * MAX_VEHICLE_ROW) {
        // Initialize the input buffer
        inputString[0] = '\0';
        
        if(fgets(inputString, MAX_READ_SIZE, f) == NULL) {
            // Reached end of file or error
            break;
        }
        
        // trim newline char
        if (inputString[strlen(inputString)-1] == '\n') {
            inputString[strlen(inputString)-1] = '\0';
        }
        
        // Get model name from file
        token = strtok(inputString,"|");
        vehicleModel = (char *)malloc(sizeof(char) * (strlen(token) + 1));
        strcpy(vehicleModel, token);
        
        // Get plate from file
        token = strtok(NULL,"|");
        vehiclePlate = (char *)malloc(sizeof(char) * (strlen(token) + 1));
        strcpy(vehiclePlate, token);
        
        // Get type from file
        token = strtok(NULL,"|");
        
        if (strcmp(token,"CAR") == 0) {
            vehicleType = CAR;
        } else if (strcmp(token,"TRUCK") == 0) {
            vehicleType = TRUCK;
        } else if (strcmp(token,"SUV") == 0) {
            vehicleType = SUV;
        } else {
            // Error, invalid type provided - skip to next line of file
            free(vehicleModel);
            free(vehiclePlate);
            continue;
        }
        
        // Get current/max fuel levels from file
        token = strtok(NULL,"|");
        sscanf (token,"%lf",&vehicleCurFuel);
        token = strtok(NULL,"|");
        sscanf (token,"%lf",&vehicleMaxFuel);
        
        // Validate fuel levels, make reasonable assumptions on error
        if (vehicleCurFuel < 0) {
            vehicleCurFuel = 0;
        }
        
        if (vehicleMaxFuel <= 0) {
            // Vehicle cannot have fuel capacity of 0, skip this vehicle
            free(vehicleModel);
            free(vehiclePlate);
            continue;
        }
        
        if (vehicleCurFuel > vehicleMaxFuel) {
            vehicleCurFuel = vehicleMaxFuel;
        }
        
        // Ready to allocate the vehicle
        v = allocVehicle(vehicleModel, vehiclePlate, vehicleType, 
                         vehicleCurFuel, vehicleMaxFuel);
                         
        free(vehicleModel);
        free(vehiclePlate);
        
        if (NULL == v) {
            // Seems we are out of memory, time to stop
            return numVehicles;
        }
        
        // If model or plate are still NULL, something went wrong - stop
        if (NULL == v->model || NULL == v->plate) {
            deallocVehicle(v);
            return numVehicles;
        }
        
        // Obtain desired vehicle position from file
        token = strtok(NULL,"|");
        rPos = strtol(token,NULL,10);
        token = strtok(NULL,"|");
        cPos = strtol(token,NULL,10);
        
        if (assignStall(v, rPos, cPos) != 0) {
            // Failed to assign vehicle to correct stall
            deallocVehicle(v);
            continue;
        }
        
        numVehicles++;
    }
    
    return numVehicles;
}

