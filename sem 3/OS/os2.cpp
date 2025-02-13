#include <iostream>
#include <thread>
#include <semaphore.h>
#include <vector>
#include <mutex>
#include <chrono>

using namespace std;

const int BUFFER_SIZE = 5; // Size of the buffer
vector<int> buffer(BUFFER_SIZE); // Shared buffer
int count = 0; // Current number of items in the buffer

sem_t empty; // Semaphore to count empty slots
sem_t full;  // Semaphore to count full slots
mutex mtx;   // Mutex for critical section

// Producer function
void producer(int id) {
    for (int i = 0; i < 10; ++i) {
        this_thread::sleep_for(chrono::milliseconds(100)); // Simulate production time

        int item = rand() % 100; // Produce an item
        sem_wait(&empty); // Wait for an empty slot
        mtx.lock(); // Lock the buffer
        buffer[count++] = item; // Add item to buffer
        cout << "Producer " << id << " produced: " << item << endl;
        mtx.unlock(); // Unlock the buffer
        sem_post(&full); // Signal that a new item is available
    }
}

// Consumer function
void consumer(int id) {
    for (int i = 0; i < 10; ++i) {
        this_thread::sleep_for(chrono::milliseconds(150)); // Simulate consumption time

        sem_wait(&full); // Wait for a full slot
        mtx.lock(); // Lock the buffer
        int item = buffer[--count]; // Remove item from buffer
        cout << "Consumer " << id << " consumed: " << item << endl;
        mtx.unlock(); // Unlock the buffer
        sem_post(&empty); // Signal that a new empty slot is available
    }
}

int main() {
    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE); // All slots are initially empty
    sem_init(&full, 0, 0); // No slots are initially full

    const int num_producers = 2;
    const int num_consumers = 2;

    // Create producer and consumer threads
    vector<thread> producers, consumers;
    for (int i = 0; i < num_producers; ++i) {
        producers.emplace_back(producer, i + 1);
    }
    for (int i = 0; i < num_consumers; ++i) {
        consumers.emplace_back(consumer, i + 1);
    }

    // Join threads
    for (auto &prod : producers) {
        prod.join();
    }
    for (auto &cons : consumers) {
        cons.join();
    }

    // Destroy semaphores
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
