#include <stdio.h>

struct Process {
    int pid, arrival_time, burst_time, priority, waiting_time, turnaround_time, completion_time;
};

void swap(struct Process *a, struct Process *b) {
    struct Process temp = *a;
    *a = *b;
    *b = temp;
}

void sortProcesses(struct Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrival_time > p[j + 1].arrival_time ||
                (p[j].arrival_time == p[j + 1].arrival_time && p[j].priority > p[j + 1].priority)) {
                swap(&p[j], &p[j + 1]);
            }
        }
    }
}

void priorityScheduling(struct Process p[], int n) {
    int completed = 0, current_time = 0;
    float total_waiting_time = 0, total_turnaround_time = 0;

    while (completed < n) {
        int min_index = -1, highest_priority = 99999;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && p[i].priority < highest_priority && p[i].completion_time == 0) {
                highest_priority = p[i].priority;
                min_index = i;
            }
        }

        if (min_index == -1) {
            current_time++;
            continue;
        }

        p[min_index].completion_time = current_time + p[min_index].burst_time;
        p[min_index].turnaround_time = p[min_index].completion_time - p[min_index].arrival_time;
        p[min_index].waiting_time = p[min_index].turnaround_time - p[min_index].burst_time;

        total_waiting_time += p[min_index].waiting_time;
        total_turnaround_time += p[min_index].turnaround_time;

        current_time = p[min_index].completion_time;
        completed++;
    }

    printf("\nProcess\tAT\tBT\tPriority\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n", p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].priority, p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);
    }

    printf("\nAverage Waiting Time: %.2f", total_waiting_time / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_turnaround_time / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &p[i].arrival_time, &p[i].burst_time, &p[i].priority);
        p[i].completion_time = 0;
    }

    sortProcesses(p, n);
    priorityScheduling(p, n);

    return 0;
}
