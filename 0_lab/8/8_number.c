#include <stdio.h>
#include <stdlib.h> 

int main() {
    FILE *file = fopen("input.txt", "r"); 
    int array[128];
    int size = 0, len_output=0; 

    if (file) {
        // &*(array + size)
        while (fscanf(file, "%d", &array[size]) != EOF && size < 128) {
            size++;
        }
        fclose(file);
    } else {
        printf("Could not open the file");
        return -1;
    }

    printf("a) numbers in odd positions;\n");
    printf("b) even numbers;\n");
    printf("c) for the current element: the value farthest (by value) from it from the same array;\n");
    printf("d) for the current element: the sum of the elements that precede it;\n");
    printf("e) for the current element: the sum of the elements that are smaller than it.\n");
    char choice;
    printf("Select an operation (a-e): ");
    scanf(" %c", &choice);
    int newArray[128];
    int index;
    printf("Enter the index of the current item: ");
    scanf("%d", &index);
    switch (choice) {
        case 'a':
            for (int i = 0, j = 0; i < size; i += 2, j++) {
                newArray[j] = array[i];
                len_output++;
            }
            break;
        case 'b':
            for (int i = 0, j = 0; i < size; i++) {
                if (array[i] % 2 == 0) {
                    newArray[j] = array[i];
                    j++;
                    len_output++;
                }
            }
            break;
        case 'c':
            if (index >= 0 && index < size) {
                int maxDiff = 0;
                int maxDiffIndex = 0;
                for (int i = 0; i < size; i++) {
                    int diff = abs(array[index] - array[i]);
                    if (diff > maxDiff) {
                        maxDiff = diff;
                        maxDiffIndex = i;
                    }
                }
                len_output=1;
                newArray[0] = array[maxDiffIndex];
            } else {
                printf("The index goes outside the array");
                return 1;
            }
            break;
        case 'd':
            if (index >= 0 && index < size) {
                int sum = 0;

                for (int i = 0; i < index; i++) {
                    sum += array[i];
                }
                len_output=1;
                newArray[0] = sum;
            } else {
                printf("The index goes outside the array");
                return 1;
            }
            break;
        case 'e':
            if (index >= 0 && index < size) {
                int sum = 0;
                for (int i = 0; i < size; i++) {
                    if (array[i] < array[index]) {
                        sum += array[i];
                    }
                }
                newArray[0] = sum;
                len_output=1;
            } else {
                printf("The index goes outside the array");
                return 1;
            }
            break;
        default:
            printf("Incorrect operation selection");
            return 1;
    }
    printf("Result:\n");
    for (int i = 0; i < len_output; i++) {
        printf("%d ", newArray[i]);
    }
    return 0;
}