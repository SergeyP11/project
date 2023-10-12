#include <stdio.h>
#include <string.h> 

int main() {
    FILE *file;
    char filename[100];
    char buffer[100];
    printf("Input name file: ");
    scanf("%s", filename);
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }
    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file.\n");
        fclose(file);
        return 1;
    }
    int col1, col2, col3;
    while (fscanf(file, "%d %d %d", &col1, &col2, &col3) != EOF) {
        fprintf(tempFile, "%d %d %d\n", col3, col1, col2); 
    }
    fclose(file);
    fclose(tempFile);
    remove(filename);
    if (rename("temp.txt", filename) != 0) {
        printf("Error when renaming a file.\n");
        return 1;
    }
    printf("The file has been successfully overwritten.\n");
    return 0;
}