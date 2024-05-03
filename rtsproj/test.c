#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For sleep function
#include <time.h>   // For time functions

typedef struct {
    int id;          // Task ID
    char operation[100]; // Description of the task operation
    int criticality; // Criticality level (1 to 5)
    int execution_time; // Execution time (in seconds)
    int deadline;    // Deadline (in seconds)
} Task;


// Function to swap two tasks
void swap(Task *a, Task *b) {
    Task temp = *a;
    *a = *b;
    *b = temp;
}

// Earliest Deadline First (EDF) scheduling algorithm
void edf_schedule(Task tasks[], int num_tasks) {
    // Sort tasks based on their deadlines (ascending order)
    for (int i = 0; i < num_tasks - 1; i++) {
        for (int j = 0; j < num_tasks - i - 1; j++) {
            if (tasks[j].deadline > tasks[j + 1].deadline) {
                swap(&tasks[j], &tasks[j + 1]);
            }
        }
    }

    // Schedule tasks with earliest deadlines first
    printf("Scheduling tasks with high criticality using EDF...\n");
    for (int i = 0; i < num_tasks; i++) {
        printf("Task %d (%s) scheduled with deadline %d\n", tasks[i].id, tasks[i].operation, tasks[i].deadline);
        // Simulate task execution
        sleep(tasks[i].execution_time); // Sleep for execution time
        printf("Task %d (%s) completed.\n", tasks[i].id, tasks[i].operation);
    }
    printf("\n");
}

// Rate Monotonic (RM) scheduling algorithm
void rm_schedule(Task tasks[], int num_tasks) {
    // Sort tasks based on their periods (execution times)
    for (int i = 0; i < num_tasks - 1; i++) {
        for (int j = 0; j < num_tasks - i - 1; j++) {
            if (tasks[j].execution_time > tasks[j + 1].execution_time) {
                swap(&tasks[j], &tasks[j + 1]);
            }
        }
    }

    // Schedule tasks with shorter periods (higher rates) first
    printf("Scheduling tasks with mid-level criticality using RM...\n");
    for (int i = 0; i < num_tasks; i++) {
        printf("Task %d (%s) scheduled with execution time %d\n", tasks[i].id, tasks[i].operation, tasks[i].execution_time);
        // Simulate task execution
        sleep(tasks[i].execution_time); // Sleep for execution time
        printf("Task %d (%s) completed.\n", tasks[i].id, tasks[i].operation);
    }
    printf("\n");
}

// Earliest Deadline Late (EDL) scheduling algorithm
void edl_schedule(Task tasks[], int num_tasks) {
    // Sort tasks based on their deadlines (descending order)
    for (int i = 0; i < num_tasks - 1; i++) {
        for (int j = 0; j < num_tasks - i - 1; j++) {
            if (tasks[j].deadline < tasks[j + 1].deadline) {
                swap(&tasks[j], &tasks[j + 1]);
            }
        }
    }

    // Schedule tasks with later deadlines first
    printf("Scheduling tasks with low criticality using EDL...\n");
    for (int i = 0; i < num_tasks; i++) {
        printf("Task %d (%s) scheduled with deadline %d\n", tasks[i].id, tasks[i].operation, tasks[i].deadline);
        // Simulate task execution
        sleep(tasks[i].execution_time); // Sleep for execution time
        printf("Task %d (%s) completed.\n", tasks[i].id, tasks[i].operation);
    }
    printf("\n");
}
Task* read_tasks_from_file(const char *filename, int *num_tasks) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    // Read number of tasks
    fscanf(file, "%d", num_tasks);
    Task *tasks = malloc(*num_tasks * sizeof(Task));
    if (tasks == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    // Read tasks from file
    for (int i = 0; i < *num_tasks; i++) {
        fscanf(file, "%d ", &tasks[i].id);
        fscanf(file, "%99[^0-9] ", tasks[i].operation);
        fscanf(file, "%d %d %d", &tasks[i].criticality, &tasks[i].execution_time, &tasks[i].deadline);
    }

    fclose(file);
    return tasks;
}
int main() {
    // Example tasks representing flight cockpit operations
    // Task tasks[] = {
    //     {1, "Sensor Reading: Altitude", 5, 1, 5},
    //     {2, "Control Input: Throttle Adjustment", 5, 2, 10},
    //     {3, "System Check: Fuel Level", 4, 3, 15},
    //     {4, "Warning: Airspeed Low", 4, 2, 8},
    //     {5, "Navigation Update: Waypoint Adjustment", 1, 3, 12}
    // };
 int num_tasks;
    Task *tasks = read_tasks_from_file("task_input.txt", &num_tasks);

    // Display tasks
    printf("Tasks from input file:\n");
    printf("Number of tasks: %d\n", num_tasks);
    printf("ID\tOperation\t\t\t\t\tCriticality\tExecution Time\tDeadline\n");
 for (int i = 0; i < num_tasks; i++) {
        printf("%-2d\t%-40s\t%d\t\t%d\t\t%d\n", tasks[i].id, tasks[i].operation, tasks[i].criticality, tasks[i].execution_time, tasks[i].deadline);
    }
    // int num_tasks = sizeof(tasks) / sizeof(tasks[0]);

    // Seed the random number generator
    srand(time(NULL));

    while (1) {
        // Randomly determine whether the alert sensor should become active
        int alert_sensor_active = rand() % 2; // Random number either 0 or 1
        if (alert_sensor_active) {
            printf("Alert sensor is now active. Eliminating lower criticality tasks.\n");
            // Eliminate lower criticality tasks
            for (int i = 0; i < num_tasks; i++) {
                if (tasks[i].criticality < 5) {
                    printf("Task %d (%s) eliminated.\n", tasks[i].id, tasks[i].operation);
                    // Set execution time of eliminated tasks to 0 to effectively remove them from scheduling
                    tasks[i].execution_time = 0;
                }
            }
       }

        // Schedule tasks based on criticality
        for (int i = 0; i < num_tasks; i++) {
            if (tasks[i].execution_time > 0) {
                if (tasks[i].criticality == 5 ) {
                    edf_schedule(&tasks[i], 1);
                } else if (tasks[i].criticality == 3) {
                    rm_schedule(&tasks[i], 1);
                } else if (tasks[i].criticality == 1) {
                    edl_schedule(&tasks[i], 1);
                }
            }
        }
    }

    //   for(int i = 0; i < num_tasks; i++) {
    //     free(tasks[i].operation);
    // }
    free(tasks);

    return 0;

}

