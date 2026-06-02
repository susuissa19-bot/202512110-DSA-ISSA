#include <iostream>
#include <string>

class Car {
private:
   
    std::string brand;
    double price;
    int year;
    std::string state; 

public:
    Car(std::string b, double p, int y, std::string s) {
        brand = b;
        price = p;
        year = y;
        state = s;
    }

    void driveRight() {
        std::cout << "The " << brand << " is driving right.\n";
    }

    void driveLeft() {
        std::cout << "The " << brand << " is driving left.\n";
    }

    void turnAround() {
        std::cout << "The " << brand << " is turning around.\n";
    }

    void goStraight() {
        std::cout << "The " << brand << " is accelerating straight ahead.\n";
    }

    void goBack() {
        std::cout << "The " << brand << " is shifting into reverse and going back.\n";
    }

    void pipi() {
        std::cout << "The " << brand << " honks its horn: Pipi! Pipi!\n";
    }

    void madeAccident() {
        state = "Totaled/Damaged";
        std::cout << "Oh no! The " << brand << " made an accident! Current state: " << state << "\n";
    }

    void displayInfo() {
        std::cout << "--- Car Details ---\n";
        std::cout << "Brand: " << brand << "\n";
        std::cout << "Price: $" << price << "\n";
        std::cout << "Year: " << year << "\n";
        std::cout << "State: " << state << "\n";
        std::cout << "-------------------\n";
    }
};


int main() {

    Car myCar("GMC", 25000.50, 2022, "Excellent");

    myCar.displayInfo();
    std::cout << "\nExecuting Car Behaviors:\n";

    myCar.goStraight();
    myCar.driveRight();
    myCar.driveLeft();
    myCar.pipi();
    myCar.turnAround();
    myCar.goBack();
    myCar.madeAccident();

    return 0;
}