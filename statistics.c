#include <stdio.h>
#include <stdlib.h>

double calculate_mean(const int values[], int n) {
    long sum = 0;
    for (int i = 0; i < n; i++) sum += values[i];
    return (double)sum / n;
}

void sort_values(int values[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (values[j] > values[j + 1]) {
                int temp = values[j];
                values[j] = values[j + 1];
                values[j + 1] = temp;
            }
        }
    }
}

double calculate_median(const int values[], int n) {
    int *copy = malloc((size_t)n * sizeof(int));
    if (copy == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++) copy[i] = values[i];
    sort_values(copy, n);
    double median;
    if (n % 2 == 1) median = copy[n / 2];
    else median = ((double)copy[n / 2 - 1] + copy[n / 2]) / 2.0;
    free(copy);
    return median;
}

void calculate_mode(const int values[], int n) {
    int *copy = malloc((size_t)n * sizeof(int));
    if (copy == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++) copy[i] = values[i];
    sort_values(copy, n);

    int max_count = 0;
    for (int i = 0; i < n;) {
        int j = i + 1;
        while (j < n && copy[j] == copy[i]) j++;
        if (j - i > max_count) max_count = j - i;
        i = j;
    }

    printf("Mode: ");
    int first = 1;
    for (int i = 0; i < n;) {
        int j = i + 1;
        while (j < n && copy[j] == copy[i]) j++;
        if (j - i == max_count) {
            if (!first) printf(", ");
            printf("%d", copy[i]);
            first = 0;
        }
        i = j;
    }
    printf("\n");
    free(copy);
}

int main(void) {
    int values[] = {4, 2, 7, 2, 9, 4, 2, 6};
    int n = (int)(sizeof(values) / sizeof(values[0]));
    printf("Values: 4, 2, 7, 2, 9, 4, 2, 6\n");
    printf("Mean: %.2f\n", calculate_mean(values, n));
    printf("Median: %.2f\n", calculate_median(values, n));
    calculate_mode(values, n);
    return 0;
}
