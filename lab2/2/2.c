#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_number(const char *str);
double geometric_mean(int count, ...);
double power(double base, int exponent);

int main(int argc, const char *argv[]) {
    // Пример использования функций
    printf("Exponentiation: %lf\n", power(2.1, 3));
    printf("Raising to a negative degree: %lf\n", power(2.1, -3));
    printf("Geometric mean: %lf\n", geometric_mean(3, "2.1", "3.1", "4.2"));
    printf("Geometric mean with incorrect input: %lf\n", geometric_mean(3, "2.0", "abc", "4.0"));
    printf("Geometric mean with insufficient number of numbers: %lf\n", geometric_mean(3, "2.0", "3.0"));
    return 0;
}

bool is_number(const char *str) {
    char *endptr;
    double val = strtod(str, &endptr); // преобразование строки в double, остаток строки в endptr
    return *endptr == '\0'; // если строка взялась полностью (остается завершающий ноль), то
    // возвращается 1, в противном случае 0
}

double geometric_mean(int count, ...) {
    va_list args; // объявление переменной типа va_list, которая используется для хранения списка переменных аргументов.
    va_start(args, count); //  извлечение дополнительных аргументов, которые идут после переменной count
    double product = 1.0;
    for (int i = 0; i < count; i++) {
        const char *num_str = va_arg(args, const char *); // извлечение очередного аргумента из списка переменных
        // аргументов args в виде строки и сохранение его в переменной num_str.
        if (!is_number(num_str)) {
            printf("Error: '%s' is not a number or the wrong number of arguments has been entered\n", num_str);
            return 0.0;
        }
        double num = atof(num_str);
        product *= num;
    }
    va_end(args);
    return pow(product, 1.0 / count);
}

double power(double number, int degree) {
    if (number==0) return 0;
    if (number==1) return 1;
    if (degree==0) return 1;    
    if (degree<0) return 1/power(number, -degree);
    if (degree==2) return number*number;
    if (degree==1) return number;
    if (degree%2==0)
        return power(power(number, degree/2), 2);
    else
        return number*power(number, degree-1);
}
