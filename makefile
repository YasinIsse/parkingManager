# makefile for parkingManager Assignment 214 
# Author: Yasin Isse, 11240548, yai472 

# Flags for the C compiler 
CFLAGS = -Wall -Wextra

.PHONY: all tests clean

all: parkingManager test_reports test_vehicle

PARKINGMANAGER_OBJ = reports.o vehicle.o parkingManager.o

parkingManager: $(PARKINGMANAGER_OBJ)
		gcc $(PARKINGMANAGER_OBJ) -o parkingManager

TEST_REPORTS_OBJ = reports.o vehicle.o test_reports.o

test_reports: $(TEST_REPORTS_OBJ)
		gcc $(TEST_REPORTS_OBJ) -o test_reports

TEST_VEHICLE_OBJ = reports.o vehicle.o test_vehicle.o

test_vehicle: $(TEST_VEHICLE_OBJ)
		gcc $(TEST_VEHICLE_OBJ) -o test_vehicle

tests: test_reports test_vehicle


parkingManager.o: parkingManager.c reports.h vehicle.h
		gcc $(CFLAGS) -c parkingManager.c

vehicle.o: vehicle.c vehicle.h
		gcc $(CFLAGS) -c vehicle.c
 
reports.o: reports.c reports.h vehicle.h
		gcc $(CFLAGS) -c reports.c

test_vehicle.o: test_vehicle.c reports.h vehicle.h
		gcc $(CFLAGS) -c test_vehicle.c

test_reports.o: test_reports.c reports.h vehicle.h
		gcc $(CFLAGS) -c test_reports.c


clean:
	rm -f reports.o vehicle.o test_vehicle.o parkingManager.o test_reports.o
	rm -f parkingManager test_vehicle test_reports


