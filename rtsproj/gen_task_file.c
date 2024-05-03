#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Task structure representing tasks in a flight cockpit
typedef struct {
    int id;          // Task ID
    char operation[100]; // Description of the task operation
    int criticality; // Criticality level (1 to 5)
    int execution_time; // Execution time (in seconds)
    int deadline;    // Deadline (in seconds)
} Task;

// Function to generate a random task
Task generate_random_task(int id) {
    Task task;
    char *operations[] = {"Sensor Reading: Altitude", "Control Input: Throttle Adjustment",
                          "System Check: Fuel Level", "Warning: Airspeed Low",
                          "Navigation Update: Waypoint Adjustment"};
    int num_operations = sizeof(operations) / sizeof(operations[0]);
    
    task.id = id;
    sprintf(task.operation, "%s", operations[rand() % num_operations]);
    task.criticality = rand() % 5 + 1;
    task.execution_time = rand() % 5 + 1;
    task.deadline = rand() % 15 + 1;
    
    return task;
}

int main() {
    srand(time(NULL)); // Seed the random number generator

    int num_tasks = rand() % 20 + 1; // Generate a random number of tasks (1 to 20)

    FILE *file = fopen("output_tasks.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    // Write number of tasks to file
    fprintf(file, "%d\n", num_tasks);

    // Generate and write tasks to file
    for (int i = 0; i < num_tasks; i++) {
        Task task = generate_random_task(i + 1);
        fprintf(file, "%d %s %d %d %d\n", task.id, task.operation, task.criticality, task.execution_time, task.deadline);
    }

    fclose(file);
    printf("Tasks generated and written to output_tasks.txt.\n");

    return 0;
}
