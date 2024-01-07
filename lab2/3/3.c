#include <stdio.h>
#include <stdarg.h>

void findSubstringInFile(const char *substring, const char *filename);
void searchInFiles(const char *substring, int num_files, ...);

int main() {
    searchInFiles("example", 2, "file1.txt", "file2.txt"); // Пример использования функции
    return 0;
}

// Функция с переменным числом аргументов
void searchInFiles(const char *substring, int num_files, ...) {
    va_list files; // Создаем список аргументов
    va_start(files, num_files); // Инициализируем список аргументов

    int actual_num_files = 0;
    for (int i = 0; i < num_files; i++) {
        const char *filename = va_arg(files, const char *); // Получаем очередной аргумент - имя файла
        actual_num_files++;
        findSubstringInFile(substring, filename); // Вызываем функцию поиска подстроки в файле
    }
    va_end(files); // Завершаем работу со списком аргументов
    if (actual_num_files != num_files) {
        printf("Error: Number of files provided does not match the expected number\n");
    }
}

// Функция для поиска подстроки в файле
void findSubstringInFile(const char *substring, const char *filename) {
    FILE *file = fopen(filename, "r"); // Открываем файл для чтения
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", filename);
        return;
    }
    char line[1000]; // Буфер для считывания строки из файла
    int line_number = 1; // Номер текущей строки
    while (fgets(line, sizeof(line), file)) { // Считываем строку из файла
        char *position = line; // объявляет указатель position на строку line. То есть, position будет указывать на начало строки line.
        while (*position != '\0') {
            int match = 1; // Переменная match используется для отслеживания совпадения подстроки с текущим фрагментом строки
            const char *sub = substring; // объявляет указатель sub, который указывает на начало искомой подстроки substring.
            const char *temp_position = position; // объявляет указатель temp_position, который будет использоваться для перемещения по текущей строке.
            while (*sub != '\0') {
                if (*temp_position != *sub) {
                    match = 0;
                    break;
                }
                temp_position++;
                sub++;
            }
            if (match) {
                printf("Substring found in file %s at line %d, position %d\n", filename, line_number, (int)(position - line) + 1);
            }
            position++; // Переходим к следующему символу
        }
        line_number++; // Увеличиваем номер строки
    }
    fclose(file); // Закрываем файл
}

