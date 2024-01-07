#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

// Длина пути
#define pathLen 256 

int FlagD(FILE* inputFile, FILE* outputFile);
int FlagI(FILE* inputFile, FILE* outputFile);
int FlagS(FILE* inputFile, FILE* outputFile);
int FlagA(FILE* inputFile, FILE* outputFile);
int FlagF(FILE* inputFile, FILE* outputFile);

int main(int argc, const char *argv[]) {

    char *inputPath; // Путь входного файла
    char *inputName; // Имя входного файла
    char *outputPath; // Путь выходного файла
    FILE *inputFile = NULL, *outputFile = NULL; // Входной и выходной файлы

    // Проверка на количество введенных аргументов, должно быть 2 или 3
    if (argc!=3 && argc!=4){
        printf("Incorrect input of arguments. Enter two or three arguments\n");
        return 1;
    }
    // Проверка на то, что введено n, но не введен путь выходного файла
    if(argv[1][1]=='n' && argc!=4){
        printf("If you use 'n', then you need to enter the path of the output file in the third parameter\n");
        return 1;
    }
    // Открытие файла для чтения
    inputFile = fopen(argv[2], "r");
    // Проверка, что он открылся
    if (inputFile==NULL){ 
        printf("Input file not opened\n");
        return -1;
    }
    // преобразует путь к файлу в абсолютный путь.
    inputPath=realpath(argv[2], NULL);
    // Находит последнее вхождение символа / в строке inputPath и возвращает указатель на это место. Позволяет получить только имя файла
    inputName = strrchr(inputPath, '/');

    // Устанавливает символ \0 (нулевой символ) в следующей позиции после найденного символа / в строке inputPath.
    // Это приведет к обрезанию строки. Останется имя файла
    *inputName++='\0';
    // Выделяем память заданного размера
    outputPath = (char*)calloc(pathLen, sizeof(char));
    // Формируем путь выходного файла в зависимости отвыбора пользователя
    if(argc==4 && argv[1][1]=='n')
    {
        strcat(outputPath, argv[3]);
    }
    else
    {
        strcat(outputPath, inputPath);
        strcat(outputPath, "/");
        strcat(outputPath, "output_");
        strcat(outputPath, inputName);
    }
    // Открываем выходной файл для записи и проверяем открылся ли, если нет закрываем файлы и очищаем дин. память, выводим сообщение
    outputFile = fopen(outputPath, "w");
    if (outputFile==NULL){
        fclose(inputFile);
        free(outputPath);
        printf("Output file not opened\n");
        return -1;
    }
    free(outputPath);
    
    // В зависимости от введенного параметра вызываем нужную функцию
    if ( !strcmp(argv[1], "-d") || !strcmp(argv[1], "/d") || !strcmp(argv[1], "/nd") || !strcmp(argv[1], "-nd"))
        FlagD(inputFile, outputFile);
    if ( !strcmp(argv[1], "-i") || !strcmp(argv[1], "/i") || !strcmp(argv[1], "/ni") || !strcmp(argv[1], "-ni")) 
        FlagI(inputFile, outputFile);
    if ( !strcmp(argv[1], "-s") || !strcmp(argv[1], "/s") || !strcmp(argv[1], "/ns") || !strcmp(argv[1], "-ns")) 
        FlagS(inputFile, outputFile);
    if ( !strcmp(argv[1], "-a") || !strcmp(argv[1], "/a") || !strcmp(argv[1], "/na") || !strcmp(argv[1], "-na"))
        FlagA(inputFile, outputFile);
    if ( !strcmp(argv[1], "-f") || !strcmp(argv[1], "/f") || !strcmp(argv[1], "/nf") || !strcmp(argv[1], "-nf"))
        FlagF(inputFile, outputFile);
    
    fclose(inputFile);
    fclose(outputFile);
    
    return 0;
}

// d необходимо исключить символы цифр из файла
int FlagD(FILE* inputFile, FILE* outputFile){
    char ch;
    // Посимвольное считывание
    while ((ch = fgetc(inputFile)) != EOF) 
    {
        if(!isdigit(ch))
        {
            // Запись в файл
             fputc(ch, outputFile);
        }
    }
    printf("The work is completed. The output file is done\n");
    return 0;
}

// i необходимо в выходной файл написать, сколько раз в каждой строке встречаются символы букв;
int FlagI(FILE* inputFile, FILE* outputFile){
    char sym;
    int countS = 0, numString=0;
    
    while ((sym = fgetc(inputFile)))
    {
        if (isalpha(sym))
        {
             countS++;
        }
        if(sym=='\n' || sym==EOF)
        {
            fprintf(outputFile,"The number of letters in the %d line: %d\n",++numString, countS);
            countS=0;
            if(sym==EOF)
            {
                 break;
            }
        }
    }
    printf("The work is completed. The output file is done\n");
    return 0;
}
// s необходимо в выходной файл написать, сколько раз в каждой строке встречаются символы,
// отличные от символов цифр, символов букв и символа пробела;
int FlagS(FILE* inputFile, FILE* outputFile){
    char sym;
    int countS = 0, numString=0;
    
    while ((sym = fgetc(inputFile)))
    {
        if (sym != EOF && !isalpha(sym) && !isspace(sym) && !isdigit(sym)) 
        {
            countS++;
        }
        if(sym == '\n' || sym == EOF)
        {
            fprintf(outputFile,"The number of letters in the %d line: %d\n",++numString, countS);
            countS = 0;
            if(sym == EOF)
            {
                 break;
            }
        }
    }
    printf("The work is completed. The output file is done\n");
    return 0;
}
// a необходимо заменить символы, отличные от цифр, их строковым представлением ASCII-кода;
int FlagA(FILE* inputFile, FILE* outputFile){
    char sym;
    
    while ((sym = fgetc(inputFile)) != EOF)
    {
        if(!isdigit(sym))
        {
              fprintf(outputFile,"%d ", sym);
        }
    }
    printf("The work is completed. The output file is done\n");
    return 0;
}
// f создать выходной файл таким образом, чтобы в каждой в каждой второй лексеме
// все буквы были переписаны в строчные, а также в каждой пятой лексеме все символы
// были заменены на эквивалентные им ASCII-коды.
int FlagF(FILE* inputFile, FILE* outputFile){
    char sym;
    int count = 0;
    
    while ((sym = fgetc(inputFile)) != EOF)
    {
        if(isspace(sym))
        {
            fputc(sym, outputFile);
            count++;
        }
        else if(count%2==1)
        { 
            fprintf(outputFile,"%c",tolower(sym));
        }                                                           
        else if(count%5==4) 
        {
            fprintf(outputFile,"%d", sym);
        }
        else
        {
             fputc(sym, outputFile);
        }
    }
    printf("The work is completed. The output file is done\n");
    return 0;
}
