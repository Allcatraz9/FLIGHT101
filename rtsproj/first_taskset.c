#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include <stdlib.h>

// Flight Control Task
void flight_control_task(void *pvParameters) {
  while (1) {
    printf("Executing flight control task...\n");

    printf("Adjusting flight control surfaces...\n");

    printf("Checking for emergencies...\n");

    vTaskDelay(pdMS_TO_TICKS(10)); // Delay for 10 milliseconds
  }
}

// Navigation Task
void navigation_task(void *pvParameters) {
  while (1) {
    printf("Executing navigation task...\n");

    printf("Calculating current position and route...\n");

    printf("Monitoring GPS signals...\n");

    vTaskDelay(pdMS_TO_TICKS(100)); // Delay for 100 milliseconds
  }
}

void communication_task(void *pvParameters) {
  while (1) {
    // Simulate communication system logic
    printf("Executing communication task...\n");

    // Example: Check for loss of communication with ground control
    int lost_connection = rand() % 10 == 0; // Simulate a 10% chance of losing connection
    if (lost_connection) {
      printf("Lost communication with ground control. Initiating reconnection...\n");

      // Create a new task to handle reconnection
      // xTaskCreate(reconnection_task, "ReconnectionTask", configMINIMAL_STACK_SIZE, NULL, PRIORITY_HIGH, NULL);
    }

    // Example: Handle other communication tasks
    printf("Handling communication with ground control and other aircraft...\n");
    printf("Managing data transmission/reception...\n");

    vTaskDelay(pdMS_TO_TICKS(50)); // Delay for 50 milliseconds
  }
}

// Reconnection Task
/* void reconnection_task(void *pvParameters) {
  printf("Reconnection task activated! Initiating reconnection procedures...\n");
  // Add reconnection procedures here
  vTaskDelay(pdMS_TO_TICKS(3000)); // Simulate reconnection procedures taking some time
  printf("Reconnection procedures completed.\n");

  // Task exits after completing reconnection procedures
  vTaskDelete(NULL);
} */

// Engine Control Task
void engine_control_task(void *pvParameters) {
  // Simulate initial engine startup procedure
  printf("Engine startup procedure initiated...\n");
  vTaskDelay(pdMS_TO_TICKS(2000)); // Delay for 2 seconds to simulate startup

  // Initialize engine parameters
  float throttle_position = 0.0;   // Initial throttle position
  float engine_temperature = 20.0; // Initial engine temperature in Celsius

  while (1) {
    // Simulate engine control logic
    printf("Executing engine control task...\n");

    // Example: Monitor engine parameters and adjust throttle settings
    // For demonstration purposes, let's simulate increasing throttle if temperature rises above 80 degrees Celsius
    if (engine_temperature > 80.0) {
      throttle_position += 5.0; // Increase throttle position by 5%
      printf("Engine temperature is high. Increasing throttle to cool down...\n");
    } else {
      // If temperature is within normal range, maintain throttle position
      printf("Engine temperature is normal. Maintaining current throttle position...\n");
    }

    // Simulate engine cooling over time
    engine_temperature -= 0.5; // Decrease temperature by 0.5 degrees Celsius per iteration

    // Example: Handle engine shutdown if temperature exceeds critical threshold
    if (engine_temperature > 100.0) {
      printf("Engine temperature critical. Initiating emergency engine shutdown...\n");
      // Additional actions for engine shutdown can be added here
      break; // Exit task loop to simulate engine shutdown
    }

    vTaskDelay(pdMS_TO_TICKS(500)); // Delay for 500 milliseconds between iterations
  }

  // Simulate engine shutdown completion
  printf("Engine shutdown completed.\n");

  // Task exits after engine shutdown
  vTaskDelete(NULL);
}

void emergency_task(void *pvParameters) {
  int emergency_level = *(int *)pvParameters;

  printf("Emergency task activated with level %d! Initiating emergency procedures...\n", emergency_level);

  // Perform emergency procedures based on the emergency level

  vTaskDelay(pdMS_TO_TICKS(5000)); // Simulate emergency procedures taking some time

  // Task exits after completing emergency procedures
  vTaskDelete(NULL);
}

// Altitude Monitoring Task
void altitude_monitoring_task(void *pvParameters) {
  while (1) {
    // Simulate altitude monitoring logic
    printf("Executing altitude monitoring task...\n");

    // Example: Check for sudden decrease in altitude
    int sudden_decrease = rand() % 100 == 0; // Simulate a 1% chance of sudden altitude decrease
    if (sudden_decrease) {
      printf("Sudden decrease in altitude detected. Initiating emergency descent procedures...\n");

      // Create a new emergency task with level 1
      int emergency_level = 1;
      xTaskCreate(emergency_task, "EmergencyTask1", configMINIMAL_STACK_SIZE, &emergency_level, PRIORITY_HIGH, NULL);
    }

    // Example: Read altitude data from sensors
    printf("Reading altitude data...\n");

    vTaskDelay(pdMS_TO_TICKS(200)); // Delay for 200 milliseconds
  }
}

// Sensor Monitoring Task
void sensor_monitoring_task(void *pvParameters) {
  while (1) {
    // Simulate sensor monitoring logic
    printf("Executing sensor monitoring task...\n");

    // Example: Read sensor data from various sensors (e.g., temperature, pressure)
    printf("Reading sensor data...\n");

    // Example: Perform health checks on sensors and raise alerts if needed
    printf("Performing health checks on sensors...\n");

    vTaskDelay(pdMS_TO_TICKS(50)); // Delay for 50 milliseconds
  }
}

// Autopilot Task
void autopilot_task(void *pvParameters) {
  while (1) {
    // Simulate autopilot logic
    printf("Executing autopilot task...\n");

    // Example: Implement autopilot control algorithms for navigation
    printf("Implementing autopilot control algorithms...\n");

    // Example: Handle mode changes and engage/disengage autopilot
    printf("Handling autopilot mode changes...\n");

    vTaskDelay(pdMS_TO_TICKS(100)); // Delay for 100 milliseconds
  }
}

// Fuel Monitoring Task (Shared Variable)
void fuel_monitoring_task(void *pvParameters) {
  float *fuel_level = (float *)pvParameters;

  while (1) {
    // Simulate fuel monitoring logic
    printf("Executing fuel monitoring task...\n");

    // Example: Check fuel level
    if (*fuel_level < 10.0) {
      printf("Low fuel level detected. Initiating emergency procedures...\n");
      // Additional actions for low fuel level can be added here
    }

    // Example: Read fuel level data from sensors
    printf("Reading fuel level data...\n");

    vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1 second between iterations
  }
}

// Fuel Flow Control Task
void fuel_flow_control_task(void *pvParameters) {
  float *fuel_level = (float *)pvParameters;

  while (1) {
    // Simulate fuel flow control logic
    printf("Executing fuel flow control task...\n");

    // Example: Adjust fuel flow based on fuel level
    if (*fuel_level < 50.0) {
      printf("Fuel level is low. Increasing fuel flow...\n");
      // Additional actions for adjusting fuel flow can be added here
    } else {
      printf("Fuel level is sufficient. Maintaining current fuel flow...\n");
    }

    vTaskDelay(pdMS_TO_TICKS(2000)); // Delay for 2 seconds between iterations
  }
}

//---------------------------------------------------------------//

// Shared structure to hold environmental parameters
typedef struct {
  float altitude;
  float airspeed;
  float cabin_pressure;
} EnvironmentParams;

// Altitude Monitoring Task
void altitude_monitoring_task_2(void *pvParameters) {
  EnvironmentParams *env_params = (EnvironmentParams *)pvParameters;

  while (1) {
    // Simulate altitude monitoring logic
    printf("Executing altitude monitoring task...\n");

    // Example: Check altitude
    if (env_params->altitude > 10000.0) {
      printf("High altitude detected. Adjusting cabin pressure...\n");
      // Additional actions for high altitude can be added here
      env_params->cabin_pressure += 5.0; // Increase cabin pressure
    }

    // Example: Read altitude data from sensors
    printf("Reading altitude data...\n");

    vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1 second between iterations
  }
}

// Airspeed Monitoring Task
void airspeed_monitoring_task(void *pvParameters) {
  EnvironmentParams *env_params = (EnvironmentParams *)pvParameters;

  while (1) {
    // Simulate airspeed monitoring logic
    printf("Executing airspeed monitoring task...\n");

    // Example: Check airspeed
    if (env_params->airspeed > 300.0) {
      printf("High airspeed detected. Adjusting altitude...\n");
      // Additional actions for high airspeed can be added here
      env_params->altitude -= 100.0; // Decrease altitude
    }

    // Example: Read airspeed data from sensors
    printf("Reading airspeed data...\n");

    vTaskDelay(pdMS_TO_TICKS(1500)); // Delay for 1.5 seconds between iterations
  }
}

// Cabin Pressure Control Task
void cabin_pressure_control_task(void *pvParameters) {
  EnvironmentParams *env_params = (EnvironmentParams *)pvParameters;

  while (1) {
    // Simulate cabin pressure control logic
    printf("Executing cabin pressure control task...\n");

    // Example: Adjust cabin pressure based on altitude
    if (env_params->altitude > 8000.0) {
      printf("High altitude detected. Increasing cabin pressure...\n");
      // Additional actions for increasing cabin pressure can be added here
      env_params->cabin_pressure += 10.0; // Increase cabin pressure
    }

    // Example: Read cabin pressure data from sensors
    printf("Reading cabin pressure data...\n");

    vTaskDelay(pdMS_TO_TICKS(2000)); // Delay for 2 seconds between iterations
  }
}

int main(void) {

  // Initial fuel level
  float fuel_level = 100.0; // Assume full tank initially

  // Initial environmental parameters
  EnvironmentParams env_params = {
      .altitude = 0.0,        // Initial altitude
      .airspeed = 250.0,      // Initial airspeed
      .cabin_pressure = 100.0 // Initial cabin pressure
  };
  // Create tasks for airplane control
  xTaskCreate(altitude_monitoring_task_2, "AltitudeMonitoring2", configMINIMAL_STACK_SIZE, &env_params, PRIORITY_MEDIUM,
              NULL);
  xTaskCreate(airspeed_monitoring_task, "AirspeedMonitoring", configMINIMAL_STACK_SIZE, &env_params, PRIORITY_HIGH,
              NULL);
  xTaskCreate(cabin_pressure_control_task, "CabinPressureControl", configMINIMAL_STACK_SIZE, &env_params, PRIORITY_LOW,
              NULL);
  xTaskCreate(fuel_monitoring_task, "FuelMonitoring", configMINIMAL_STACK_SIZE, &fuel_level, PRIORITY_MEDIUM, NULL);
  xTaskCreate(fuel_flow_control_task, "FuelFlowControl", configMINIMAL_STACK_SIZE, &fuel_level, PRIORITY_HIGH, NULL);
  xTaskCreate(flight_control_task, "FlightControl", configMINIMAL_STACK_SIZE, NULL, PRIORITY_HIGH, NULL);
  xTaskCreate(navigation_task, "Navigation", configMINIMAL_STACK_SIZE, NULL, PRIORITY_MEDIUM, NULL);
  xTaskCreate(communication_task, "Communication", configMINIMAL_STACK_SIZE, NULL, PRIORITY_LOW, NULL);
  xTaskCreate(engine_control_task, "EngineControl", configMINIMAL_STACK_SIZE, NULL, PRIORITY_HIGH, NULL);
  xTaskCreate(sensor_monitoring_task, "SensorMonitoring", configMINIMAL_STACK_SIZE, NULL, PRIORITY_MEDIUM, NULL);
  xTaskCreate(autopilot_task, "Autopilot", configMINIMAL_STACK_SIZE, NULL, PRIORITY_LOW, NULL);
  xTaskCreate(altitude_monitoring_task, "AltitudeMonitoring", configMINIMAL_STACK_SIZE, NULL, PRIORITY_MEDIUM, NULL);

  // Start FreeRTOS scheduler
  vTaskStartScheduler();

  // Should never reach here
  return 0;
}

