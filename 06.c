#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char cropType[50];
    char growthStage[50];
    float expectedYield;
} Crop;

typedef struct {
    float temperature;
    float rainfall;
    float windSpeed;
} WeatherForecast;

typedef struct {
    char equipmentName[50];
    char operationalStatus[50];
    float fuelLevel;
    char activitySchedule[100];
} Equipment;

typedef struct {
    float soilNutrients;
    float pHLevel;
    int pestActivity;
} Sensor;

typedef struct {
    char GPS[50];
    float soilHealth;
    float moistureLevel;
    Crop *crops;
    int numCrops;
    WeatherForecast weather;
    Equipment *equipment;
    int numEquipment;
    Sensor *sensors;
    int numSensors;
} Field;

typedef struct {
    char hubName[50];
    Field *fields;
    int numFields;
} RegionalHub;

Field createField();
void displayField(Field field);
RegionalHub createRegionalHub();
void displayRegionalHub(RegionalHub hub);

int main() {
    int numHubs;
    printf("Enter the number of regional hubs: ");
    scanf("%d", &numHubs);

    RegionalHub *hubs = (RegionalHub *)malloc(numHubs * sizeof(RegionalHub));
    for (int i = 0; i < numHubs; i++) {
        printf("\nCreating Regional Hub %d\n", i + 1);
        hubs[i] = createRegionalHub();
    }

    printf("\nDisplaying all regional hubs and their details:\n");
    for (int i = 0; i < numHubs; i++) {
        displayRegionalHub(hubs[i]);
    }

    for (int i = 0; i < numHubs; i++) {
        for (int j = 0; j < hubs[i].numFields; j++) {
            free(hubs[i].fields[j].crops);
            free(hubs[i].fields[j].equipment);
            free(hubs[i].fields[j].sensors);
        }
        free(hubs[i].fields);
    }
    free(hubs);

    return 0;
}

Field createField() {
    Field field;

    printf("Enter GPS coordinates: ");
    scanf("%s", field.GPS);
    printf("Enter soil health: ");
    scanf("%f", &field.soilHealth);
    printf("Enter moisture level: ");
    scanf("%f", &field.moistureLevel);

    printf("Enter the number of crops: ");
    scanf("%d", &field.numCrops);
    field.crops = (Crop *)malloc(field.numCrops * sizeof(Crop));
    for (int i = 0; i < field.numCrops; i++) {
        printf("Enter crop %d type: ", i + 1);
        scanf("%s", field.crops[i].cropType);
        printf("Enter crop %d growth stage: ", i + 1);
        scanf("%s", field.crops[i].growthStage);
        printf("Enter crop %d expected yield: ", i + 1);
        scanf("%f", &field.crops[i].expectedYield);
    }

    printf("Enter temperature: ");
    scanf("%f", &field.weather.temperature);
    printf("Enter rainfall: ");
    scanf("%f", &field.weather.rainfall);
    printf("Enter wind speed: ");
    scanf("%f", &field.weather.windSpeed);

    printf("Enter the number of equipment: ");
    scanf("%d", &field.numEquipment);
    field.equipment = (Equipment *)malloc(field.numEquipment * sizeof(Equipment));
    for (int i = 0; i < field.numEquipment; i++) {
        printf("Enter equipment %d name: ", i + 1);
        scanf("%s", field.equipment[i].equipmentName);
        printf("Enter equipment %d operational status: ", i + 1);
        scanf("%s", field.equipment[i].operationalStatus);
        printf("Enter equipment %d fuel level: ", i + 1);
        scanf("%f", &field.equipment[i].fuelLevel);
        printf("Enter equipment %d activity schedule: ", i + 1);
        scanf("%s", field.equipment[i].activitySchedule);
    }

    printf("Enter the number of sensors: ");
    scanf("%d", &field.numSensors);
    field.sensors = (Sensor *)malloc(field.numSensors * sizeof(Sensor));
    for (int i = 0; i < field.numSensors; i++) {
        printf("Enter sensor %d soil nutrients: ", i + 1);
        scanf("%f", &field.sensors[i].soilNutrients);
        printf("Enter sensor %d pH level: ", i + 1);
        scanf("%f", &field.sensors[i].pHLevel);
        printf("Enter sensor %d pest activity: ", i + 1);
        scanf("%d", &field.sensors[i].pestActivity);
    }

    return field;
}

void displayField(Field field) {
    printf("GPS: %s\n", field.GPS);
    printf("Soil Health: %.2f\n", field.soilHealth);
    printf("Moisture Level: %.2f\n", field.moistureLevel);

    printf("Crops:\n");
    for (int i = 0; i < field.numCrops; i++) {
        printf("  Crop Type: %s, Growth Stage: %s, Expected Yield: %.2f\n",
               field.crops[i].cropType, field.crops[i].growthStage, field.crops[i].expectedYield);
    }

    printf("Weather Forecast: Temperature: %.2f, Rainfall: %.2f, Wind Speed: %.2f\n",
           field.weather.temperature, field.weather.rainfall, field.weather.windSpeed);

    printf("Equipment:\n");
    for (int i = 0; i < field.numEquipment; i++) {
        printf("  Name: %s, Status: %s, Fuel Level: %.2f, Schedule: %s\n",
               field.equipment[i].equipmentName, field.equipment[i].operationalStatus,
               field.equipment[i].fuelLevel, field.equipment[i].activitySchedule);
    }

    printf("Sensors:\n");
    for (int i = 0; i < field.numSensors; i++) {
        printf("  Soil Nutrients: %.2f, pH Level: %.2f, Pest Activity: %d\n",
               field.sensors[i].soilNutrients, field.sensors[i].pHLevel, field.sensors[i].pestActivity);
    }
}

RegionalHub createRegionalHub() {
    RegionalHub hub;

    printf("Enter regional hub name: ");
    scanf("%s", hub.hubName);

    printf("Enter the number of fields in this hub: ");
    scanf("%d", &hub.numFields);

    hub.fields = (Field *)malloc(hub.numFields * sizeof(Field));
    for (int i = 0; i < hub.numFields; i++) {
        printf("\nCreating Field %d\n", i + 1);
        hub.fields[i] = createField();
    }

    return hub;
}

void displayRegionalHub(RegionalHub hub) {
    printf("\nRegional Hub: %s\n", hub.hubName);
    for (int i = 0; i < hub.numFields; i++) {
        printf("\nField %d:\n", i + 1);
        displayField(hub.fields[i]);
    }
}
