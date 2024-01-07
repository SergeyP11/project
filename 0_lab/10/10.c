#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** generateMatrix(int rows, int cols);
void freeMatrix(int** matrix, int rows);
int** multiplyMatrices(int** matrix1, int rows1, int cols1, int** matrix2, int rows2, int cols2);
int determinant(int** matrix, int n);
void printMatrix(int** matrix, int rows, int cols);

int main(int argc, const char *argv[]) {
    // инициализация генератора случайных чисел
    srand(time(NULL)); 
    // row - ряд, col- столбцы
    int rows1, cols1, rows2, cols2;
    char input[100];

    // Ввод количества столбцов/строк двух матриц
    printf("Enter the number of rows for the first matrix: ");
    //scanf("%d", &rows1);
    fgets(input, sizeof(input), stdin);
    if (sscanf(input, "%d", &rows1) == 1) {
        if (rows1 <= 1 || rows1 >= 10) {
            printf("Error: Enter a number from 1 to 10.\n");
            return -1;
        }
    } else {
        printf("Error: Enter the correct number.\n");
        return -1;
    }
    input[0] = '\0';

    printf("Enter the number of columns for the first matrix: ");
    // scanf("%d", &cols1);
    fgets(input, sizeof(input), stdin);
    if (sscanf(input, "%d", &cols1) == 1) {
        if (cols1 <= 1 || cols1 >= 10) {
            printf("Error: Enter a number from 1 to 10.\n");
            return -1;
        }
    } else {
        printf("Error: Enter the correct number.\n");
        return -1;
    }
    input[0] = '\0';

    printf("Enter the number of rows for the second matrix: ");
    // scanf("%d", &rows2);
    fgets(input, sizeof(input), stdin);
    if (sscanf(input, "%d", &rows2) == 1) {
        if (rows2 <= 1 || rows2 >= 10) {
            printf("Error: Enter a number from 1 to 10.\n");
            return -1;
        }
    } else {
        printf("Error: Enter the correct number.\n");
        return -1;
    }
    input[0] = '\0';
    
    printf("Enter the number of columns for the second matrix: ");
    // scanf("%d", &cols2);
    fgets(input, sizeof(input), stdin);
    if (sscanf(input, "%d", &cols2) == 1) {
        if (cols2 <= 1 || cols2 >= 10) {
            printf("Error: Enter a number from 1 to 10.\n");
            return -1;
        }
    } else {
        printf("Error: Enter the correct number.\n");
        return -1;
    }
    input[0] = '\0';

    int **matrix1 = generateMatrix(rows1, cols1); // создание и заполнение первой матрицы
    int **matrix2 = generateMatrix(rows2, cols2); // создание и заполнение второй матрицы

    printf("First matrix:\n");
    printMatrix(matrix1, rows1, cols1); // вывод первой матрицы
    printf("Second matrix:\n");
    printMatrix(matrix2, rows2, cols2); // вывод второй матрицы

    int** result = multiplyMatrices(matrix1, rows1, cols1, matrix2, rows2, cols2); // умножение матриц
    if (result != NULL) {
        printf("Result of matrix multiplication:\n");
        for (int i = 0; i < rows1; i++) {
            for (int j = 0; j < cols2; j++) {
                printf("%d ", result[i][j]); // вывод результата умножения матриц
            }
            printf("\n");
        }
        freeMatrix(result, rows1); // освобождение памяти результата
    }
    int det1 = determinant(matrix1, rows1); // нахождение определителя первой матрицы
    int det2 = determinant(matrix2, rows2); // нахождение определителя второй матрицы
    printf("Determinant of matrix 1: %d\n", det1); // вывод определителя первой матрицы
    printf("Determinant of matrix 2: %d\n", det2); // вывод определителя второй матрицы
    freeMatrix(matrix1, rows1); // освобождение памяти первой матрицы
    freeMatrix(matrix2, rows2); // освобождение памяти второй матрицы
    return 0;
}

// Функция генерации матрицы
int** generateMatrix(int rows, int cols) {
    int** matrix = (int**)malloc(rows * sizeof(int*)); // выделение памяти под массив указателей на строки
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int)); // выделение памяти под каждую строку (массив элементов)
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 201 - 100; // заполнение матрицы произвольными значениями, дает случайное число
            // в диапазоне от 0 до 200. После этого вычитанием 100 мы получаем случайное число в диапазоне от -100 до 100.
        }
    }
    return matrix;
}

// Функция освобождения памяти, выделенной под матрицу
void freeMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]); // освобождение памяти отдельных строк
    }
    free(matrix); // освобождение памяти массива указателей
}

// Функция умножения матриц
int** multiplyMatrices(int** matrix1, int rows1, int cols1, int** matrix2, int rows2, int cols2) {
    if (cols1 != rows2) {
        printf("Error: Matrix dimensions are not compatible for multiplication\n"); // проверка совместимости размерностей матриц
        return NULL;
    }
    
    int** result = (int**)malloc(rows1 * sizeof(int*)); // выделение памяти под результат умножения
    for (int i = 0; i < rows1; i++) {
        result[i] = (int*)malloc(cols2 * sizeof(int)); // выделение памяти под строки результата
        for (int j = 0; j < cols2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < cols1; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j]; // вычисление элементов результата
            }
        }
    }
    return result;
}

// Функция нахождения определителя матрицы
int determinant(int** matrix, int n) {
    if (n == 1) {
        return matrix[0][0]; // базовый случай для выхода из рекурсии
    }
    int det = 0;
    int** submatrix = (int**)malloc((n - 1) * sizeof(int*)); // выделение памяти под подматрицу
    for (int i = 0; i < n - 1; i++) {
        submatrix[i] = (int*)malloc((n - 1) * sizeof(int)); // выделение памяти под строки подматрицы
    }
    int sign = 1;
    for (int i = 0; i < n; i++) {
        int subi = 0;
        for (int row = 1; row < n; row++) {
            int subj = 0;
            for (int col = 0; col < n; col++) {
                if (col == i) {
                    continue;
                }
                submatrix[subi][subj] = matrix[row][col]; // заполнение подматрицы
                subj++;
            }
            subi++;
        }
        det = det + (sign * matrix[0][i] * determinant(submatrix, n - 1)); // рекурсивный подсчёт определителя
        sign = -sign;
    }
    for (int i = 0; i < n - 1; i++) { // освобождение памяти подматрицы
        free(submatrix[i]);
    }
    free(submatrix);
    return det;
}

// Функция вывода матрицы
void printMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]); // вывод элементов матрицы
        }
        printf("\n");
    }
}