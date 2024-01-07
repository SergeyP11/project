#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
// Длина пути
#define pathLen 256

void addendum(const char *inputPath, FILE *outputFile);

int main(int argc, const char *argv[]) 
{
    char *currentPath;
    char *outputPath;
    FILE *outputFile = NULL, *listFiles = NULL;
    // Проверка аргументов командной строки
    if (argc<2)
    {
           printf("You entered the wrong argument\n");
           return 1;
    }
    // Ввод пути выходного файла, проверка
    outputPath  = calloc(pathLen, sizeof(char));
    printf("Enter the path to the output file:\n");
    scanf("%s", outputPath);
    outputFile = fopen(outputPath, "w");
    if (outputFile == NULL){
        free(outputPath);
        printf("Mistake. The output file does not open\n");
        return -1;
    }
    currentPath = calloc(pathLen, sizeof(char));

    // -fi <file_name> в текстовом файле с указанным именем содержится
    // список имен файлов с исходными данными;
    if (!strcmp(argv[1], "-fi"))
    {
        // Открытие списка файлов, проверка на ошибки
        listFiles = fopen(argv[2], "r");
        if (listFiles == NULL)
        {
            free(currentPath);
            free(outputPath);
            fclose(outputFile);
            printf("Mistake. The input file does not open\n");
            return -1;
        }
        while (!feof(listFiles))
        {
            // Считываем путь файла, добавляем содержимое этого файла в выходной файл
            fscanf(listFiles, "%s", currentPath);
            addendum(currentPath, outputFile);
        }
        fclose(listFiles);
        printf("The output file has been created. The job is done\n");
    }

    // -сin список файлов необходимо считать из стандартного потока
    // ввода, то есть имена файлов, в которых содержатся данные, вводит пользователь;
    else if (!strcmp(argv[1], "-cin"))
    {
        while(1)
        {
            // Ввод пути к файлу и добавление его содержимого в выходной файл
            printf("Enter the path to the file (Stop to exit):\n");
            scanf("%s", currentPath);
            if(!strcmp(currentPath, "Stop"))
            {
                break;
            }
            addendum(currentPath, outputFile);
        }
        printf("The output file has been created. The job is done\n");
    }
    // -arg все имена файлов передаются через аргументы командной строки.
    else if (!strcmp(argv[1], "-arg"))
    {
        // Считывание пути к файлу и добавление его содержимого в выходной файл
        for(int i=2; i<argc; i++)
        {
            addendum(argv[i], outputFile);
        }
        printf("The output file has been created. The job is done\n");
    }
    else 
    {
        printf("You entered the wrong argument\n");
    }
    free(outputPath);
    free(currentPath);
    fclose(outputFile);
    return 0;
}
// Функция переноса содержимого одного файла в другой
void addendum(const char * inputPath, FILE *outputFile)
{
    FILE *inputFile = NULL;
    char sym;
    // Открытие входящего файла, проверка на ошибки
    inputFile = fopen(inputPath, "r");
    if (inputFile == NULL){
        printf("Mistake. The input file does not open\n");
        return;
    }
    // Посимвольный перенос
    while ((sym = fgetc(inputFile)) != EOF)
    {
        fputc(sym, outputFile);
    }
    fclose(inputFile);
}
