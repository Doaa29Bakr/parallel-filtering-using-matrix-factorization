#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE_LEN 256
#define MAX_MOVIES 2000

int main() {
    // 1. Create an array to store movie titles
    char titles[MAX_MOVIES][MAX_TITLE_LEN];
    FILE *itemFile = fopen("ml-100k/u.item", "r");

    if (itemFile == NULL) {
        printf("Error: Could not open ml-100k/u.item\n");
        return 1;
    }

    // 2. Load u.item into the titles array
    char line[1024];
    while (fgets(line, sizeof(line), itemFile)) {
        int id;
        char title[MAX_TITLE_LEN];

        // Parse ID and Title (separated by '|')
        char *token = strtok(line, "|");
        if (token != NULL) {
            id = atoi(token);
            token = strtok(NULL, "|");
            if (token != NULL && id < MAX_MOVIES) {
                strncpy(titles[id], token, MAX_TITLE_LEN);
            }
        }
    }
    fclose(itemFile);

    // 3. Read movies.out and write to recommendations.txt
    FILE *outFile = fopen("movies.out", "r");
    FILE *reportFile = fopen("recommendations.txt", "w");

    if (outFile == NULL || reportFile == NULL) {
        printf("Error: Could not open movies.out or recommendations.txt\n");
        return 1;
    }

    int movie_idx;
    int user_id = 0;
    fprintf(reportFile, "User ID   | Recommended Movie Title\n");
    fprintf(reportFile, "-----------------------------------\n");

    while (fscanf(outFile, "%d", &movie_idx) != EOF) {
        // C code uses 0-indexed IDs, u.item uses 1-indexed IDs
        int movie_id = movie_idx + 1;
        if (movie_id < MAX_MOVIES) {
            fprintf(reportFile, "%-9d | %s\n", user_id, titles[movie_id]);
        }
        user_id++;
    }

    fclose(outFile);
    fclose(reportFile);
    printf("Success! Titles saved to recommendations.txt\n");

    return 0;
}