#include <iostream>
#include <queue>
#include <string>

using namespace std;

struct Patient {
    string name;
    int priority;

    Patient(string n, int p) : name(n), priority(p) {}

    bool operator<(const Patient& other) const {
        return priority > other.priority;
    }
};

class HospitalQueue {
private:
    priority_queue<Patient> pq;

public:
    void addPatient(const string& name, int priority) {
        pq.push(Patient(name, priority));
    }

    void servePatient() {
        if (!pq.empty()) {
            Patient topPatient = pq.top();
            pq.pop();
            cout << "Serving Patient: " << topPatient.name << " (Priority: " << topPatient.priority << ")" << endl;
        } else {
            cout << "No patients to serve!" << endl;
        }
    }

    bool isEmpty() {
        return pq.empty();
    }

    void displayQueue() {
        cout << "Patients in Queue (sorted by priority):" << endl;
        priority_queue<Patient> tempQueue = pq;
        while (!tempQueue.empty()) {
            Patient p = tempQueue.top();
            cout << p.name << " (Priority: " << p.priority << ")" << endl;
            tempQueue.pop();
        }
    }
};

int main() {
    HospitalQueue hospitalQueue;

    hospitalQueue.addPatient("John Doe", 1);  // Serious
    hospitalQueue.addPatient("Jane Smith", 2);  // Non-serious
    hospitalQueue.addPatient("Jack Black", 3);  // General checkup
    hospitalQueue.addPatient("Alice Green", 1);  // Serious
    hospitalQueue.addPatient("Bob White", 2);  // Non-serious

    hospitalQueue.displayQueue();

    cout << "\nServing Patients in order of priority:\n";
    while (!hospitalQueue.isEmpty()) {
        hospitalQueue.servePatient();
    }

    return 0;
}
