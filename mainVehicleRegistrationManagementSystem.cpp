#include <iostream>
#include "VehicleRegistrationManagementSystem.h"

void addVehicleRecord();
void displayAllRecords();
void searchByPlate();

int main() {
    int choice;
    do {
        std::cout << "\n=========================================\n";
        std::cout << "  VEHICLE REGISTRATION MANAGEMENT SYSTEM \n";
        std::cout << "=========================================\n";
        std::cout << "1. Register New Vehicle & Owner\n";
        std::cout << "2. Display All Records (Table View)\n";
        std::cout << "3. Search Record by Plate Number\n";
        std::cout << "4. Exit System\n";
        std::cout << "Enter your choice (1-4): ";
        
        if (!(std::cin >> choice)) {
            std::cout << ">> Invalid option. Please key in numeric digits only.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1: addVehicleRecord(); break;
            case 2: displayAllRecords(); break;
            case 3: searchByPlate(); break;
            case 4: std::cout << "\nShutting down administrative console interface. Goodbye.\n"; break;
            default: std::cout << ">> Choice selection out of range. Please use 1-4.\n";
        }
    } while (choice != 4);

    return 0;
}