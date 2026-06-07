#ifndef VEHICLEREGISTRATIONMANAGEMENTSYSTEM_H
#define VEHICLEREGISTRATIONMANAGEMENTSYSTEM_H

#include <string>
#include <iostream>

// Base Class: User
class User {
private:
    std::string name;
    std::string email;
    std::string phone;

public:
    // Constructor
    User(std::string n, std::string e, std::string p) : name(n), email(e), phone(p) {}

    // Encapsulation: Getters and Setters
    std::string getName() const { return name; }
    void setName(std::string n) { name = n; }

    std::string getEmail() const { return email; }
    void setEmail(std::string e) { email = e; }

    std::string getPhone() const { return phone; }
    void setPhone(std::string p) { phone = p; }
};

// Derived Class: VehicleOwner inheriting from User (Inheritance Design)
class VehicleOwner : public User {
public:
    // Constructor Chaining
    VehicleOwner(std::string n, std::string e, std::string p) : User(n, e, p) {}
};

// Separate Vehicle Class associated with VehicleOwner
class Vehicle {
private:
    std::string plateNumber;
    std::string vehicleType;
    int year;
    VehicleOwner owner; 

public:
    // Constructor
    Vehicle(std::string plate, std::string type, int yr, VehicleOwner o)
        : plateNumber(plate), vehicleType(type), year(yr), owner(o) {}

    // Getters
    std::string getPlateNumber() const { return plateNumber; }
    std::string getVehicleType() const { return vehicleType; }
    int getYear() const { return year; }
    VehicleOwner getOwner() const { return owner; }

    std::string toCSV() const {
        return plateNumber + "," + vehicleType + "," + std::to_string(year) + "," +
               owner.getName() + "," + owner.getEmail() + "," + owner.getPhone();
    }
};

bool validatePlate(const std::string& plate);
bool validateEmail(const std::string& email);
bool validatePhone(const std::string& phone);

void addVehicleRecord();
void displayAllRecords();
void searchByPlate();

#endif