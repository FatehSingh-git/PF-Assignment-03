#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char title[100];
    int runtime;
    char encodingFormat[50];
} ContentMetadata;

typedef struct {
    float engagementScore; 
} Engagement;

typedef struct {
    char resolution[20];
    char playbackHistory[200];
    float bandwidthUsage;
} DevicePreferences;

typedef struct {
    char username[50];
    Engagement **engagementMatrix; 
    DevicePreferences **deviceMatrix; 
    ContentMetadata **contentMatrix; 
} UserProfile;

UserProfile *createUserProfiles(int numUsers, int numCategories, int numDevices, int numContentPerCategory);
void updateEngagementScore(UserProfile *users, int userIndex, int categoryIndex, float newScore);
void displayUserProfile(UserProfile *users, int numUsers, int numCategories, int numDevices, int numContentPerCategory);
void freeMemory(UserProfile *users, int numUsers, int numCategories, int numDevices, int numContentPerCategory);

int main() {
    int numUsers, numCategories, numDevices, numContentPerCategory;

    printf("Enter the number of users: ");
    scanf("%d", &numUsers);
    printf("Enter the number of content categories: ");
    scanf("%d", &numCategories);
    printf("Enter the number of devices per user: ");
    scanf("%d", &numDevices);
    printf("Enter the number of content items per category: ");
    scanf("%d", &numContentPerCategory);

    UserProfile *users = createUserProfiles(numUsers, numCategories, numDevices, numContentPerCategory);

    updateEngagementScore(users, 0, 1, 9.5); 
    displayUserProfile(users, numUsers, numCategories, numDevices, numContentPerCategory);

    freeMemory(users, numUsers, numCategories, numDevices, numContentPerCategory);

    return 0;
}

UserProfile *createUserProfiles(int numUsers, int numCategories, int numDevices, int numContentPerCategory) {
    UserProfile *users = (UserProfile *)malloc(numUsers * sizeof(UserProfile));

    for (int i = 0; i < numUsers; i++) {
        printf("Enter username for user %d: ", i + 1);
        scanf("%s", users[i].username);

        users[i].engagementMatrix = (Engagement **)malloc(numCategories * sizeof(Engagement *));
        for (int j = 0; j < numCategories; j++) {
            users[i].engagementMatrix[j] = (Engagement *)malloc(sizeof(Engagement));
            users[i].engagementMatrix[j]->engagementScore = 0.0; // Initialize scores
        }

        users[i].deviceMatrix = (DevicePreferences **)malloc(numDevices * sizeof(DevicePreferences *));
        for (int j = 0; j < numDevices; j++) {
            users[i].deviceMatrix[j] = (DevicePreferences *)malloc(sizeof(DevicePreferences));
            strcpy(users[i].deviceMatrix[j]->resolution, "1080p");
            strcpy(users[i].deviceMatrix[j]->playbackHistory, "None");
            users[i].deviceMatrix[j]->bandwidthUsage = 0.0;
        }

        users[i].contentMatrix = (ContentMetadata **)malloc(numCategories * sizeof(ContentMetadata *));
        for (int j = 0; j < numCategories; j++) {
            users[i].contentMatrix[j] = (ContentMetadata *)malloc(numContentPerCategory * sizeof(ContentMetadata));
            for (int k = 0; k < numContentPerCategory; k++) {
                strcpy(users[i].contentMatrix[j][k].title, "Content Title");
                users[i].contentMatrix[j][k].runtime = 120; // Example runtime
                strcpy(users[i].contentMatrix[j][k].encodingFormat, "HD");
            }
        }
    }

    return users;
}

void updateEngagementScore(UserProfile *users, int userIndex, int categoryIndex, float newScore) {
    users[userIndex].engagementMatrix[categoryIndex]->engagementScore = newScore;
}

void displayUserProfile(UserProfile *users, int numUsers, int numCategories, int numDevices, int numContentPerCategory) {
    for (int i = 0; i < numUsers; i++) {
        printf("\nUser: %s\n", users[i].username);

        printf("Engagement Scores:\n");
        for (int j = 0; j < numCategories; j++) {
            printf("  Category %d: %.2f\n", j, users[i].engagementMatrix[j]->engagementScore);
        }

     
        printf("Device Preferences:\n");
        for (int j = 0; j < numDevices; j++) {
            printf("  Device %d: Resolution=%s, Playback History=%s, Bandwidth Usage=%.2f Mbps\n",
                   j, users[i].deviceMatrix[j]->resolution, users[i].deviceMatrix[j]->playbackHistory,
                   users[i].deviceMatrix[j]->bandwidthUsage);
        }

        printf("Content Metadata:\n");
        for (int j = 0; j < numCategories; j++) {
            printf("  Category %d:\n", j);
            for (int k = 0; k < numContentPerCategory; k++) {
                printf("    Title=%s, Runtime=%d mins, Format=%s\n",
                       users[i].contentMatrix[j][k].title, users[i].contentMatrix[j][k].runtime,
                       users[i].contentMatrix[j][k].encodingFormat);
            }
        }
    }
}

void freeMemory(UserProfile *users, int numUsers, int numCategories, int numDevices, int numContentPerCategory) {
    for (int i = 0; i < numUsers; i++) {
  
        for (int j = 0; j < numCategories; j++) {
            free(users[i].engagementMatrix[j]);
        }
        free(users[i].engagementMatrix);

        for (int j = 0; j < numDevices; j++) {
            free(users[i].deviceMatrix[j]);
        }
        free(users[i].deviceMatrix);

        for (int j = 0; j < numCategories; j++) {
            free(users[i].contentMatrix[j]);
        }
        free(users[i].contentMatrix);
    }
    free(users);
}
