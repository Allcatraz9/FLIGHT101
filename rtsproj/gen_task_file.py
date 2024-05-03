import random

def uunifast(total_utilization, num_tasks):
    # Generate random utilizations
    utilizations = []
    sumU = total_utilization
    for i in range(1, num_tasks):
        next_sumU = sumU * random.random() ** (1 / (num_tasks - i))
        utilizations.append(sumU - next_sumU)
        sumU = next_sumU
    utilizations.append(sumU)

    return utilizations

def generate_taskset(num_tasks, total_utilization, max_period):
    taskset = []
    utilizations = uunifast(total_utilization, num_tasks)
    for i in range(num_tasks):
        period = random.randint(1, max_period)
        execution_time = random.randint(1, period) # Random execution time <= period
        deadline = random.randint(execution_time, period) # Random deadline between execution time and period
        taskset.append((i+1, f"Task {i+1}", utilizations[i], period, execution_time, deadline))
    return taskset

def save_taskset_to_file(taskset, filename):
    with open(filename, 'w') as file:
        file.write(f"{len(taskset)}\n")
        for task in taskset:
            file.write(f"{task[0]} {task[1]} {task[2]} {task[3]} {task[4]} {task[5]}\n")

if __name__ == "__main__":
    num_tasks = 10
    total_utilization = 0.8
    max_period = 100
    taskset = generate_taskset(num_tasks, total_utilization, max_period)
    save_taskset_to_file(taskset, "task_input.txt")
