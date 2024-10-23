#include <iostream>
using namespace std;

class Deque {
private:
    int* arr;
    int front;
    int rear;
    int capacity;

public:
    Deque(int size) {
        capacity = size;
        arr = new int[capacity];
        front = -1;
        rear = -1;
    }

    ~Deque() {
        delete[] arr;
    }

    bool isFull() {
        return (front == 0 && rear == capacity - 1) || (front == rear + 1);
    }

    bool isEmpty() {
        return front == -1;
    }

    void addFront(int value) {
        if (isFull()) {
            cout << "Deque is full. Cannot add " << value << " to front." << endl;
            return;
        }

        if (front == -1) { // First element being added
            front = 0;
            rear = 0;
        } else if (front == 0) { // Wrap around
            front = capacity - 1;
        } else {
            front--;
        }
        arr[front] = value;
        cout << "Added " << value << " to front." << endl;
    }

    void addRear(int value) {
        if (isFull()) {
            cout << "Deque is full. Cannot add " << value << " to rear." << endl;
            return;
        }

        if (front == -1) { // First element being added
            front = 0;
            rear = 0;
        } else if (rear == capacity - 1) { // Wrap around
            rear = 0;
        } else {
            rear++;
        }
        arr[rear] = value;
        cout << "Added " << value << " to rear." << endl;
    }

    void deleteFront() {
        if (isEmpty()) {
            cout << "Deque is empty. Cannot delete from front." << endl;
            return;
        }

        cout << "Deleted " << arr[front] << " from front." << endl;
        if (front == rear) { // Only one element
            front = -1;
            rear = -1;
        } else if (front == capacity - 1) { // Wrap around
            front = 0;
        } else {
            front++;
        }
    }

    void deleteRear() {
        if (isEmpty()) {
            cout << "Deque is empty. Cannot delete from rear." << endl;
            return;
        }

        cout << "Deleted " << arr[rear] << " from rear." << endl;
        if (front == rear) { // Only one element
            front = -1;
            rear = -1;
        } else if (rear == 0) { // Wrap around
            rear = capacity - 1;
        } else {
            rear--;
        }
    }

    void display() {
        if (isEmpty()) {
            cout << "Deque is empty." << endl;
            return;
        }

        cout << "Deque elements: ";
        if (rear >= front) {
            for (int i = front; i <= rear; i++) {
                cout << arr[i] << " ";
            }
        } else {
            for (int i = front; i < capacity; i++) {
                cout << arr[i] << " ";
            }
            for (int i = 0; i <= rear; i++) {
                cout << arr[i] << " ";
            }
        }
        cout << endl;
    }
};

// Main function to test the deque
int main() {
    Deque dq(5); // Create a deque of size 5

    int choice, value;
    do {
        cout << "1. Add to Front\n2. Add to Rear\n3. Delete from Front\n4. Delete from Rear\n5. Display Deque\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to add to front: ";
                cin >> value;
                dq.addFront(value);
                break;
            case 2:
                cout << "Enter value to add to rear: ";
                cin >> value;
                dq.addRear(value);
                break;
            case 3:
                dq.deleteFront();
                break;
            case 4:
                dq.deleteRear();
                break;
            case 5:
                dq.display();
                break;
            case 6:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice! Please enter again." << endl;
        }
    } while (choice != 6);

    return 0;
}
