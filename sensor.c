#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_TEMP 20
#define MAX_TEMP 80
#define TOTAL_READINGS 10

struct Sensor {
    int id;
    float temperature;
    int status;   // 1 = PASS, 0 = FAIL
};

float generateTemperature() {
    return (rand() % 100);   // 0 to 99
}

int checkStatus(float temp) {
    if (temp >= MIN_TEMP && temp <= MAX_TEMP)
        return 1;
    else
        return 0;
}

int main() {
    struct Sensor sensors[TOTAL_READINGS];
    FILE *file;

    srand(time(NULL));

    // Open file in write mode
    file = fopen("sensor_data.csv", "w");

    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Write CSV header
    fprintf(file, "SensorID,Temperature,Status\n");

    for (int i = 0; i < TOTAL_READINGS; i++) {
        sensors[i].id = i + 1;
        sensors[i].temperature = generateTemperature();
        sensors[i].status = checkStatus(sensors[i].temperature);

        // Write data to file
        fprintf(file, "%d,%.2f,%s\n",
                sensors[i].id,
                sensors[i].temperature,
                sensors[i].status ? "PASS" : "FAIL");
    }

    fclose(file);

    printf("Sensor data written to sensor_data.csv successfully.\n");

    return 0;
}
