#include <stdio.h>

struct Process {
    int pid;
    int burst_time;
    int priority;
    int arrival_time;
    int waiting_time;
    int turnaround_time;
};

void findWaitingTime(struct Process proc[], int n, int bt[]) {
    int rt[n];
    for (int i = 0; i < n; i++)
        rt[i] = bt[i];

    int complete = 0, t = 0, minm = 9999;
    int shortest = 0;

    while (complete != n) {
        for (int j = 0; j < n; j++) {
            if ((proc[j].arrival_time <= t) && (rt[j] < minm) && rt[j] > 0) {
                minm = rt[j];
                shortest = j;
            }
        }

        rt[shortest]--;

        minm = 9999;

        if (rt[shortest] == 0) {
            complete++;
            proc[shortest].waiting_time = t - proc[shortest].arrival_time - bt[shortest];

            if (proc[shortest].waiting_time < 0) {
                proc[shortest].waiting_time = 0;
            }
        }
        t++;
    }
}

void findTurnAroundTime(struct Process proc[], int n) {
    for (int i = 0; i < n; i++)
        proc[i].turnaround_time = proc[i].burst_time + proc[i].waiting_time;
}

void findAverageTime(struct Process proc[], int n) {
    int total_waiting_time = 0, total_turnaround_time = 0;
    float avg_waiting_time, avg_turnaround_time;

    findWaitingTime(proc, n, proc[0].burst_time);
    findTurnAroundTime(proc, n);

    for (int i = 0; i < n; i++) {
        total_waiting_time = total_waiting_time + proc[i].waiting_time;
        total_turnaround_time = total_turnaround_time + proc[i].turnaround_time;
    }

    avg_waiting_time = (float)total_waiting_time / (float)n;
    avg_turnaround_time = (float)total_turnaround_time / (float)n;

    printf("\nAverage waiting time = %.2f\n", avg_waiting_time);
    printf("Average turnaround time = %.2f\n", avg_turnaround_time);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    for (int i = 0; i < n; i++) {
        printf("\nEnter Process[%d] details:\n", i + 1);
        printf("PID: ");
        scanf("%d", &proc[i].pid);
        printf("Burst Time: ");
        scanf("%d", &proc[i].burst_time);
        printf("Priority: ");
        scanf("%d", &proc[i].priority);
        printf("Arrival Time: ");
        scanf("%d", &proc[i].arrival_time);
    }

    findAverageTime(proc, n);

    return 0;
}
