
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int choice;

    while (1) {
        printf("\n================================\n");
        printf("   INTER-PROCESS CHAT SYSTEM\n");
        printf("================================\n");
        printf("1. Start User A\n");
        printf("2. Start User B\n");
        printf("3. View Chat History\n");
        printf("4. Clear Chat History\n");
        printf("5. Exit Menu\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            return 1;
        }

        switch (choice) {
            case 1:
                printf("Starting User A...\n");
                system("./chat A");
                break;

            case 2:
                printf("Starting User B...\n");
                system("./chat B");
                break;

            case 3:
                system("./history_viewer");
                break;

            case 4: {
                char confirm;
                printf("Clear all chat history? (y/n): ");
                scanf(" %c", &confirm);

                if (confirm == 'y' || confirm == 'Y') {
                    FILE *file = fopen("chat_history.txt", "w");

                    if (file == NULL) {
                        perror("Unable to clear history");
                    } else {
                        fclose(file);
                        printf("Chat history cleared.\n");
                    }
                } else {
                    printf("Operation cancelled.\n");
                }
                break;
            }

            case 5:
                printf("Exiting menu. Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}
