#include <stdio.h>

// Function to find the greatest among n processes
int findGreatest(int bt[], int n) {
    int greatest = bt[0];
    for (int i = 1; i < n; i++) {
        if (bt[i] > greatest) {
            greatest = bt[i];
        }
    }
    return greatest;
}

// Function to calculate waiting time
void findWaitingTime(int processes[], int n, int bt[], int wt[], int quantum) {
    // Create a copy of burst times
    int rem_bt[n];
    for (int i = 0; i < n; i++) {
        rem_bt[i] = bt[i];
    }

    int t = 0; // Current time

    // Keep traversing processes in round robin manner
    // until all of them are not completed
    while (1) {
        // Traverse all processes one by one repeatedly
        bool done = true;
        for (int i = 0; i < n; i++) {
            if (rem_bt[i] > 0) {
                done = false;

                if (rem_bt[i] > quantum) {
                    t += quantum;
                    rem_bt[i] -= quantum;
                } else {
                    t += rem_bt[i];
                    wt[i] = t - bt[i];
                    rem_bt[i] = 0;
                }
            }
        }

        if (done == true) {
            break;
        }
    }
}

// Function to calculate turnaround time
void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    // Calculating turnaround time
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }
}

// Function to calculate average waiting and turnaround times
void findavgTime(int processes[], int n, int bt[], int quantum) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    // Function to find waiting time of all processes
    findWaitingTime(processes, n, bt, wt, quantum);

    // Function to find turnaround time for all processes
    findTurnAroundTime(processes, n, bt, wt, tat);

    // Display processes along with all details
    printf("\nProcess\t\tBurst Time\t\tWaiting Time\t\tTurnaround Time\n");

    // Calculate total waiting time and total turnaround time
    for (int i = 0; i < n; i++) {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        printf("   %d\t\t\t  %d\t\t\t    %d\t\t\t\t  %d\n", i + 1, bt[i], wt[i], tat[i]);
    }

    printf("Average waiting time = %.2f\n", (float)total_wt / (float)n);
    printf("Average turnaround time = %.2f\n", (float)total_tat / (float)n);
}

// Driver code
int main() {
    // Process IDs here should be 1, 2, 3, ..., n
    int processes[] = { 1, 2, 3 };
    int n = sizeof(processes) / sizeof(processes[0]);

    // Burst time of all processes
    int burst_time[] = { 10, 5, 8 };

    // Time quantum
    int quantum = 2;

    findavgTime(processes, n, burst_time, quantum);

    return 0;
}
