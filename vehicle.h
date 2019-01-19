//yasin isse 11240548 cmpt 214 assignment 3

# ifndef VEHICLE_H
# define VEHICLE_H

// Represents the type of a vehicle: C for car, T for truck, S for SUV
typedef enum {CAR, TRUCK, SUV} VType;

// The maximum number of vehicles that can be stored in the parking garage
#define MAX_VEHICLE_ROW 10
#define MAX_VEHICLE_COL 10




// Data type to represent a single vehicle
typedef struct {
    char* model;               // string with the make and model of the vehicle
    char* plate;               // licence plate of the vehicle as a string
    VType type;          // either CAR, TRUCK OR SUV
    double curFuel;          // current fuel level, in litres
    double maxFuel;       // maximum fuel level, in litres
} Vehicle;
Vehicle* Garage[MAX_VEHICLE_ROW][MAX_VEHICLE_COL];


// allocVehicle:
//   Create and initialize a new vehicle record dynamically
// In:
//   model - a C string containing the vehicle's model
//   plate - a C string containing the vehicle's licence plate
//   type - a VType: one of C, T, S
//   curFuel - current fuel level, in litres
//   maxFuel - maximum fuel level, in litres
// Out:
//   model/plate is unchanged, vehicle is entered into global Garage array
//   return -- The address of the new record, otherwise NULL on error
Vehicle* allocVehicle(char* model, char* plate, VType type, double curFuel, double maxFuel) ;



// deallocVehicle:
//   Delete a vehicles's record and deallocate any associated memory
// In:
//   v - a valid vehicle pointer
// Out:
//   vehicle's record is removed from global Vehicle array
//   return -- 0 on success, otherwise -1
int deallocVehicle(Vehicle* v); 


// assignStall:
//   Assigns the vehicle v to the stall in Garage with row r and column c
// In:
//   v - a valid pointer to a vehicle
//   r - row index in Garage to place the vehicle
//   c - column index in Garage to place the vehicle
// Out:
//   pointer to vehicle stored in correct place in global Garage array
//   return -- 0 on success, otherwise -1
int assignStall(Vehicle* v, int r, int c);




// calcFuel:
//   Calculates the amount of fuel in vehicle v as a percentage
// In:
//   v - a valid pointer to a vehicle
// Out:
//   return -- returns a percentage between 0 and 100, -1 on error
double calcFuel(Vehicle* v);




// refuelVehicle:
//   Adds fuelAmount litres of fuel to vehicle v, will discard any remaining fuel after tank is full
// In:
//   v - a valid pointer to a vehicle
//   fuelAmount - valid amount of fuel in litres
// Out:
//   return -- 0 on success, otherwise -1
int refuelVehicle(Vehicle* v, double fuelAmount) ;


// printVehicle:
//   Prints all information on file for a vehicle in a user-friendly format
// In:
//   v - a valid pointer to a Vehicle
// Out:
//   vehicle's record is printed to standard output
//   on error, nothing is printed
void printVehicle(Vehicle* v);


// printfuel:
//   Prints  fuel level of vehicle in a user-friendly format
// In:
//   v - a valid pointer to a Vehicle
// Out:
//   vehicle's fuel level to standard output
//   on error, nothing is printed
void printfeul(Vehicle* v);


// Maximum number of characters per line of a file to be read in
const int MAX_READ_SIZE;


//NOTE: This function was not required for this assignment - it is provided for A3
// importFromFile:
//   Initialize vehicle records from a file, skips vehicles when invalid data
//   is read in - stops importing vehicles if a serious formatting error or
//   EOF is found
// In:
//   file - a C string containing a valid file path
// Out:
//   file is unchanged, vehicles are entered into global Garage array
//   return -- number of vehicles added, 0 if no vehicles added
int importFromFile(char* file);

#endif