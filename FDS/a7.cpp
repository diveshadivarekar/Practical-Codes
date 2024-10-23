#include <iostream>
#include <string>

using namespace std;

struct Node {
    string name;
    string prn;
    Node* next;
};

// Class to represent the Pinnacle Club
class PinnacleClub {
private:
    Node* president;
    Node* secretary;

public:
    PinnacleClub() {
        president = new Node{"President", "PRN-PRES", nullptr};  // First node for President
        secretary = nullptr;  // Secretary initially set to nullptr
    }

    // Function to add a member
    void addMember(string name, string prn) {
        Node* newNode = new Node{name, prn, nullptr};
        if (secretary == nullptr) {
            president->next = newNode;
            secretary = newNode; // Secretary becomes the first member
        } else {
            Node* temp = president;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode; // Add to the end of the list
        }
    }

    // Function to delete a member
    void deleteMember(string prn) {
        Node* temp = president;
        Node* prev = nullptr;

        while (temp != nullptr && temp->prn != prn) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Member with PRN " << prn << " not found." << endl;
            return;
        }

        if (prev == nullptr) { // Deleting the first member (after president)
            president->next = temp->next;
        } else {
            prev->next = temp->next;
        }
        delete temp; // Free memory
        cout << "Member with PRN " << prn << " deleted successfully." << endl;
    }

    // Function to compute total number of members
    int totalMembers() {
        int count = 0;
        Node* temp = president->next; // Start counting after president
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    // Function to display members
    void displayMembers() {
        Node* temp = president;
        cout << "Club Members:" << endl;
        while (temp != nullptr) {
            cout << "Name: " << temp->name << ", PRN: " << temp->prn << endl;
            temp = temp->next;
        }
    }

    // Function to concatenate two lists
    void concatenate(PinnacleClub& other) {
        if (this->secretary == nullptr) {
            this->president->next = other.president->next;
        } else {
            Node* temp = this->president;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = other.president->next; // Concatenate the second list
        }
    }

    ~PinnacleClub() {
        Node* current = president;
        Node* nextNode;
        while (current != nullptr) {
            nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
};

int main() {
    PinnacleClub divisionA;
    PinnacleClub divisionB;

    divisionA.addMember("Divesh", "PRN-001");
    divisionA.addMember("John", "PRN-002");
    divisionA.addMember("Nobita", "PRN-003");

    divisionB.addMember("Been", "PRN-004");
    divisionB.addMember("Shinchan", "PRN-005");

    cout << "Division A:" << endl;
    divisionA.displayMembers();
    cout << "Total Members in Division A: " << divisionA.totalMembers() << endl;

    cout << "\nDivision B:" << endl;
    divisionB.displayMembers();
    cout << "Total Members in Division B: " << divisionB.totalMembers() << endl;

    cout << "\nConcatenating Division A and Division B:" << endl;
    divisionA.concatenate(divisionB);
    divisionA.displayMembers();
    cout << "Total Members after Concatenation: " << divisionA.totalMembers() << endl;

    // Example of deleting a member
    divisionA.deleteMember("PRN-002");
    divisionA.displayMembers();
    cout << "Total Members after Deletion: " << divisionA.totalMembers() << endl;

    return 0;
}
