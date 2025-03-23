#include <stdio.h>

struct Process {
    int pid, arrival_time, burst_time, remaining_time, completion_time, turnaround_time, waiting_time;
};

void roundRobinScheduling(struct Process p[], int n, int time_quantum) {
    int completed = 0, current_time = 0, queue[n], front = 0, rear = 0;
    float total_waiting_time = 0, total_turnaround_time = 0;

    for (int i = 0; i < n; i++)
        p[i].remaining_time = p[i].burst_time;

    int isInQueue[n];
    for (int i = 0; i < n; i++)
        isInQueue[i] = 0;

    queue[rear++] = 0;
    isInQueue[0] = 1;

    while (completed < n) {
        int index = queue[front++];

        if (p[index].remaining_time > time_quantum) {
            current_time += time_quantum;
            p[index].remaining_time -= time_quantum;
        } else {
            current_time += p[index].remaining_time;
            p[index].completion_time = current_time;
            p[index].turnaround_time = p[index].completion_time - p[index].arrival_time;
            p[index].waiting_time = p[index].turnaround_time - p[index].burst_time;
            total_waiting_time += p[index].waiting_time;
            total_turnaround_time += p[index].turnaround_time;
            p[index].remaining_time = 0;
            completed++;
        }

        for (int i = 1; i < n; i++) {
            if (p[i].arrival_time <= current_time && p[i].remaining_time > 0 && !isInQueue[i]) {
                queue[rear++] = i;
                isInQueue[i] = 1;
            }
        }

        if (p[index].remaining_time > 0)
            queue[rear++] = index;
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);
    }

    printf("\nAverage Waiting Time: %.2f", total_waiting_time / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_turnaround_time / n);
}

int main() {
    int n, time_quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);
    }

    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);

    roundRobinScheduling(p, n, time_quantum);

    return 0;
}
