#include <stdio.h>
#include <string.h>

struct Player {
    int ballScores[12];
    char playerName[50];
    int totalScore;
};

int validateScore(int score) {
    if (score >= 0 && score <= 6) {
        return score;
    }
    printf("Invalid score! This ball is marked as zero.\n");
    return 0;
}

void playGame(struct Player *player) {
    player->totalScore = 0;
    printf("\nEnter scores for %s:\n", player->playerName);
    for (int i = 0; i < 12; i++) {
        printf("Ball %d: ", i + 1);
        int score;
        scanf("%d", &score);
        player->ballScores[i] = validateScore(score);
        player->totalScore += player->ballScores[i];
    }
}

void findWinner(struct Player player1, struct Player player2) {
    printf("\nMatch Result:\n");
    if (player1.totalScore > player2.totalScore) {
        printf("%s wins with %d runs!\n", player1.playerName, player1.totalScore);
    } else if (player2.totalScore > player1.totalScore) {
        printf("%s wins with %d runs!\n", player2.playerName, player2.totalScore);
    } else {
        printf("It's a tie with both scoring %d runs!\n", player1.totalScore);
    }
}

void displayMatchScoreboard(struct Player player1, struct Player player2) {
    printf("\nMatch Scoreboard:\n");
    printf("%s's Scores: ", player1.playerName);
    for (int i = 0; i < 12; i++) {
        printf("%d ", player1.ballScores[i]);
    }
    printf("\nTotal: %d\n", player1.totalScore);

    printf("%s's Scores: ", player2.playerName);
    for (int i = 0; i < 12; i++) {
        printf("%d ", player2.ballScores[i]);
    }
    printf("\nTotal: %d\n", player2.totalScore);
}

int main() {
    struct Player player1, player2;

    printf("Enter Player 1 Name: ");
    scanf(" %[^\n]", player1.playerName);
    printf("Enter Player 2 Name: ");
    scanf(" %[^\n]", player2.playerName);

    playGame(&player1);
    playGame(&player2);

    displayMatchScoreboard(player1, player2);
    findWinner(player1, player2);

    return 0;
}

