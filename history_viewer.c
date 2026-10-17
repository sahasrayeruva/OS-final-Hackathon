
#include <stdio.h>
#include <string.h>

#define HISTORY_FILE "chat_history.txt"
#define MAX_LINE 1024

int main(void) {
    FILE *file = fopen(HISTORY_FILE, "r");

    if (file == NULL) {
        printf("No chat history found yet.\n");
        return 1;
    }

    char line[MAX_LINE];
    int total = 0;
    int userA = 0;
    int userB = 0;

    printf("\n========== CHAT HISTORY ==========\n\n");

    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
        total++;

        if (strstr(line, "User A:") != NULL)
            userA++;
        else if (strstr(line, "User B:") != NULL)
            userB++;
    }

    fclose(file);

    printf("\n========== STATISTICS ==========\n");
    printf("Total messages : %d\n", total);
    printf("User A messages: %d\n", userA);
    printf("User B messages: %d\n", userB);
    printf("================================\n");

    return 0;
}
