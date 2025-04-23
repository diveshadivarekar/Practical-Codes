#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Employee {
    int empID;
    string name;
    string designation;
    float salary;
};

struct Index {
    int empID;
    long position; // The position of the employee record in the data file
};

void addEmployee() {
    Employee emp;
    cout << "Enter Employee ID: ";
    cin >> emp.empID;
    cin.ignore(); // To ignore the newline character
    cout << "Enter Employee Name: ";
    getline(cin, emp.name);
    cout << "Enter Employee Designation: ";
    getline(cin, emp.designation);
    cout << "Enter Employee Salary: ";
    cin >> emp.salary;

    ofstream dataFile("employees.dat", ios::app | ios::binary);
    dataFile.write(reinterpret_cast<char*>(&emp), sizeof(emp));
    dataFile.close();

    // Update index file
    fstream indexFile("index.dat", ios::in | ios::out | ios::binary);
    if (!indexFile) {
        indexFile.open("index.dat", ios::out | ios::binary);
    }
    
    // Get the position of the new record in the data file
    indexFile.seekg(0, ios::end);
    long position = indexFile.tellg();
    
    // Add the index entry
    Index indexEntry = {emp.empID, position};
    indexFile.seekp(0, ios::end);
    indexFile.write(reinterpret_cast<char*>(&indexEntry), sizeof(indexEntry));
    indexFile.close();

    cout << "Employee added successfully!" << endl;
}

void deleteEmployee() {
    int empID;
    cout << "Enter Employee ID to delete: ";
    cin >> empID;

    ifstream dataFile("employees.dat", ios::in | ios::binary);
    fstream indexFile("index.dat", ios::in | ios::out | ios::binary);

    vector<Index> indices;
    Index indexEntry;
    bool found = false;

    while (indexFile.read(reinterpret_cast<char*>(&indexEntry), sizeof(indexEntry))) {
        indices.push_back(indexEntry);
    }

    // Search for the employee in the index
    for (auto it = indices.begin(); it != indices.end(); ++it) {
        if (it->empID == empID) {
            found = true;
            indices.erase(it); // Remove the index entry for the employee
            break;
        }
    }

    if (found) {
        // Recreate the index file with the updated list
        indexFile.close();
        indexFile.open("index.dat", ios::out | ios::binary | ios::trunc);
        for (const auto& idx : indices) {
            indexFile.write(reinterpret_cast<const char*>(&idx), sizeof(idx)); // Change here
        }

        // Create a new data file excluding the deleted employee
        ofstream tempDataFile("temp_employees.dat", ios::binary);
        Employee emp;
        long position;

        while (dataFile.read(reinterpret_cast<char*>(&emp), sizeof(emp))) {
            position = dataFile.tellg();
            if (position != indexEntry.position) {
                tempDataFile.write(reinterpret_cast<const char*>(&emp), sizeof(emp)); // Change here
            }
        }

        dataFile.close();
        tempDataFile.close();

        // Replace the original file with the temp file
        remove("employees.dat");
        rename("temp_employees.dat", "employees.dat");

        cout << "Employee deleted successfully!" << endl;
    } else {
        cout << "Employee not found!" << endl;
    }

    indexFile.close();
}


void displayEmployee() {
    int empID;
    cout << "Enter Employee ID to display: ";
    cin >> empID;

    ifstream indexFile("index.dat", ios::in | ios::binary);
    if (!indexFile) {
        cout << "Index file not found!" << endl;
        return;
    }

    Index indexEntry;
    bool found = false;

    while (indexFile.read(reinterpret_cast<char*>(&indexEntry), sizeof(indexEntry))) {
        if (indexEntry.empID == empID) {
            found = true;
            // Display the employee record
            ifstream dataFile("employees.dat", ios::in | ios::binary);
            dataFile.seekg(indexEntry.position);
            Employee emp;
            dataFile.read(reinterpret_cast<char*>(&emp), sizeof(emp));

            cout << "\nEmployee Details:\n";
            cout << "Employee ID: " << emp.empID << endl;
            cout << "Name: " << emp.name << endl;
            cout << "Designation: " << emp.designation << endl;
            cout << "Salary: " << emp.salary << endl;

            dataFile.close();
            break;
        }
    }

    if (!found) {
        cout << "Employee not found!" << endl;
    }

    indexFile.close();
}

int main() {
    int choice;
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add Employee\n";
        cout << "2. Delete Employee\n";
        cout << "3. Display Employee\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                deleteEmployee();
                break;
            case 3:
                displayEmployee();
                break;
            case 4:
                cout << "Exiting program." << endl;
                return 0;
            default:
                cout << "Invalid choice, please try again!" << endl;
        }
    }
}
