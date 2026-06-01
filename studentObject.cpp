#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Requirement 1: Create a Student Object to store student information
class Student {
private:
    string rollNumber;
    string name;
    int age;

public:
    // Constructors
    Student() {
        rollNumber = "";
        name = "";
        age = 0;
    }

    Student(string r, string n, int a) {
        rollNumber = r;
        name = n;
        age = a;
    }

    // Getters
    string getRollNumber() { return rollNumber; }
    string getName() { return name; }
    int getAge() { return age; }

    // Setters
    void setRollNumber(string r) { rollNumber = r; }
    void setName(string n) { name = n; }
    void setAge(int a) { age = a; }

    // Helper to format data into CSV line
    string toCSV() {
        return rollNumber + "," + name + "," + to_string(age);
    }
};

// Helper function to count total lines/records in the file
int countRecords(string filename) {
    ifstream file(filename);
    if (!file.is_open()) return 0;

    int count = 0;
    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            count++;
        }
    }
    file.close();
    return count;
}

// Requirement 2: Implement a function to display all students stored in the file
void displayAllStudents(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "\nError: Could not open file or file does not exist.\n";
        return;
    }

    string roll, name, ageStr;
    cout << "\n--- Student Records ---\n";
    cout << "Roll Number | Name | Age\n";
    cout << "---------------------------\n";

    // Read CSV line by line parsing by commas
    while (getline(file, roll, ',') && getline(file, name, ',') && getline(file, ageStr)) {
        cout << roll << " | " << name << " | " << ageStr << "\n";
    }
    file.close();
}

// Requirement 3: Search for a student by Roll Number
void searchStudent(string filename) {
    string targetRoll;
    cout << "\nEnter Roll Number to search: ";
    cin >> targetRoll;

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "\nStudent not found (No records exist yet).\n";
        return;
    }

    string roll, name, ageStr;
    bool found = false;

    while (getline(file, roll, ',') && getline(file, name, ',') && getline(file, ageStr)) {
        if (roll == targetRoll) {
            cout << "\nStudent Found:\n";
            cout << "Roll Number: " << roll << "\n";
            cout << "Name: " << name << "\n";
            cout << "Age: " << ageStr << "\n";
            found = true;
            break;
        }
    }
    file.close();

    if (!found) {
        cout << "\nStudent not found\n";
    }
}

// Requirement 4: Update student information permanently
void updateStudent(string filename) {
    string targetRoll;
    cout << "\nEnter Roll Number to update: ";
    cin >> targetRoll;

    int totalRecords = countRecords(filename);
    if (totalRecords == 0) {
        cout << "\nStudent not found (File is empty).\n";
        return;
    }

    // Dynamically allocate array instead of using std::vector
    Student* studentArray = new Student[totalRecords];
    
    ifstream inFile(filename);
    string roll, name, ageStr;
    int index = 0;
    bool found = false;

    // Load file content into memory
    while (getline(inFile, roll, ',') && getline(inFile, name, ',') && getline(inFile, ageStr)) {
        studentArray[index].setRollNumber(roll);
        studentArray[index].setName(name);
        studentArray[index].setAge(stoi(ageStr));
        
        if (roll == targetRoll) {
            found = true;
            // Ask for new information
            string newName;
            int newAge;
            cout << "Enter updated Name: ";
            cin.ignore(); // Clear newline buffer
            getline(cin, newName);
            cout << "Enter updated Age: ";
            cin >> newAge;

            studentArray[index].setName(newName);
            studentArray[index].setAge(newAge);
        }
        index++;
    }
    inFile.close();

    if (!found) {
        cout << "\nStudent not found\n";
    } else {
        // Rewrite the file with updated content
        ofstream outFile(filename, ios::trunc); // Clear old content
        for (int i = 0; i < totalRecords; i++) {
            outFile << studentArray[i].toCSV() << "\n";
        }
        outFile.close();
        cout << "\nStudent information updated successfully!\n";
    }

    // Free allocated memory
    delete[] studentArray;
}

// Requirement 5: Delete student record permanently
void deleteStudent(string filename) {
    string targetRoll;
    cout << "\nEnter Roll Number to delete: ";
    cin >> targetRoll;

    int totalRecords = countRecords(filename);
    if (totalRecords == 0) {
        cout << "\nStudent not found (File is empty).\n";
        return;
    }

    Student* studentArray = new Student[totalRecords];
    
    ifstream inFile(filename);
    string roll, name, ageStr;
    int index = 0;
    bool found = false;

    while (getline(inFile, roll, ',') && getline(inFile, name, ',') && getline(inFile, ageStr)) {
        if (roll == targetRoll) {
            found = true;
            // Skip saving this record to memory (effectively deleting it)
            continue; 
        }
        studentArray[index].setRollNumber(roll);
        studentArray[index].setName(name);
        studentArray[index].setAge(stoi(ageStr));
        index++;
    }
    inFile.close();

    if (!found) {
        cout << "\nStudent not found\n";
    } else {
        // Rewrite the file without the deleted record
        ofstream outFile(filename, ios::trunc);
        for (int i = 0; i < index; i++) { // Only loop up to 'index' (totalRecords - 1)
            outFile << studentArray[i].toCSV() << "\n";
        }
        outFile.close();
        cout << "\nStudent record deleted successfully!\n";
    }

    delete[] studentArray;
}

// Helper initialization to create standard assignment sample records if file doesn't exist
void initializeSampleData(string filename) {
    ifstream testFile(filename);
    if (!testFile.is_open()) {
        ofstream outFile(filename);
        outFile << "202312051,lithacynthia,18\n";
        outFile << "202312052,dessama,18\n";
        outFile << "202312053,david,20\n";
        outFile.close();
    } else {
        testFile.close();
    }
}

// Requirement 7: Menu-driven system using a loop and switch statement
int main() {
    string filename = "student.txt";
    initializeSampleData(filename); // Populates text file with assignment values

    int choice;
    do {
        cout << "\n==============================\n";
        cout << "1. Display All Students\n";
        cout << "2. Search Student\n";
        cout << "3. Update Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
        cout << "==============================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayAllStudents(filename);
                break;
            case 2:
                searchStudent(filename);
                break;
            case 3:
                updateStudent(filename);
                break;
            case 4:
                deleteStudent(filename);
                break;
            case 5:
                cout << "\nExiting program. Goodbye!\n";
                break;
            default:
                cout << "\nInvalid choice! Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}