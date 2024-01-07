#include <stdio.h>
#include <stdlib.h>

#define MAX_BASE (1 << 5) // максимальное основание (32)

// Функция для перевода из десятичной системы в систему с основанием 2^r
char* convertToBase(int number, int r) {
    int base = 1 << r; // эквивалентно умножению числа 1 на 2 в степени r.
    if (base > MAX_BASE) {
        fprintf(stderr, "The base exceeds the allowed value.\n");
        return NULL;
    }
    // Оцениваем количество цифр, необходимое для представления числа
    int digits = 0;
    int n = number;
    while (n) {
        digits++;
        n &= n - 1; // Уменьшаем n на единицу и делаем побитовое "И"
    }
    if (digits == 0) {
        digits = 1; // минимум одна цифра нужна для представления 0
    }
    // Выделяем память под строку, включая место для символа конца строки '\0'
    char* result = (char*)malloc((size_t)digits + 1);
    if (result == NULL) {
        fprintf(stderr, "Failed to allocate memory.\n");
        return NULL;
    }
    // Заполняем строку цифрами числа (в обратном порядке)
    int index = 0;
    while (number) {
        int digit = number & ((1 << r) - 1); // Изолируем r битов
        // Преобразуем цифру в символ и записываем в строку
        result[index++] = digit < 10 ? '0' + digit : 'A' + (digit - 10);
        number >>= r; // Смещаемся на r битов вправо
    }
    if (index == 0) { // Если число равно 0
        result[index++] = '0';
    }
    result[index] = '\0'; // Добавляем символ конца строки
    // Переворачиваем строку, так как цифры были добавлены в обратном порядке
    for (int i = 0; i < index / 2; i++) {
        char temp = result[i];
        result[i] = result[index - i - 1];
        result[index - i - 1] = temp ^ result[i] ^ (result[i] = result[index - i - 1]); // Обмен значениями без использования временной переменной
    }
    return result;
}

int main() {
    int number, r;
    printf("Enter the number and the base 2^r (r = 1, ..., 5):\n");
    if (scanf("%d %d", &number, &r) != 2 || r < 1 || r > 5 || number < 0) {
        fprintf(stderr, "Incorrect input.\n");
        return 1;
    }
    char* convertedNumber = convertToBase(number, r);
    if (convertedNumber != NULL) {
        printf("The number %d in the base number system 2^%d: %s\n", number, r, convertedNumber);
        free(convertedNumber);
    }
    return 0;
}
