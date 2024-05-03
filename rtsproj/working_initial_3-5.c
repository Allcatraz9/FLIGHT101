#include "FreeRTOS.h"
#include "task.h"
#include "timers.h" // Include Timer functionality
#include <stdio.h>
#include <stdlib.h>

// Define Task Structure
typedef struct {
  int id;
  int arrival_time;
  int processing_time;
  int deadline;
  int period; // Add a member for task period
  char criticality; // A, B, C, D, or E
} Task;

// Avionics Task Handler
void avionicsTaskHandler(void *pvParameters) {
  Task *task = (Task *)pvParameters;
  printf("Executing Avionics Task %d (Criticality: %c)...\n", task->id, task->criticality);
  // Simulate processing time
  vTaskDelay(pdMS_TO_TICKS(task->processing_time));
  // Check if the task missed its deadline
  if (xTaskGetTickCount() > pdMS_TO_TICKS(task->deadline)) {
    printf("Avionics Task %d missed its deadline!\n", task->id);
  }
  vTaskDelete(NULL); // Delete task after execution
}

// Timer callback function to execute the task
void timerCallback(TimerHandle_t xTimer) {
  Task *task = (Task *)pvTimerGetTimerID(xTimer);
  // Create the task with appropriate parameters
  xTaskCreate(avionicsTaskHandler, "AvionicsTask", configMINIMAL_STACK_SIZE, (void *)task, tskIDLE_PRIORITY, NULL);
  // Restart the timer with the task's period
  xTimerChangePeriod(xTimer, pdMS_TO_TICKS(task->period), 0);
}

int main() {
  // Specify the input file location
  const char *input_file = "/home/user/Documents/taskset.txt";

  // Read task parameters from the input file
  FILE *file = fopen(input_file, "r");
  if (file == NULL) {
    printf("Error: Unable to open input file %s.\n", input_file);
    return -1;
  }

  // Read number of tasks
  int num_tasks = 50; // Assuming a fixed number of tasks for now
  // If you want to dynamically determine the number of tasks, you can count the lines in the file

  // Allocate memory for tasks
  Task *avionics_tasks = (Task *)malloc(num_tasks * sizeof(Task));
  if (avionics_tasks == NULL) {
    printf("Error: Memory allocation failed.\n");
    fclose(file);
    return -1;
  }

  // Read task parameters
  for (int i = 0; i < num_tasks; i++) {
    if (fscanf(file, "%d, %d, %d, %d, %d, %c", &avionics_tasks[i].id, &avionics_tasks[i].arrival_time,
               &avionics_tasks[i].period, &avionics_tasks[i].processing_time, &avionics_tasks[i].deadline,
               &avionics_tasks[i].criticality) != 6) {
      printf("Error: Unable to read task parameters from input file.\n");
      free(avionics_tasks);
      fclose(file);
      return -1;
    }
  }

  // Close the file
  fclose(file);

  // Sort tasks based on arrival times
  for (int i = 0; i < num_tasks - 1; i++) {
    for (int j = 0; j < num_tasks - i - 1; j++) {
      if (avionics_tasks[j].arrival_time > avionics_tasks[j + 1].arrival_time) {
        Task temp = avionics_tasks[j];
        avionics_tasks[j] = avionics_tasks[j + 1];
        avionics_tasks[j + 1] = temp;
      }
    }
  }

  // Create software timers for each task
  for (int i = 0; i < num_tasks; i++) {
    TimerHandle_t xTimer = xTimerCreate("TaskTimer", pdMS_TO_TICKS(avionics_tasks[i].arrival_time), pdFALSE,
                                        (void *)&avionics_tasks[i], timerCallback);
    if (xTimer == NULL) {
      printf("Error: Unable to create timer for task %d.\n", avionics_tasks[i].id);
      // Handle error appropriately
    } else {
      xTimerStart(xTimer, 0); // Start the timer
    }
  }

  // Start FreeRTOS scheduler
  vTaskStartScheduler();

  // Free allocated memory
  free(avionics_tasks);

  return 0;
}

