#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

int find_min(int arr[], int size);
int find_max(int arr[], int size);
void swap(int arr[], int min_index, int max_index);
void print_array(int arr[], int size);

int main() {
    int arr[SIZE];
    int i, min_index, max_index, temp;
    srand(time(NULL));
    for (i = 0; i < SIZE; i++) {
        arr[i] = rand();
    }
    printf("Source array:\n");
    print_array(arr, SIZE);
    min_index = find_min(arr, SIZE);
    max_index = find_max(arr, SIZE);
    swap(arr, min_index, max_index);
    printf("\nModified array:\n");
    print_array(arr, SIZE);
    return 0;
}

int find_min(int arr[], int size) {
    int i, min_index = 0;
    int min = arr[0];
    for (i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
            min_index = i;
        }
    }
    return min_index;
}

int find_max(int arr[], int size) {
    int i, max_index = 0;
    int max = arr[0];
    for (i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
            max_index = i;
        }
    }
    return max_index;
}

void swap(int arr[], int min_index, int max_index) {
    int temp = arr[min_index];
    arr[min_index] = arr[max_index];
    arr[max_index] = temp;

    // a ^= b;
    // b ^= a;
    // a ^= b;
}

void print_array(int arr[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}