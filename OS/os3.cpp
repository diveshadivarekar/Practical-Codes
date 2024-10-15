#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <vector>

using namespace std;

mutex mtx; // Mutex for critical section
condition_variable cv; // Condition variable for signaling
int readers_count = 0; // Number of active readers
int waiting_writers = 0; // Number of waiting writers

// Function for readers
void reader(int id) {
    while (true) {
        // Start reading
        {
            unique_lock<mutex> lock(mtx);
            // Wait if there are writers waiting
            while (waiting_writers > 0) {
                cv.wait(lock);
            }
            readers_count++; // Increase count of readers
            cout << "Reader " << id << " is reading." << endl;
        }
        
        // Simulate reading time
        this_thread::sleep_for(chrono::milliseconds(100));
        
        // Finish reading
        {
            unique_lock<mutex> lock(mtx);
            readers_count--; // Decrease count of readers
            if (readers_count == 0) {
                cv.notify_all(); // Notify waiting writers
            }
            cout << "Reader " << id << " finished reading." << endl;
        }
        
        this_thread::sleep_for(chrono::milliseconds(100)); // Wait before next read
    }
}

// Function for writers
void writer(int id) {
    while (true) {
        // Start writing
        {
            unique_lock<mutex> lock(mtx);
            waiting_writers++; // Increase waiting writers count
            // Wait while there are active readers
            while (readers_count > 0) {
                cv.wait(lock);
            }
            waiting_writers--; // Decrease waiting writers count
            cout << "Writer " << id << " is writing." << endl;
        }

        // Simulate writing time
        this_thread::sleep_for(chrono::milliseconds(150));
        
        // Finish writing
        {
            unique_lock<mutex> lock(mtx);
            cv.notify_all(); // Notify all waiting readers and writers
            cout << "Writer " << id << " finished writing." << endl;
        }
        
        this_thread::sleep_for(chrono::milliseconds(100)); // Wait before next write
    }
}

int main() {
    const int num_readers = 3;
    const int num_writers = 2;

    vector<thread> readers, writers;

    // Create reader threads
    for (int i = 0; i < num_readers; ++i) {
        readers.emplace_back(reader, i + 1);
    }

    // Create writer threads
    for (int i = 0; i < num_writers; ++i) {
        writers.emplace_back(writer, i + 1);
    }

    // Join threads (not necessary here since threads run indefinitely)
    for (auto &r : readers) {
        r.join();
    }
    for (auto &w : writers) {
        w.join();
    }

    return 0;
}

