#include <stdio.h>
#include <stdlib.h>

// Structure to represent a process
struct Process {
    int pid; // Process ID
    int burst_time; // Burst time of the process
};

// Function to find the process with the smallest burst time
int find_shortest_job(struct Process proc, int n, int completed) {
    int min_time = 9999; // Initialize with a large value
    int shortest_job_index = -1;

    for (int i = 0; i < n; i++) {
        if (completed[i] == 0 && proc[i].burst_time < min_time) {
            min_time = proc[i].burst_time;
            shortest_job_index = i;
        }
    }

    return shortest_job_index;
}

// Function to implement SJF scheduling
void sjf_scheduling(struct Process proc, int n) {
    int completed[n]; // Array to keep track of completed processes
    int current_time = 0;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    // Initialize completed array
    for (int i = 0; i < n; i++) {
        completed[i] = 0;
    }

    printf("\nProcess\t\tBurst Time\tWaiting Time\tTurnaround Time\n");

    // Keep scheduling until all processes are completed
    while (1) {
        int shortest_job_index = find_shortest_job(proc, n, completed);

        if (shortest_job_index == -1) {
            break; // All processes are completed
        }

        // Execute the process
        current_time += proc[shortest_job_index].burst_time;

        // Calculate waiting time and turnaround time
        int waiting_time = current_time - proc[shortest_job_index].burst_time;
        int turnaround_time = current_time;

        // Update total waiting time and turnaround time
        total_waiting_time += waiting_time;
        total_turnaround_time += turnaround_time;

        printf("%d\t\t%d\t\t%d\t\t%d\n", proc[shortest_job_index].pid, 
               proc[shortest_job_index].burst_time, waiting_time, turnaround_time);

        // Mark the process as completed
        completed[shortest_job_index] = 1;
    }

    // Calculate and print average waiting time and turnaround time
    float avg_waiting_time = (float)total_waiting_time / n;
    float avg_turnaround_time = (float)total_turnaround_time / n;

    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &proc[i].burst_time);
    }

    sjf_scheduling(proc, n);

    return 0;
}
