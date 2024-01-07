#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <stdbool.h>

// Функция для определения выпуклости многоугольника
// Принимает количество вершин многоугольника и координаты вершин в формате (x1, y1, x2, y2, ..., xn, yn)
bool isConvexPolygon(int numVertices, ...) {
    va_list args; // объявление списка аргументов
    va_start(args, numVertices); // начало использования списка аргументов с указанием числа вершин многоугольника
    // Получаем координаты вершин многоугольника
    double x0 = va_arg(args, double); // извлечение координаты x первой вершины
    double y0 = va_arg(args, double); // извлечение координаты y первой вершины
    double x1 = va_arg(args, double); // извлечение координаты x второй вершины
    double y1 = va_arg(args, double); // извлечение координаты y второй вершины
    double x2, y2; // объявление переменных для третьей вершины
    bool Neg = false, Pos = false; // инициализация флагов для отрицательных и положительных векторных произведений
    double crossProduct; // переменная для хранения векторного произведения

    for (int i = 2; i < numVertices; i++) {
        x2 = va_arg(args, double); // извлечение координаты x i-той вершины
        y2 = va_arg(args, double); // извлечение координаты y i-той вершины
        // Считаем векторные произведения двух последовательных ребер
        crossProduct = (x1 - x0) * (y2 - y1) - (y1 - y0) * (x2 - x1);
        if (crossProduct < 0) {
            Neg = true;
        } else if (crossProduct > 0) {
            Pos = true;
        }
        x0 = x1;
        y0 = y1;
        x1 = x2;
        y1 = y2;
    }
    va_end(args); // завершение использования списка аргументов
    // Если есть и положительные, и отрицательные векторные произведения,
    // то многоугольник невыпуклый
    if (Neg && Pos) {
        return false; // если есть и отрицательное, и положительное векторное произведение, многоугольник невыпуклый
    } else {
        return true; // в противном случае многоугольник выпуклый
    }
}

double evaluatePolynomial(double point, int degree, ...) {
    va_list args;
    va_start(args, degree);
    
    double result = 0;
    double coefficient;
    
    for (int i = 0; i <= degree; i++) {
        coefficient = va_arg(args, double);
        result += coefficient * pow(point, degree - i);
    }
    
    va_end(args);
    return result;
}


int main() {
    // Пример использования функции для проверки выпуклости многоугольника
    bool convex = isConvexPolygon(4, 0.0, 0.0, 1.0, 1.0, 2.0, 0.0, 0.0, 0.0);
    printf("Многоугольник %s выпуклым.\n", convex ? "является" : "не является");
    convex = isConvexPolygon(5, 0.0, 0.0, 2.0, 2.0, 1.0, 3.0, 3.0, 1.0, 0.0, 0.0);
    printf("Многоугольник %s выпуклым.\n", convex ? "является" : "не является");

    // Пример использования функции для вычисления значения многочлена
    double value = evaluatePolynomial(2.0, 3, 1.0, 2.0, 3.0, 4.0);
    printf("Значение многочлена в точке x=2: %f\n", value);

    return 0;
}
