#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MIN_TEMP 20
#define MAX_TEMP 80
#define TOTAL_READINGS 10
#define SPIKE_LIMIT 15.0

struct Sensor {
    int id;
    float temperature;
    int status;                 // 1 = PASS, 0 = FAIL
    char reason[20];             // NONE, OUT_OF_RANGE, SPIKE
};

float generateTemperature() {
    return (rand() % 100);       // 0–99
}

void evaluateSensor(struct Sensor *current, struct Sensor *previous) {
    // Check range
    if (current->temperature < MIN_TEMP || current->temperature > MAX_TEMP) {
        current->status = 0;
        sprintf(current->reason, "OUT_OF_RANGE");
        return;
    }

    // Check spike (if previous exists)
    if (previous != NULL) {
        float diff = fabs(current->temperature - previous->temperature);
        if (diff > SPIKE_LIMIT) {
            current->status = 0;
            sprintf(current->reason, "SPIKE_DETECTED");
            return;
        }
    }

    // Otherwise pass
    current->status = 1;
    sprintf(current->reason, "NONE");
}

int main() {
    struct Sensor sensors[TOTAL_READINGS];
    FILE *file;

    srand(time(NULL));

    file = fopen("sensor_data.csv", "w");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    fprintf(file, "ID,Temperature,Status,Reason\n");

    for (int i = 0; i < TOTAL_READINGS; i++) {
        sensors[i].id = i + 1;
        sensors[i].temperature = generateTemperature();

        if (i == 0)
            evaluateSensor(&sensors[i], NULL);
        else
            evaluateSensor(&sensors[i], &sensors[i - 1]);

        fprintf(file, "%d,%.2f,%s,%s\n",
                sensors[i].id,
                sensors[i].temperature,
                sensors[i].status ? "PASS" : "FAIL",
                sensors[i].reason);
    }

    fclose(file);

    printf("Sensor data with spike detection written to sensor_data.csv\n");
    return 0;
}
