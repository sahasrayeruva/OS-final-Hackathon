#include <string.h>
#ifndef HISTORY_H
#define HISTORY_H

#include <stdio.h>
#include <time.h>

void save_message(const char *username, const char *message) {
    FILE *file = fopen("chat_history.txt", "a");

    if (file == NULL) {
        perror("Error opening chat history");
        return;
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    char timestamp[20] = "unknown";

    if (t != NULL) {
        strftime(timestamp, sizeof(timestamp),
                 "%Y-%m-%d %H:%M:%S", t);
    }

    fprintf(file, "[%s] %s: %s", timestamp,
            username, message);

    size_t len = strlen(message);
    if (len == 0 || message[len - 1] != '\n')
        fprintf(file, "\n");

    fclose(file);
}

#endif
