#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>

char* sumNumbers(int base, int count, ...);
int isValidNumber(char* number, int base);
int isValidDigit(char digit, int base);
char* addNumbers(char* num1, char* num2, int base);
int digitToValue(char digit);
int baseToDecimal(char* number, int base);

int main() {
    // Примеры использования
    char* num1 = "10101010101010101000000";
    char* num2 = "111111111110000";
    char* num3 = "11111111111111111111";
    // Суммируем три числа в двоичной системе счисления
    printf("The amount in the specified number system: %s\n", sumNumbers(2, 3, num1, num2, num3));
    return 0;
}

// Функция для суммирования чисел в заданной системе счисления
char* sumNumbers(int base, int count, ...) {
    va_list numbers; // Создаем список аргументов
    va_start(numbers, count); // Инициализируем список аргументов

    char* result = (char*)malloc(100 * sizeof(char)); // Выделяем память под результат
    result[0] = '0'; // Инициализируем результат нулем
    result[1] = '\0'; // Добавляем завершающий нуль
    for (int i = 0; i < count; i++) { // Перебираем все числа
        char* current = va_arg(numbers, char*); // Получаем следующее число из списка аргументов
        if (!isValidNumber(current, base)) { // Проверяем валидность числа
            printf("Invalid number: %s\n", current); 
            return "Error"; 
        }
        char* temp = result; // Сохраняем указатель на предыдущий результат (для освобождения памяти)
        result = addNumbers(result, current, base); // Складываем текущее число с общим результатом
        free(temp); // Освобождаем память, занятую предыдущим результатом
    } 
    va_end(numbers);
    return result;
}

// Функция для проверки валидности строки числа в заданной системе счисления
int isValidNumber(char* number, int base) {
    for (int i = 0; i < strlen(number); i++) {
        if (!isValidDigit(number[i], base)) {
            return 0;
        }
    }
    return 1;
}

// Функция для проверки, является ли символ цифрой заданной системы счисления
int isValidDigit(char digit, int base) {
    if (digit >= '0' && digit <= '9') {
        return digit - '0' < base;
    } else if (digit >= 'A' && digit <= 'Z') {
        return digit - 'A' + 10 < base;
    } else {
        return 0;
    }
}

// Функция для сложения двух чисел в заданной системе счисления
char* addNumbers(char* num1, char* num2, int base) {
    int carry = 0;
    char* result = (char*)malloc(100 * sizeof(char)); // Выделяем память под результат
    int i = strlen(num1) - 1; // (берем последнюю цифру)
    int j = strlen(num2) - 1; // (берем последнюю цифру)
    int k = 0; // Инициализируем переменную k нулем (индекс результата)
    
    // Пока не закончились цифры в обоих числах или есть перенос
    while (i >= 0 || j >= 0 || carry) {
        int digit1 = (i >= 0) ? digitToValue(num1[i]) : 0; // Получаем значение текущей цифры 
        int digit2 = (j >= 0) ? digitToValue(num2[j]) : 0; // Получаем значение текущей цифры
        int sum = digit1 + digit2 + carry; // Складываем текущие цифры и перенос
        carry = sum / base; // Вычисляем новый перенос
        result[k++] = (sum % base < 10) ? (sum % base + '0') : (sum % base - 10 + 'A'); // Записываем новую цифру результата
        
        i--; // Уменьшаем индекс первого числа
        j--; // Уменьшаем индекс второго числа

    }
    // Реверсируем полученный результат
    result[k] = '\0';
    int len = strlen(result);
    for (int l = 0; l < len / 2; l++) {
        char temp = result[l];
        result[l] = result[len - l - 1];
        result[len - l - 1] = temp;
    }
    return result;
}

// Функция для преобразования цифры в число
int digitToValue(char digit) {
    if (digit >= '0' && digit <= '9') {
        return digit - '0';
    } else {
        return digit - 'A' + 10;
    }
}

// Функция для преобразования числа в заданной системе счисления в десятичное число
int baseToDecimal(char* number, int base) {
    int result = 0;
    int power = 0;
    for (int i = strlen(number) - 1; i >= 0; i--) {
        result += digitToValue(number[i]) * pow(base, power);
        power++;
    }
    return result;
}
