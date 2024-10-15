#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Process {
    int id;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
};

// FCFS Scheduling
void fcfs(vector<Process> &processes) {
    int n = processes.size();
    processes[0].waiting_time = 0;
    for (int i = 1; i < n; i++) {
        processes[i].waiting_time = processes[i - 1].waiting_time + processes[i - 1].burst_time;
    }
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
    }
}

// SJF Scheduling
void sjf(vector<Process> &processes) {
    int n = processes.size();
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.burst_time < b.burst_time;
    });
    fcfs(processes);
}

// Priority Scheduling
void priorityScheduling(vector<Process> &processes) {
    int n = processes.size();
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.priority < b.priority;
    });
    fcfs(processes);
}

// Round Robin Scheduling
void roundRobin(vector<Process> &processes, int quantum) {
    int n = processes.size();
    vector<int> remaining_time(n);
    for (int i = 0; i < n; i++) {
        remaining_time[i] = processes[i].burst_time;
    }
    
    int t = 0; // Current time
    while (true) {
        bool done = true;
        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                done = false;
                if (remaining_time[i] > quantum) {
                    t += quantum;
                    remaining_time[i] -= quantum;
                } else {
                    t += remaining_time[i];
                    processes[i].waiting_time = t - processes[i].burst_time;
                    remaining_time[i] = 0;
                }
            }
        }
        if (done) break; // All processes are done
    }
    
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
    }
}

// Calculate average times
void calculateAverageTimes(vector<Process> &processes) {
    int n = processes.size();
    double total_waiting_time = 0, total_turnaround_time = 0;
    
    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }
    
    cout << fixed << setprecision(2);
    cout << "Average Waiting Time: " << total_waiting_time / n << endl;
    cout << "Average Turnaround Time: " << total_turnaround_time / n << endl;
}

// Print Gantt Chart
void printGanttChart(const vector<Process> &processes) {
    int n = processes.size();
    cout << "Gantt Chart: ";
    for (int i = 0; i < n; i++) {
        cout << "| P" << processes[i].id << " ";
    }
    cout << "|" << endl;

    cout << "Time: ";
    int time = 0;
    for (int i = 0; i < n; i++) {
        cout << time << " ";
        time += processes[i].burst_time;
    }
    cout << time << endl;
}

int main() {
    vector<Process> processes = {
        {1, 10, 2, 0, 0}, 
        {2, 5, 1, 0, 0}, 
        {3, 8, 3, 0, 0}
    };

    cout << "FCFS Scheduling:\n";
    fcfs(processes);
    printGanttChart(processes);
    calculateAverageTimes(processes);

    cout << "\nSJF Scheduling:\n";
    sjf(processes);
    printGanttChart(processes);
    calculateAverageTimes(processes);

    cout << "\nPriority Scheduling:\n";
    priorityScheduling(processes);
    printGanttChart(processes);
    calculateAverageTimes(processes);

    cout << "\nRound Robin Scheduling (Quantum = 3):\n";
    roundRobin(processes, 3);
    printGanttChart(processes);
    calculateAverageTimes(processes);

    return 0;
}
