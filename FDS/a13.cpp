#include <iostream>
#include <string>
using namespace std;

class CircularQueue {
private:
    string* orders;
    int front;
    int rear;
    int capacity;

public:
    CircularQueue(int size) {
        capacity = size;
        orders = new string[capacity];
        front = -1;
        rear = -1;
    }

    ~CircularQueue() {
        delete[] orders;
    }

    bool isFull() {
        return (front == 0 && rear == capacity - 1) || (front == rear + 1);
    }

    bool isEmpty() {
        return front == -1;
    }

    void placeOrder(string order) {
        if (isFull()) {
            cout << "Order queue is full. Cannot place order: " << order << endl;
            return;
        }

        if (front == -1) { // First order being placed
            front = 0;
            rear = 0;
        } else if (rear == capacity - 1) { // Wrap around
            rear = 0;
        } else {
            rear++;
        }
        orders[rear] = order;
        cout << "Order placed: " << order << endl;
    }

    void serveOrder() {
        if (isEmpty()) {
            cout << "No orders to serve." << endl;
            return;
        }

        cout << "Serving order: " << orders[front] << endl;
        if (front == rear) { // Only one order
            front = -1;
            rear = -1;
        } else if (front == capacity - 1) { // Wrap around
            front = 0;
        } else {
            front++;
        }
    }

    void displayOrders() {
        if (isEmpty()) {
            cout << "No orders in the queue." << endl;
            return;
        }

        cout << "Current orders in the queue: ";
        if (rear >= front) {
            for (int i = front; i <= rear; i++) {
                cout << orders[i] << " ";
            }
        } else {
            for (int i = front; i < capacity; i++) {
                cout << orders[i] << " ";
            }
            for (int i = 0; i <= rear; i++) {
                cout << orders[i] << " ";
            }
        }
        cout << endl;
    }
};

// Main function to test the pizza parlor simulation
int main() {
    int maxOrders;
    cout << "Enter maximum number of orders that can be accepted: ";
    cin >> maxOrders;

    CircularQueue cq(maxOrders);
    int choice;
    string order;

    do {
        cout << "1. Place Order\n2. Serve Order\n3. Display Orders\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter order: ";
                cin >> order;
                cq.placeOrder(order);
                break;
            case 2:
                cq.serveOrder();
                break;
            case 3:
                cq.displayOrders();
                break;
            case 4:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice! Please enter again." << endl;
        }
    } while (choice != 4);

    return 0;
}
