

====Parking Manager Program====


==Introduction==

Parking Manager is a program with a console based interface to interact with the parking lot system. A vehicle that is stored in the parking lot system must have the following information: model, plate number, type (CAR,SUV,TRUCK), fuel level, and fuel maximum capacity. Along with the stall location, these information are "volatile”, so the data is cleared after every termination. The maximum allowed vehicles are hard coded in the variables MAX_VEHICLE_ROW and MAX_VEHICLE_COL which dictate the columns and rows of the garage. All the vehicles in the program are stored in an array, which dynamically allocates space. The user can input all the characteristics of a vehicle, as mentioned above, and select the stall in the garage by inputing the row and column. A stall can only contain one vehicle at a time. The testing functions are divided up by their targets. For a vehicle or vehicles, the testing is done in the test_vehicle.c, whereas for general garage information like fuel reports and printouts, the testing is done in the test_reports.c. A special function was designed to report the fuel levels of a specific vehicle. It is similar to the printVehicle() function, but it exclusively reports only the fuel level of the vehicle desired. When errors are inputed by the user, the interface is able to reset to the main interface which lists the options available. For the specific error of incorrectly naming the vehicle type (not CAR,SUV, or TRUCK), then the program exits. 


==Compiling & Running==

To compile parkingManager have all the files in the same directory.

Note: Include the file ‘test_file.txt’ with that specific name to import the information correctly.

List of files: parkingManager.c, vehicle.c, vehicle.h, reports.c, reports.h,
test_vehicle.c, test_reports.c, test_file.txt, makefile

Enter the following command in terminal:
	make -f makefile all

New files (objects and executables): 
parkingManager, test_vehicle, test_reports, reports.o, vehicle.o, parkingManager.o, test_vehicle.o, test_reports.o


To run parkingManager enter the following command in terminal:
	./parkingManager

To run test_vehicle enter the following command in terminal:
	./test_vehicle

To run test_reports enter the following command in terminal:
	./test_reports

To clean up enter the following command in terminal:
	make -f makefile clean

==Interface Options==
The text base interface is able to perform all the following operations:

1:  To add an individual vehicle.
2:  To remove an individual vehicle.
3:  To assign an individual vehicle a parking stall.
4:  To print out all information for a specific vehicle.
5:  To print out all vehicles info in parking garage.
6:  To retrieve the fuel level of a vehicle.
7:  To update the fuel level of a vehicle.
8:  To print a visual representation of the parking garage.	
9:  To print a refuelling report.
10: To import multiple vehicles from a file.
11: Exit.

==Limitations==

The program’s interface can only locate a vehicle by the location of the stall it occupies.
It should be able to improve by searching the plate number of the vehicle.
Also the program cannot stop the user from entering duplicate information, but it does stop from
having two vehicles occupying one stall or prevent old information from being overridden.

 
