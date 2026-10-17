#include "history.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>

#define PIPE_AB "/tmp/userA_to_userB"
#define PIPE_BA "/tmp/userB_to_userA"
#define SIZE 512

int main(int argc, char *argv[]) {
    if (argc != 2 ||
        (strcmp(argv[1], "A") != 0 &&
         strcmp(argv[1], "B") != 0)) {
        printf("Usage: %s A or %s B\n", argv[0]);
        return 1;
    }

    int isA = strcmp(argv[1], "A") == 0;
    const char *user = isA ? "User A" : "User B";

    signal(SIGPIPE, SIG_IGN);

    if (mkfifo(PIPE_AB, 0666) == -1 &&
        access(PIPE_AB, F_OK) == -1) {
        perror("mkfifo");
        return 1;
    }

    if (mkfifo(PIPE_BA, 0666) == -1 &&
        access(PIPE_BA, F_OK) == -1) {
        perror("mkfifo");
        return 1;
    }

    printf("%s: Waiting for the other user...\n", user);
    fflush(stdout);

    int outgoing, incoming;

    if (isA) {
        outgoing = open(PIPE_AB, O_WRONLY);
        if (outgoing == -1) {
            perror("open outgoing");
            return 1;
        }
        incoming = open(PIPE_BA, O_RDONLY);
    } else {
        incoming = open(PIPE_AB, O_RDONLY);
        if (incoming == -1) {
            perror("open incoming");
            return 1;
        }
        outgoing = open(PIPE_BA, O_WRONLY);
    }

    if (incoming == -1 || outgoing == -1) {
        perror("open pipe");
        if (incoming != -1) close(incoming);
        if (outgoing != -1) close(outgoing);
        return 1;
    }

    printf("Connected! Type /exit to leave.\n\n");
    fflush(stdout);

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        close(incoming);
        close(outgoing);
        return 1;
    }

    if (pid == 0) {
        char buffer[SIZE];
        ssize_t n;

        while ((n = read(incoming, buffer, SIZE - 1)) > 0) {
            buffer[n] = '\0';

            if (strcmp(buffer, "/exit\n") == 0 ||
                strcmp(buffer, "/exit") == 0) {
                printf("\nOther user left the chat.\n");
                fflush(stdout);
                kill(getppid(), SIGTERM);
                break;
            }

            time_t now = time(NULL);
            struct tm *t = localtime(&now);
            char timestamp[16] = "";

            if (t)
                strftime(timestamp, sizeof(timestamp),
                         "%H:%M:%S", t);

            printf("\n[%s] %s: %s", timestamp,
                   isA ? "User B" : "User A", buffer);

            if (buffer[n - 1] != '\n')
                printf("\n");

            printf("You: ");
            fflush(stdout);
        }

        close(incoming);
        close(outgoing);
        _exit(0);
    }

    char message[SIZE];

    while (1) {
        printf("You: ");
        fflush(stdout);

        if (fgets(message, sizeof(message), stdin) == NULL)
            break;

        size_t len = strlen(message);
        if (strcmp(message, "/exit\n") != 0 &&
    strcmp(message, "/exit") != 0) {
    save_message(user, message);
}

        if (write(outgoing, message, len) == -1) {
            perror("write");
            break;
        }

        if (strcmp(message, "/exit\n") == 0 ||
            strcmp(message, "/exit") == 0)
            break;

        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        char timestamp[16] = "";

        if (t)
            strftime(timestamp, sizeof(timestamp),
                     "%H:%M:%S", t);

        printf("[%s] You: %s", timestamp, message);
        if (len > 0 && message[len - 1] != '\n')
            printf("\n");
    }

    close(outgoing);
    close(incoming);

    if (isA) {
        unlink(PIPE_AB);
        unlink(PIPE_BA);
    }

    kill(pid, SIGTERM);
    waitpid(pid, NULL, 0);

    printf("Chat ended.\n");
    return 0;
}
