#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Student {
    int rollNo;
    string name;
    string division;
    string address;
};

void addStudent() {
    Student student;
    ofstream outFile("students.txt", ios::app); // Open file in append mode

    cout << "Enter Roll Number: ";
    cin >> student.rollNo;
    cin.ignore(); // To consume the newline character after the integer input
    cout << "Enter Name: ";
    getline(cin, student.name);
    cout << "Enter Division: ";
    getline(cin, student.division);
    cout << "Enter Address: ";
    getline(cin, student.address);

    outFile.write(reinterpret_cast<char*>(&student), sizeof(student));
    outFile.close();

    cout << "Student added successfully!" << endl;
}

void deleteStudent() {
    int rollNo;
    cout << "Enter the Roll Number to delete: ";
    cin >> rollNo;

    ifstream inFile("students.txt", ios::in | ios::binary);
    ofstream tempFile("temp.txt", ios::out | ios::binary);

    Student student;
    bool found = false;
    
    while (inFile.read(reinterpret_cast<char*>(&student), sizeof(student))) {
        if (student.rollNo == rollNo) {
            found = true;
            continue; // Skip writing this student to the temporary file
        }
        tempFile.write(reinterpret_cast<char*>(&student), sizeof(student));
    }

    inFile.close();
    tempFile.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "Student with Roll Number " << rollNo << " deleted successfully!" << endl;
    else
        cout << "No student found with Roll Number " << rollNo << endl;
}

void displayStudent() {
    int rollNo;
    cout << "Enter the Roll Number to display: ";
    cin >> rollNo;

    ifstream inFile("students.txt", ios::in | ios::binary);
    Student student;
    bool found = false;

    while (inFile.read(reinterpret_cast<char*>(&student), sizeof(student))) {
        if (student.rollNo == rollNo) {
            found = true;
            cout << "\nStudent Details: \n";
            cout << "Roll Number: " << student.rollNo << endl;
            cout << "Name: " << student.name << endl;
            cout << "Division: " << student.division << endl;
            cout << "Address: " << student.address << endl;
            break;
        }
    }

    inFile.close();

    if (!found) {
        cout << "No student found with Roll Number " << rollNo << endl;
    }
}

int main() {
    int choice;
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add Student\n";
        cout << "2. Delete Student\n";
        cout << "3. Display Student\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                deleteStudent();
                break;
            case 3:
                displayStudent();
                break;
            case 4:
                cout << "Exiting program." << endl;
                return 0;
            default:
                cout << "Invalid choice, please try again!" << endl;
        }
    }
}
