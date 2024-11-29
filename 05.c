#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

void initializeInventory(char ***speciesSupplies, int *numSupplies, int numSpecies);
void addSupplies(char ***speciesSupplies, int *numSupplies, int numSpecies);
void updateSupplies(char ***speciesSupplies, int *numSupplies, int numSpecies);
void removeSpecies(char ***speciesSupplies, int *numSupplies, int *numSpecies);
void displayInventory(char *speciesNames, char **speciesSupplies, int *numSupplies, int numSpecies);

int main() {
    int numSpecies;
    printf("Enter the number of species: ");
    scanf("%d", &numSpecies);

    char *speciesNames = (char *)malloc(numSpecies * sizeof(char *));
    for (int i = 0; i < numSpecies; i++) {
        speciesNames[i] = (char *)malloc(MAX_NAME_LENGTH * sizeof(char));
        printf("Enter the name of species %d: ", i + 1);
        scanf("%s", speciesNames[i]);
    }

    char **speciesSupplies = (char *)malloc(numSpecies * sizeof(char *));
    int *numSupplies = (int *)malloc(numSpecies * sizeof(int));
    initializeInventory(speciesSupplies, numSupplies, numSpecies);

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Add Supplies\n");
        printf("2. Update Supplies\n");
        printf("3. Remove Species\n");
        printf("4. Display Inventory\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addSupplies(speciesSupplies, numSupplies, numSpecies);
                break;
            case 2:
                updateSupplies(speciesSupplies, numSupplies, numSpecies);
                break;
            case 3:
                removeSpecies(speciesSupplies, numSupplies, &numSpecies);
                break;
            case 4:
                displayInventory(speciesNames, speciesSupplies, numSupplies, numSpecies);
                break;
            case 5:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);

    for (int i = 0; i < numSpecies; i++) {
        for (int j = 0; j < numSupplies[i]; j++) {
            free(speciesSupplies[i][j]);
        }
        free(speciesSupplies[i]);
        free(speciesNames[i]);
    }
    free(speciesSupplies);
    free(speciesNames);
    free(numSupplies);

    return 0;
}

void initializeInventory(char ***speciesSupplies, int *numSupplies, int numSpecies) {
    for (int i = 0; i < numSpecies; i++) {
        speciesSupplies[i] = NULL; // No supplies initially
        numSupplies[i] = 0;
    }
}

void addSupplies(char ***speciesSupplies, int *numSupplies, int numSpecies) {
    int speciesIndex;
    printf("Enter the species index (0 to %d): ", numSpecies - 1);
    scanf("%d", &speciesIndex);

    if (speciesIndex < 0 || speciesIndex >= numSpecies) {
        printf("Invalid species index!\n");
        return;
    }

    int newSupplies;
    printf("Enter the number of new supplies to add: ");
    scanf("%d", &newSupplies);

    speciesSupplies[speciesIndex] = (char **)realloc(speciesSupplies[speciesIndex],
                                                    (numSupplies[speciesIndex] + newSupplies) * sizeof(char *));
    for (int i = 0; i < newSupplies; i++) {
        speciesSupplies[speciesIndex][numSupplies[speciesIndex] + i] = (char *)malloc(MAX_NAME_LENGTH * sizeof(char));
        printf("Enter name of supply %d: ", i + 1);
        scanf("%s", speciesSupplies[speciesIndex][numSupplies[speciesIndex] + i]);
    }
    numSupplies[speciesIndex] += newSupplies;
}

void updateSupplies(char ***speciesSupplies, int *numSupplies, int numSpecies) {
    int speciesIndex, supplyIndex;
    printf("Enter the species index (0 to %d): ", numSpecies - 1);
    scanf("%d", &speciesIndex);

    if (speciesIndex < 0 || speciesIndex >= numSpecies || numSupplies[speciesIndex] == 0) {
        printf("Invalid species index or no supplies available!\n");
        return;
    }

    printf("Enter the supply index (0 to %d): ", numSupplies[speciesIndex] - 1);
    scanf("%d", &supplyIndex);

    if (supplyIndex < 0 || supplyIndex >= numSupplies[speciesIndex]) {
        printf("Invalid supply index!\n");
        return;
    }

    printf("Enter the new name for supply: ");
    scanf("%s", speciesSupplies[speciesIndex][supplyIndex]);
}

void removeSpecies(char ***speciesSupplies, int *numSupplies, int *numSpecies) {
    int speciesIndex;
    printf("Enter the species index (0 to %d) to remove: ", *numSpecies - 1);
    scanf("%d", &speciesIndex);

    if (speciesIndex < 0 || speciesIndex >= *numSpecies) {
        printf("Invalid species index!\n");
        return;
    }

    for (int i = 0; i < numSupplies[speciesIndex]; i++) {
        free(speciesSupplies[speciesIndex][i]);
    }
    free(speciesSupplies[speciesIndex]);

    for (int i = speciesIndex; i < *numSpecies - 1; i++) {
        speciesSupplies[i] = speciesSupplies[i + 1];
        numSupplies[i] = numSupplies[i + 1];
    }
    (*numSpecies)--;
}

void displayInventory(char *speciesNames, char **speciesSupplies, int *numSupplies, int numSpecies) {
    for (int i = 0; i < numSpecies; i++) {
        printf("\nSpecies: %s\n", speciesNames[i]);
        printf("Supplies:\n");
        for (int j = 0; j < numSupplies[i]; j++) {
            printf("- %s\n", speciesSupplies[i][j]);
        }
    }
}
