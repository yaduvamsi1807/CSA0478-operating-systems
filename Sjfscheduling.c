#include <stdio.h>

// Structure to hold process information
struct Process {
    int pid; // Process ID
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

// Function to find the process with the shortest burst time
int find_shortest_job(struct Process proc[], int n, int current_time) {
    int shortest = -1;
    for (int i = 0; i < n; i++) {
        if (proc[i].arrival_time <= current_time && proc[i].completion_time == 0) {
            if (shortest == -1 || proc[i].burst_time < proc[shortest].burst_time) {
                shortest = i;
            }
        }
    }
    return shortest;
}

// Function to calculate and print the results
void calculate_and_print(struct Process proc[], int n) {
    int total_turnaround_time = 0;
    int total_waiting_time = 0;

    for (int i = 0; i < n; i++) {
        proc[i].turnaround_time = proc[i].completion_time - proc[i].arrival_time;
        proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;

        total_turnaround_time += proc[i].turnaround_time;
        total_waiting_time += proc[i].waiting_time;
    }

    printf("\nProcess\t\tArrival Time\tBurst Time\tStart Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
               proc[i].pid, proc[i].arrival_time, proc[i].burst_time, proc[i].start_time, 
               proc[i].completion_time, proc[i].turnaround_time, proc[i].waiting_time);
    }

    printf("\nAverage Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter arrival time for P%d: ", i + 1);
        scanf("%d", &proc[i].arrival_time);
        printf("Enter burst time for P%d: ", i + 1);
        scanf("%d", &proc[i].burst_time);
        proc[i].start_time = 0;
        proc[i].completion_time = 0;
    }

    int current_time = 0;
    int completed = 0;

    while (completed != n) {
        int shortest = find_shortest_job(proc, n, current_time);

        if (shortest != -1) {
            proc[shortest].start_time = current_time;
            current_time += proc[shortest].burst_time;
            proc[shortest].completion_time = current_time;
            completed++;
        } else {
            current_time++; // Increment time if no process is available
        }
    }

    calculate_and_print(proc, n);

    return 0;
}
