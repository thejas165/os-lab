#include <stdio.h>

struct Process {
    int pid, arrival_time, burst_time, remaining_time, waiting_time, turnaround_time, completion_time;
};

void sjfPreemptive(struct Process p[], int n) {
    int completed = 0, current_time = 0, min_index = -1, min_burst = 99999;
    float total_waiting_time = 0, total_turnaround_time = 0;

    for (int i = 0; i < n; i++)
        p[i].remaining_time = p[i].burst_time;

    while (completed < n) {
        min_index = -1, min_burst = 99999;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && p[i].remaining_time > 0 && p[i].remaining_time < min_burst) {
                min_burst = p[i].remaining_time;
                min_index = i;
            }
        }

        if (min_index == -1) {
            current_time++;
            continue;
        }

        p[min_index].remaining_time--;
        current_time++;

        if (p[min_index].remaining_time == 0) {
            completed++;
            p[min_index].completion_time = current_time;
            p[min_index].turnaround_time = p[min_index].completion_time - p[min_index].arrival_time;
            p[min_index].waiting_time = p[min_index].turnaround_time - p[min_index].burst_time;

            total_waiting_time += p[min_index].waiting_time;
            total_turnaround_time += p[min_index].turnaround_time;
        }
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
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);
    }

    sjfPreemptive(p, n);

    return 0;
}
