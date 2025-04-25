#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int cmp(const void *a, const void *b) {
    int ia = *(int *)a;
    int ib = *(int *)b;
    return ia - ib;
}

int is_sorted(int *arr, int size) {
    for (int i = 1; i < size; i++) {
        if (arr[i - 1] > arr[i]) return 0;
    }
    return 1;
}

void generate_sorted(int *arr, int size) {
    for (int i = 0; i < size; i++)
        arr[i] = i;
}

void generate_reversed(int *arr, int size) {
    for (int i = 0; i < size; i++)
        arr[i] = size - i;
}

void generate_equal(int *arr, int size) {
    for (int i = 0; i < size; i++)
        arr[i] = 42;
}

void generate_random(int *arr, int size) {
    for (int i = 0; i < size; i++)
        arr[i] = rand() % size;
}

void benchmark(const char *label, void (*gen)(int *, int), int size) {
    int *arr = malloc(size * sizeof(int));
    gen(arr, size);

    clock_t start = clock();
    qsort(arr, size, sizeof(int), cmp);
    clock_t end = clock();

    printf("%s: %ld мс, правильність: %s\n", label,
           (end - start) * 1000 / CLOCKS_PER_SEC,
           is_sorted(arr, size) ? "так" : "ні");

    free(arr);
}

int main() {
    srand(time(NULL));
    int size = 100000;

    benchmark("відсортований", generate_sorted, size);
    benchmark("у зворотному порядку", generate_reversed, size);
    benchmark("однакові елементи", generate_equal, size);
    benchmark("випадковий", generate_random, size);

    return 0;
}
