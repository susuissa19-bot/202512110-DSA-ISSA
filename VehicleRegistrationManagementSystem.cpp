#include "VehicleRegistrationManagementSystem.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <regex>

const std::string FILE_NAME = "records.txt"; // Hardcoded file requirement 

bool validatePlate(const std::string& plate) {
    
    std::regex pattern("^[A-Z]{3}[0-9]{3}[A-Z]{1}$");
    return std::regex_match(plate, pattern);
}

bool validateEmail(const std::string& email) {
 
    std::regex pattern("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    return std::regex_match(email, pattern);
}

bool validatePhone(const std::string& phone) {

    std::regex pattern("^\\+250[0-9]{9}$");
    return std::regex_match(phone, pattern);
}

// Write feature using append (ios::app) mode 
void addVehicleRecord() {
    std::string plate, type, name, email, phone, yearStr;
    int year;

    std::cout << "\n=== Register New Vehicle & Owner ===\n";
    std::cin.ignore();

    // Loops reject input and force re-entry if validation criteria fails 
    do {
        std::cout << "Enter Plate Number (e.g., RAA123A): ";
        std::getline(std::cin, plate);
        if (!validatePlate(plate)) std::cout << ">> Invalid plate structure. Please re-enter.\n";
    } while (!validatePlate(plate));

    std::cout << "Enter Vehicle Type (e.g., Sedan, SUV): ";
    std::getline(std::cin, type);

    while (true) {
        std::cout << "Enter Production Year: ";
        std::getline(std::cin, yearStr);
        try {
            year = std::stoi(yearStr); 
            if (year > 1800 && year <= 2026) break;
            else std::cout << ">> Please input a realistic calendar year.\n";
        } catch (...) {
            std::cout << ">> Invalid entry. Number expected.\n";
        }
    }

    std::cout << "Enter Owner Full Name: ";
    std::getline(std::cin, name);

    do {
        std::cout << "Enter Owner Email: ";
        std::getline(std::cin, email);
        if (!validateEmail(email)) std::cout << ">> Invalid email formatting. Must contain '@' and '.'.\n";
    } while (!validateEmail(email));

    do {
        std::cout << "Enter Owner Phone (Must start with +250): ";
        std::getline(std::cin, phone);
        if (!validatePhone(phone)) std::cout << ">> Invalid format. Must start with +250 and have 13 characters.\n";
    } while (!validatePhone(phone));

    VehicleOwner owner(name, email, phone);
    Vehicle newVehicle(plate, type, year, owner);

    std::ofstream outFile(FILE_NAME, std::ios::app);
    if (outFile.is_open()) {
        outFile << newVehicle.toCSV() << "\n";
        outFile.close();
        std::cout << "\n[Success] Record successfully appended to records.txt!\n";
    } else {
        std::cerr << "[Error] Unable to gain system access to records.txt.\n";
    }
}

void printTableRow(const std::string& p, const std::string& t, const std::string& y, 
                   const std::string& n, const std::string& e, const std::string& ph) {
    std::cout << "| " << std::left << std::setw(10) << p 
              << "| " << std::setw(12) << t 
              << "| " << std::setw(6)  << y 
              << "| " << std::setw(18) << n 
              << "| " << std::setw(22) << e 
              << "| " << std::setw(15) << ph << "|\n";
}

void displayAllRecords() {
    std::ifstream inFile(FILE_NAME);
    if (!inFile.is_open()) {
        std::cout << "\n>> Notice: The data file records.txt is currently empty or uninitialized.\n";
        return;
    }

    std::cout << "\n" << std::string(91, '-') << "\n";
    printTableRow("Plate No", "Type", "Year", "Owner Name", "Email Address", "Phone Number");
    std::cout << std::string(91, '-') << "\n";

    std::string line;
    
    while (std::getline(inFile, line)) {
        
        if (line.empty() || line.find_first_not_of(" \t\r\n") == std::string::npos) {
            continue;
        }
        
        std::stringstream ss(line); 
        std::string plate, type, yearStr, name, email, phone;

        if (std::getline(ss, plate, ',') &&
            std::getline(ss, type, ',') &&
            std::getline(ss, yearStr, ',') &&
            std::getline(ss, name, ',') &&
            std::getline(ss, email, ',')) {
            
            std::getline(ss, phone);

            if (!phone.empty() && phone.back() == '\r') {
                phone.pop_back();
            }

            printTableRow(plate, type, yearStr, name, email, phone);
        }
    }
    std::cout << std::string(91, '-') << "\n";
    inFile.close();
}

void searchByPlate() {
    std::ifstream inFile(FILE_NAME);
    if (!inFile.is_open()) {
        std::cout << "\n>> Notice: No registered records available to look through.\n";
        return;
    }

    std::string searchPlate;
    std::cout << "\nEnter Plate Number to search: ";
    std::cin >> searchPlate;

    std::string line;
    bool found = false;

    while (std::getline(inFile, line)) {
        if (line.empty() || line.find_first_not_of(" \t\r\n") == std::string::npos) {
            continue;
        }

        std::stringstream ss(line);
        std::string plate, type, yearStr, name, email, phone;

        if (std::getline(ss, plate, ',') &&
            std::getline(ss, type, ',') &&
            std::getline(ss, yearStr, ',') &&
            std::getline(ss, name, ',') &&
            std::getline(ss, email, ',')) {
            
            std::getline(ss, phone);
            if (!phone.empty() && phone.back() == '\r') {
                phone.pop_back();
            }

            if (plate == searchPlate) {
                found = true;
                std::cout << "\n================ MATCH FOUND ================\n";
                std::cout << "  Plate Number : " << plate << "\n";
                std::cout << "  Vehicle Type : " << type << "\n";
                std::cout << "  Mfg Year     : " << yearStr << "\n";
                std::cout << "  Owner Name   : " << name << "\n";
                std::cout << "  Owner Email  : " << email << "\n";
                std::cout << "  Owner Phone  : " << phone << "\n";
                std::cout << "==============================================\n";
                break;
            }
        }
    }

    if (!found) {
        std::cout << "\n>> Notification: Vehicle with plate '" << searchPlate << "' does not exist in the system.\n";
    }
    inFile.close();
}