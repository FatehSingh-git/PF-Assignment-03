#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int validateEmail(char *email) {
    int atCount = 0, dotAfterAt = 0;
    int atPosition = -1;

    if (email == NULL || strlen(email) == 0) {
        return 0; 
    }

    for (int i = 0; email[i] != '\0'; i++) {
        if (email[i] == '@') {
            atCount++;
            atPosition = i;
        }
        if (atCount == 1 && email[i] == '.' && i > atPosition) {
            dotAfterAt = 1;
        }
    }

    return (atCount == 1 && dotAfterAt == 1);
}

int main() {
    char *email;
    int size;

    printf("Enter the size of your email address: ");
    scanf("%d", &size);
    email = (char *)malloc((size + 1) * sizeof(char));

    if (email == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Enter your email address: ");
    scanf(" %[^\n]", email);

    if (validateEmail(email)) {
        printf("Valid Email\n");
    } else {
        printf("Invalid Email\n");
    }

    free(email);

    return 0;
}

