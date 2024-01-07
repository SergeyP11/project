#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

size_t custom_strlen(const char *str) {
    const char *s;
    for (s = str; *s; ++s) {} // Продвигаем указатель до конца строки
    return (s - str); // Возвращаем разницу между конечным и начальным указателями
}

void custom_strcpy(char *dest, const char *src) {
    while ((*dest++ = *src++)) {} // Копируем символы из src в dest, пока не встретим нулевой символ
}

// Инициализация генератора случайных чисел
void custom_srand(unsigned int seed) {
    srand(seed);
}

// Генерация случайного числа
int custom_rand() {
    return rand();
}

// Функция реверсирования строки
char* reverse_string(const char *str) {
    size_t len = custom_strlen(str); // Сначала получаем длину строки
    char *res = malloc(len + 1); // Выделяем память под результат
    if (!res) {
        return NULL; // В случае неудачи возвращаем NULL
    }
    for (size_t i = 0; i < len; ++i) {
        res[i] = str[len - i - 1]; // Копируем символы в обратном порядке
    }
    res[len] = '\0'; // В конце устанавливаем нулевой символ
    return res;
}

// Функция для преобразования символов на нечетных позициях к верхнему регистру
char* upper_odd_characters(const char *str) {
    size_t len = custom_strlen(str); // Вычисляем длину исходной строки
    char *res = malloc(len + 1); // Выделяем память под результат
    if (!res) {
        return NULL;
    }
    for (size_t i = 0; i < len; ++i) {
        if (i % 2 == 0) {
            res[i] = str[i]; // Копируем четные
        } else {
            res[i] = toupper((unsigned char)str[i]); // Приводим нечетные к верхнему регистру
        }
    }
    res[len] = '\0';
    return res;
}

// Cортировка строки по символам
char* sort_string(const char *input) {
    int i, digit_count = 0, alpha_count = 0, other_count = 0;
    int length = 0;

    // Сначала подсчитываем длину строки и количество символов каждого типа.
    while (input[length] != '\0') {
        if (isdigit(input[length])) digit_count++;
        else if (isalpha(input[length])) alpha_count++;
        else other_count++;
        length++;
    }

    // Выделяем память для результата.
    char *result = (char *)malloc(length + 1);  // Дополнительный байт для нуль-терминатора.
    if (result == NULL) {
        return NULL;  // Выход в случае ошибки выделения памяти.
    }

    int digit_index = 0, alpha_index = digit_count, other_index = digit_count + alpha_count;

    // Распределяем символы по категориям.
    for (i = 0; i < length; i++) {
        if (isdigit(input[i])) {
            result[digit_index++] = input[i];
        } else if (isalpha(input[i])) {
            result[alpha_index++] = input[i];
        } else {
            result[other_index++] = input[i];
        }
    }

    // Добавляем нуль-терминатор в конец строки.
    result[length] = '\0';

    return result;

}

// Функция для конкатенации строк в случайном порядке
char* concat_strings(int count, char **strings, unsigned int seed) {
    custom_srand(seed); // Инициализируем генератор случайных чисел
    size_t total_length = 1; // Начинаем с 1 для учета нулевого символа

    for (int i = 0; i < count; ++i) {
        total_length += custom_strlen(strings[i]); // Считаем общую длину всех строк
    }

    char *res = malloc(total_length); // Выделяем память под результат
    if (!res) {
        return NULL;
    }

    res[0] = '\0'; // Инициализация результирующей строки как пустой

    for (int i = 0; i < count; ++i) {
        // Выбираем случайный индекс для следующей строки
        const int r = custom_rand() % (count - i);
        for (size_t j = 0; strings[r][j] != '\0'; ++j) {
            // Добавляем символы из строки в результат
            const size_t res_len = custom_strlen(res);
            res[res_len] = strings[r][j];
            res[res_len + 1] = '\0';
        }
        // Меняем местами использованную строку, чтобы не выбрать ее опять
        char *temp = strings[r];
        strings[r] = strings[count - i - 1];
        strings[count - i - 1] = temp;
    }
    return res;
}

int main(int argc, char *argv[]) {
    // Проверка количества аргументов
    if (argc < 3) {
        printf("Usage: %s FLAG STRING [SEED] [STRINGS...]\n", argv[0]);
        return 1;
    }
    char *result = NULL; // Для сохранения результата работы функции
    // Определение действия в зависимости от флага
    if (argv[1][0] == '-' && argv[1][2] == '\0') {
        switch (argv[1][1]) {
            case 'l': // Если флаг -l, печатаем длину строки
                printf("Length: %zu\n", custom_strlen(argv[2]));
                return 0;
            case 'r': // Если флаг -r, реверсируем строку
                result = reverse_string(argv[2]);
                break;
            case 'u': // Если флаг -u, преобразуем нечетные символы к верхнему регистру
                result = upper_odd_characters(argv[2]);
                break;
            case 'n': // Если флаг -n, сортируем символы строки
                result = sort_string(argv[2]);
                break;
            case 'c': // Если флаг -c, конкатенируем строки в случайном порядке
                if (argc < 5) {
                    printf("Usage for concatenation: %s -c SEED STRING...\n", argv[0]);
                    return 1;
                }
                unsigned int seed = strtoul(argv[3], NULL, 10);
                result = concat_strings(argc - 4, argv + 4, seed);
                break;
            default: // Если флаг неизвестен
                printf("Unknown flag: %s\n", argv[1]);
                return 1;
        }
    } else {
        // Если формат флага некорректен
        printf("Invalid flag format: %s\n", argv[1]);
        return 1;
    }

    if (result) {
        // Выводим результат и освобождаем память
        printf("Result: %s\n", result);
        free(result);
    } else {
        // Сообщаем об ошибке если результат NULL (функции вернули NULL)
        printf("An error occurred.\n");
        return 1;
    }
    return 0; // Корректное завершение программы
}
