#include <stdio.h>
#include <stdarg.h>

// Функция для определения, имеет ли десятичная дробь конечное представление в заданной системе счисления
int hasFiniteRepresentation(int base, int count, ...) {
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; ++i) {
        double num = va_arg(args, double);
        // Проверка на валидность
        if (num <= 0 || num >= 1) {
            printf("Invalid input: %f\n", num);
            continue;
        }
        // Проверка на конечное представление в данной системе счисления
        int finite = 1;
        double fraction = num;
        while (fraction != 0 && finite) {
            fraction *= base;
            if (fraction >= 1) {
                if (fraction == 1) {
                    break;
                } else {
                    finite = 0;
                }
            }
        }
        if (finite) {
            printf("The decimal fraction %f has a finite representation in base %d\n", num, base);
        } else {
            printf("The decimal fraction %f does not have a finite representation in base %d\n", num, base);
        }
    }
    va_end(args);
}

int main() {
    hasFiniteRepresentation(2, 2, 0.5, (double) 1/3);
    hasFiniteRepresentation(3, 2, 0.5, (double) 1/3);
    return 0;
}