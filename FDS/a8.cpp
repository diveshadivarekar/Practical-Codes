#include <iostream>
#include <string>

using namespace std;

struct Node {
    char bit;          // Store a binary bit ('0' or '1')
    Node* next;       // Pointer to the next node
    Node* prev;       // Pointer to the previous node

    Node(char b) : bit(b), next(nullptr), prev(nullptr) {}
};

class BinaryNumber {
private:
    Node* head;       // Pointer to the first node
    Node* tail;       // Pointer to the last node

public:
    BinaryNumber() : head(nullptr), tail(nullptr) {}

    // Function to insert bits at the end of the doubly linked list
    void insertBit(char bit) {
        Node* newNode = new Node(bit);
        if (!head) {
            head = tail = newNode; // If the list is empty
        } else {
            tail->next = newNode;  // Insert at the end
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Function to display the binary number
    void display() {
        Node* temp = head;
        while (temp) {
            cout << temp->bit;
            temp = temp->next;
        }
        cout << endl;
    }

    // Function to compute 1's complement
    void onesComplement() {
        Node* temp = head;
        while (temp) {
            temp->bit = (temp->bit == '0') ? '1' : '0'; // Flip bits
            temp = temp->next;
        }
    }

    // Function to compute 2's complement
    void twosComplement() {
        onesComplement(); // Compute 1's complement
        addBinary("1");   // Add 1 to the 1's complement
    }

    // Function to add a binary number
    void addBinary(const string& binary) {
        Node* temp = tail;  // Start from the last node
        int carry = 0;
        int i = binary.length() - 1;

        while (temp || i >= 0 || carry) {
            int sum = carry;

            // Add current binary number bit if available
            if (temp) {
                sum += (temp->bit - '0'); // Convert char to int
                temp = temp->prev;        // Move to the previous node
            }

            // Add the new binary number bit if available
            if (i >= 0) {
                sum += (binary[i] - '0'); // Convert char to int
                i--;
            }

            carry = sum / 2;             // Calculate carry
            char sumBit = (sum % 2) + '0'; // Determine sum bit
            insertBit(sumBit);           // Insert the sum bit at the front
        }
    }

    // Destructor to free memory
    ~BinaryNumber() {
        Node* current = head;
        while (current) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
};

int main() {
    BinaryNumber binaryNumber;

    // Input binary number
    string inputBinary;
    cout << "Enter a binary number: ";
    cin >> inputBinary;

    for (char bit : inputBinary) {
        binaryNumber.insertBit(bit);
    }

    cout << "Original Binary Number: ";
    binaryNumber.display();

    // Compute and display 1's complement
    binaryNumber.onesComplement();
    cout << "1's Complement: ";
    binaryNumber.display();

    // Compute and display 2's complement
    binaryNumber.twosComplement();
    cout << "2's Complement: ";
    binaryNumber.display();

    // Adding another binary number
    string binaryToAdd;
    cout << "Enter another binary number to add: ";
    cin >> binaryToAdd;

    binaryNumber.addBinary(binaryToAdd);
    cout << "Result after addition: ";
    binaryNumber.display();

    return 0;
}
