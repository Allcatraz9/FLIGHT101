import random

# Task structure representing tasks in a flight cockpit
class Task:
    def __init__(self, id, operation, criticality, execution_time, deadline):
        self.id = id
        self.operation = operation
        self.criticality = criticality
        self.execution_time = execution_time
        self.deadline = deadline

# Function to generate a random task
def generate_random_task(id):
    # List of possible task operations
    operations = ["Sensor Reading: Altitude", "Control Input: Throttle Adjustment",
                  "System Check: Fuel Level", "Warning: Airspeed Low",
                  "Navigation Update: Waypoint Adjustment"]
    operation = random.choice(operations)
    criticality = random.randint(1, 5) # Random criticality level (1 to 5)
    execution_time = random.randint(1, 5) # Random execution time (1 to 5 seconds)
    deadline = random.randint(1, 15) # Random deadline (1 to 15 seconds)
    return Task(id, operation, criticality, execution_time, deadline)

# Function to calculate total utilization of tasks
def calculate_utilization(tasks):
    total_utilization = sum(task.execution_time / task.deadline for task in tasks)
    return total_utilization

# Schedulability test for EDF and RM
def is_schedulable(tasks, threshold):
    total_utilization = calculate_utilization(tasks)
    return total_utilization <= threshold

# Main function
if __name__ == "__main__":
    # Example tasks for each criticality level
    tasks_c1_c2 = [Task(1, "Task1", 1, 1, 5), Task(2, "Task2", 2, 2, 10)]
    tasks_c3_c4 = [Task(3, "Task3", 3, 3, 15), Task(4, "Task4", 4, 2, 8)]
    tasks_c5 = [Task(5, "Task5", 5, 1, 5)]

    # EDF threshold = 1, RM threshold = 0.693 (for 2 tasks)
    threshold_edf = 1
    threshold_rm = 0.693

    # Check schedulability for each criticality level
    schedulable_c1_c2 = is_schedulable(tasks_c1_c2, threshold_edf)
    schedulable_c3_c4 = is_schedulable(tasks_c3_c4, threshold_rm)
    schedulable_c5 = is_schedulable(tasks_c5, 1) # No specific threshold for EDL

    print("Schedulability Analysis:")
    print("Criticality 1 and 2 tasks:", "Schedulable" if schedulable_c1_c2 else "Not Schedulable")
    print("Criticality 3 and 4 tasks:", "Schedulable" if schedulable_c3_c4 else "Not Schedulable")
    print("Criticality 5 tasks:", "Schedulable" if schedulable_c5 else "Not Schedulable")
    sum = 0
    if schedulable_c1_c2 and schedulable_c3_c4 and schedulable_c5:
        # Generate random number of tasks (increase upper limit for more tasks) and write them to a file
        num_tasks = random.randint(1, 20) # Random number of tasks (1 to 20)
        with open("task_input.txt", "w") as file:
            file.write(str(num_tasks) + "\n") # Write number of tasks to file
            for i in range(num_tasks):
                task = generate_random_task(i + 1)
               
                file.write(f"{task.id} {task.operation} {task.criticality} {task.execution_time} {task.deadline}\n")

        print("Task input file generated successfully.")
    else:
        print("Tasks cannot be scheduled. Skipping task file generation.")
