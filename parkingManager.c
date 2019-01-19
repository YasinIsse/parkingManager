/*
File: parkingManager.c
Description: Sample solution to CMPT 214 A2 by David Kreiser
Author: Yasin Isse for CMPT214 Assignment 3
Student Number: 11240548
NSID: yai472
June 22, 2018
*/

// The Standard Headers
#include <assert.h>     // for assert()
#include <stdio.h>      // for printf(), etc.
#include <stdlib.h>     // for EXIT_SUCCESS, abs(), etc.
#include <string.h>     // for strcpy(), strlen(), etc.

// The Local Headers
#include "vehicle.h"
#include "reports.h"

// Snips the newline character from a string
//   In: str must not be NULL
//
//   Out: \n character removed from the string if it was present
void snipNewline(char* str) {
    if (NULL == str) {
        return;
    }
    
    if (str[strlen(str)-1] == '\n') {
        str[strlen(str)-1] = '\0';
    }
}

// Maximum length of input accepted on standard input
int MAX_INPUT_LENGTH = 50;

// main:
//  Runs the interface for the parkingManager system.
// In:
//   user inputs and test_file.txt
// Out:
//   return -- EXIT_SUCCESS on success, otherwise EXIT_FAILURE
//   Will repeat options until an incorrect entry is entered.
int main() 
{

// MAX_INPUT_LENGTH + 1 to account for null byte
char inputString[MAX_INPUT_LENGTH+1];

printf("==========Welcome to Parking Manager Interface=================\n") ;
printf("===============================================================\n") ;
printf("=======================By: Yasin Isse==========================\n") ;
printf("\n");
printf("\tPlease Enter the number to select an operation:\n") ;
printf("\n");
printf ( "Enter 1:  To add an individual vehicle\n" ) ;
printf ( "Enter 2:  To remove an individual vehicle\n" ) ;
printf ( "Enter 3:  To assign an individual vehicle a parking stall\n" ) ;
printf ( "Enter 4:  To print out all information for a specific vehicle.\n" ) ;
printf ( "Enter 5:  To print out all vehicles info in parking garage\n" ) ;
printf ( "Enter 6:  To retrieve the fuel level of a vehicle\n" ) ;
printf ( "Enter 7:  To update the fuel level of a vehicle\n" ) ;
printf ( "Enter 8:  To print a visual representation of the parking garage\n" ) ;	
printf ( "Enter 9:  To print a refueling report i.e.\n" ) ;
printf ( "Enter 10: To import multiple vehicles from a file\n" ) ;
printf ( "Enter 11:  Exit\n" ) ;
printf("\tPlease Enter now:\n");

    while (1)
    {
        printf("Parking Manager> ");
        // Initialize the input buffer
        inputString[0] = '\0';
        
        
        // Obtain input from standard input
        if(fgets(inputString, MAX_INPUT_LENGTH, stdin) == NULL) 
            {
                fprintf(stderr, 
                        "Error: fgets failed to grab input. Terminated program.");
                exit(EXIT_FAILURE);
            }
    
        // Snip the newline character from the input received
        snipNewline(inputString);
        
         // allocVehicle a Vehicle
        if (strcmp(inputString, "1") == 0) 
        {   
             // Initialize
            char vehicleModel[100], vehiclePlate[100];
            VType vehicleType;
            char v_type[100];
            float vehicleCurFuel = 0;
            float vehicleMaxFuel = 0;
            int rPos = 0, cPos = 0;
	        
            printf ( "Operation: Add an individual vehicle\n" ) ;
            printf ( "What is the model of the Vehicle (keep it short):\n" ) ;
            fgets(vehicleModel, MAX_INPUT_LENGTH, stdin);
            
            printf ( "What is the plate# of the Vehicle (keep it short):\n" ) ;
            scanf("%s", vehiclePlate);
            
            printf ( "What Vehicle type (CAR, SUV, TRUCK):?\n" ) ;
            scanf("%s", v_type);
            if (strcmp(v_type,"CAR") == 0) 
            {
            vehicleType = CAR;
            } 
            else if (strcmp(v_type,"TRUCK") == 0) 
            {
            vehicleType = TRUCK;
            }
            else if (strcmp(v_type,"SUV") == 0) 
            {
            vehicleType = SUV;
            }  
            else 
            {
            // Error, exit program.
            printf ( "Incorrect vehcile type added. EXITING PROGRAM.\n" ) ; 
            exit(EXIT_FAILURE);
            }
            
            printf ( "What is the vehicle fuel current level (enter double):\n" ) ; 
            scanf("%f", &vehicleCurFuel);
            
            printf ( "What is the vehicle fuel maximum level (enter a double):\n" ) ; 
            scanf("%f", &vehicleMaxFuel);
            
            printf ( "What is the vehicle row position (enter a integer)>\n");
            scanf("%d", &rPos);
            printf ( "What is the vehicle column position (enter a integer)>\n");
            scanf("%d", &cPos);
            
            // Stall given is availible for entry.
            if (Garage[rPos][cPos] == NULL) 
            {
                // place vehicle in stall with inputs from user.
                assignStall(allocVehicle(vehicleModel, vehiclePlate, 
                            vehicleType, vehicleCurFuel, vehicleMaxFuel), rPos, cPos);
                // confirmation signal for user.
                printf ( "Vehicle added.\n");
            }
            // Unsuccessful allocation.
            else 
            {
             printf ( "Incorrect information received, NO Vehicle added.\n");
            }
        }
        
        
        // deallocVehicle a Vehicle
        else if (strcmp(inputString, "2") == 0) 
        {   
            //Initialize
            int rPos = 0, cPos = 0;
            
            // Need vehicle parking stall to remove.
            printf ( "Operation: Remove an individual vehicle\n" ) ; 
            printf ( "What is the vehicle row position (enter a integer)>\n");
            scanf("%d", &rPos);
            printf ( "What is the vehicle column position (enter a integer)>\n");
            scanf("%d", &cPos);
            
            // Found the vehicle's position
            if (Garage[rPos][cPos] != NULL) 
            {
                deallocVehicle(Garage[rPos][cPos]);
                printf ( "Vehicle removed at the following row-col: %d, %d\n",rPos, cPos);
            }
            
             // No Vehicle in the stall given.
            else 
            {
             printf ( "No Vehicle in stall give, row-col: %d, %d\n",rPos, cPos);
            }
        }
        
        
        // Assign a Vehicle a new stall.
        else if (strcmp(inputString, "3") == 0) 
        {   
            //Initialize
            int rPos = 0, cPos = 0;
            int rPos1 = 0, cPos1 = 0;

            printf ( "Operation: To assign an individual vehicle a new parking stall\n" ) ;
            
            // Find current location.
            printf ( "What is the vehicle's current row position (enter a integer)>\n");
            scanf("%d", &rPos);
            printf ( "What is the vehicle's current column position (enter a integer)>\n");
            scanf("%d", &cPos);
            
            // Vehicle is in current location.
            if (Garage[rPos][cPos] != NULL) 
            {
                // Found a vehicle in the position
                printf ( "Found a vehicle in the position>\n");
                
                // Find new location.
                printf ( "What is the vehicle's new row position (enter a integer)>\n");
                scanf("%d", &rPos1);
                printf ( "What is the vehicle's new column position (enter a integer)>\n");
                scanf("%d", &cPos1);
                
                if (Garage[rPos][cPos] != NULL) 
                {
                assignStall(Garage[rPos][cPos], rPos1, cPos1); 
                printf ( "Vehicle assigned a new stall at the following row-col: %d, %d\n",rPos1, cPos1);
                }
                else 
                {
                printf ( "The new stall is occupied, row-col: %d, %d\n",rPos1, cPos1);
                } 
            }
            // Vehicle is not in current location.
            else 
            {
             printf ( "No Vehicle in stall give, row-col: %d, %d\n",rPos, cPos);
            }
        }
        
        
        // Information for a specific Vehicle.
        else if (strcmp(inputString, "4") == 0) 
        {   
            //Initialize
            int rPos = 0, cPos = 0;
            
            printf ( "Operation: To print out all information for a specific vehicle.\n" ) ;
            // Find current location for vehicle of interest.
            printf ( "What is the vehicle's current row position (enter a integer)>\n");
            scanf("%d", &rPos);
            printf ( "What is the vehicle's current column position (enter a integer)>\n");
            scanf("%d", &cPos);
            
            // Vehicle is in given location.
            if (Garage[rPos][cPos] != NULL) 
            {
                 printVehicle(Garage[rPos][cPos]);
            }
            
            // Vehicle is not in given location.
            else
            {
             printf ( "No Vehicle in stall give, row-col: %d, %d\n",rPos, cPos);
            }
        }
        
        
        // Print general information about all the vehicles present.
        else if (strcmp(inputString, "5") == 0) 
        {
            printf ( "Operation: To print out all vehicles info in parking garage\n" ) ;
            printAllVehicles();
        }
        
        
        // Print fuel level of a specific vehicle.
        else if (strcmp(inputString, "6") == 0) 
        {   
            // Initialize 
            int rPos = 0, cPos = 0;
            int printfuel(Vehicle *v);
            printf ( "Operation: To retrieve the fuel level of a vehicle\n" ) ;

            // Find current location for vehicle of interest.
            printf ( "What is the vehicle's current row position (enter a integer)>\n");
            scanf("%d", &rPos);
            printf ( "What is the vehicle's current column position (enter a integer)>\n");
            scanf("%d", &cPos);
            
            // Vehicle is in given location.
            if (Garage[rPos][cPos] != NULL) 
            {
                printfuel(Garage[rPos][cPos]);
            }
            
            // Vehicle is not in given location.
            else  
            {
                 printf ( "No Vehicle in stall give, row-col: %d, %d\n",rPos, cPos);
            }
        }
        
        
        // To refuel a specific vehicle.
        else if (strcmp(inputString, "7") == 0) 
        {
            //Initialize
            int refuelVehicle(Vehicle* v, double fuelAmount);
            int rPos = 0, cPos = 0;
            float vehicleCurFuel = 0;
            printf ( "Operation: To update the fuel level of a vehicle\n" ) ; 
            
            // Find current location for vehicle of interest.
            printf ( "What is the vehicle's current row position (enter a integer)>\n");
            scanf("%d", &rPos);
            printf ( "What is the vehicle's current column position (enter a integer)>\n");
            scanf("%d", &cPos);
            
            // Vehicle is in given location.
            if (Garage[rPos][cPos] != NULL) 
            {   
                //Get the amount to refuel Vehicle.
                printf ( "What is the vehicle amount of fuel to add level (enter double):\n" ) ; 
                scanf("%f", &vehicleCurFuel);
                refuelVehicle(Garage[rPos][cPos], vehicleCurFuel);
            } 
            
            // Vehicle is not in given location.
            else  
            {
                 printf ( "No Vehicle in stall give, row-col: %d, %d\n",rPos, cPos);
            }
        }
        
        
        // Print parking lot.
        else if (strcmp(inputString, "8") == 0) 
        {
            // Print visual information about the parking garage.
            printf ( "Operation: To print a visual representation of the parking garage\n" ) ;
            printGarageMap();
        }
        
        
        // Print a refueling report.
        else if (strcmp(inputString, "9") == 0) 
        {
            printf ( "Operation: To print a refueling report i.e.\n" ) ;
            printRefuelReport();          
        }
        
        
        //Import a hard-coded text file.
        else if (strcmp(inputString, "10") == 0) 
        {
        printf("==========Importing vehicles from a file + outputting map==========\n");
        // Test of importFromFile, test_file.txt must be in pwd and correctly formatted
        assert(10 == importFromFile("test_file.txt"));      //must match name.
        printAllVehicles();
        printGarageMap();
        }
        
        
        //Quit the program.
        else if (strcmp(inputString, "11") == 0) 
        {
            printf ( "Operation: To Exit\n" ) ;           
            return EXIT_SUCCESS;
        }
    }
    return EXIT_SUCCESS;
}