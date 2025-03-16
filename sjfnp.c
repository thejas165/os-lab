#include <stdio.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
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
                (p[j].arrival_time == p[j + 1].arrival_time && p[j].burst_time > p[j + 1].burst_time)) {
                swap(&p[j], &p[j + 1]);
            }
        }
    }
}


void sjfScheduling(struct Process p[], int n) {
    int completed = 0, current_time = 0;
    float total_waiting_time = 0, total_turnaround_time = 0;

    while (completed < n) {
        int min_index = -1;
        int min_burst = 99999;

        
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && p[i].burst_time < min_burst && p[i].completion_time == 0) {
                min_burst = p[i].burst_time;
                min_index = i;
            }
        }

        if (min_index == -1) {
            current_time++; // No process arrived yet, increment time
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
        p[i].completion_time = 0; // Initialize completion time
    }

    // Sort processes based on arrival time
    sortProcesses(p, n);

    // Execute SJF Scheduling
    sjfScheduling(p, n);

    return 0;
}
