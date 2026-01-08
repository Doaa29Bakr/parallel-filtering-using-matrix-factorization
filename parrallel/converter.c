#include <stdio.h>
#include <stdlib.h>

// Settings for your matrix factorization program
#define ITERATIONS 50
#define ALPHA 0.0001
#define FEATURES 10

typedef struct {
    int user;
    int item;
    double rate;
} Rating;

int main() {
    FILE *inputFile = fopen("ml-100k/u.data", "r");
    FILE *outputFile = fopen("movies.in", "w");

    if (inputFile == NULL) {
        printf("Error: Could not find 'ml-100k/u.data'. Ensure the folder is in your project directory.\n");
        return 1;
    }

    int u, i, ts;
    double r;
    int maxUser = 0;
    int maxItem = 0;
    int ratingCount = 0;

    // First pass: Count ratings and find maximum IDs for the header
    while (fscanf(inputFile, "%d %d %lf %d", &u, &i, &r, &ts) != EOF) {
        if (u > maxUser) maxUser = u;
        if (i > maxItem) maxItem = i;
        ratingCount++;
    }

    // Reset file pointer to the beginning to read data again
    rewind(inputFile);

    // Write the project-specific header
    fprintf(outputFile, "%d\n", ITERATIONS);
    fprintf(outputFile, "%f\n", ALPHA);
    fprintf(outputFile, "%d\n", FEATURES);
    // Note: MovieLens IDs start at 1, so maxUser/maxItem are the counts
    fprintf(outputFile, "%d %d %d\n", maxUser, maxItem, ratingCount);

    // Second pass: Write the data with 0-based indexing
    while (fscanf(inputFile, "%d %d %lf %d", &u, &i, &r, &ts) != EOF) {
        // Subtract 1 from IDs to convert to 0-based indexing for C arrays
        fprintf(outputFile, "%d %d %.1f\n", u - 1, i - 1, r);
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("Success! Created 'movies.in' with %d users, %d items, and %d ratings.\n",
            maxUser, maxItem, ratingCount);

    return 0;
}