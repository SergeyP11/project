#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Определение структуры TreeNode для хранения узла дерева.
typedef struct TreeNode {
    char *value; // Значение в узле дерева
    struct TreeNode **children; // Указатель на массив указателей на дочерние узлы.
    int childCount; // Количество дочерних узлов.
} TreeNode;

// Функция создания нового узла дерева с заданным значением.
TreeNode* createNode(char *value) {
    // Выделение памяти для нового узла дерева.
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    // Проверка успешности выделения памяти.
    if (!node) {
        perror("Error allocating memory for node");
        exit(EXIT_FAILURE);
    }
    // Выделение памяти и копирование значения для узла дерева.
    node->value = strdup(value);
    // Проверка успешности выделения памяти для значения.
    if (!node->value) {
        perror("Error allocating memory for node value");
        exit(EXIT_FAILURE);
    }
    // Инициализация указателя на дочерние узлы как NULL.
    node->children = NULL;
    // Инициализация количества дочерних узлов как 0.
    node->childCount = 0;
    // Возврат созданного узла.
    return node;
}

// Функция добавления дочернего узла к родительскому узлу.
void addChild(TreeNode *parent, TreeNode *child) {
    // Для массива дочерних узлов с учетом добавления нового узла.
    parent->children = (TreeNode**)realloc(parent->children, sizeof(TreeNode*) * (parent->childCount + 1));
    // Проверка успешности
    if (!parent->children) {
        perror("Error reallocating memory for children");
        exit(EXIT_FAILURE);
    }
    // Добавление нового узла в массив дочерних узлов.
    parent->children[parent->childCount] = child;
    // Увеличение количества дочерних узлов.
    parent->childCount++;
}

// Функция рекурсивного освобождения памяти всего дерева, начиная с заданного узла.
void freeTree(TreeNode *node) {
    // Проверка, существует ли узел.
    if (node) {
        // Рекурсивное освобождение памяти для каждого из дочерних узлов.
        for (int i = 0; i < node->childCount; i++) {
            freeTree(node->children[i]);
        }
        // Освобождение памяти, занятой значением узла.
        free(node->value);
        // Освобождение памяти, занятой массивом дочерних узлов.
        free(node->children);
        // Освобождение памяти, занятой самим узлом.
        free(node);
    }
}


// Функция для печати дерева в файл.
void printTree(FILE *file, TreeNode *node, int depth) {
    if (node) { // Проверка, существует ли узел.
        for (int i = 0; i < depth; i++) { // Цикл для вывода пробелов (отступов) в зависимости от глубины узла.
            fprintf(file, "    "); // Вывод четырех пробелов в файл для каждого уровня глубины.
        }
        fprintf(file, "%s\n", node->value); // Вывод значения узла в файл.
        for (int i = 0; i < node->childCount; i++) { // Рекурсивный обход всех дочерних узлов.
            printTree(file, node->children[i], depth + 1); // Рекурсивный вызов функции печати для дочернего узла с увеличением глубины.
        }
    }
}

// Функция для разбора выражения и построения дерева из него.
TreeNode* parseExpression(const char **str) {
    if (**str == '\0' || **str == ',') { // Проверка на конец строки или запятую.
        return NULL; // Возврат NULL, если нет больше символов или найдена запятая (конец списка дочерних узлов).
    }
    // Парсинг имени узла, который заканчивается на '(', ',', ')' или конец строки.
    char nodeValue[1024]; // Буфер для хранения значения узла.
    int valueLength = 0; // Счетчик длины значения узла.
    while (**str && **str != '(' && **str != ',' && **str != ')') { // Цикл чтения символов, пока не встретится один из ограничивающих символов.
        nodeValue[valueLength++] = *(*str)++; // Добавление символа в буфер и инкремент счетчика длины.
    }
    nodeValue[valueLength] = '\0'; // Добавление нулевого символа в конец строки для обозначения конца C-строки.

    // Создание нового узла с разобранным именем.
    TreeNode* node = createNode(nodeValue);

    // Если текущий символ '(', начинаем парсинг дочерних узлов.
    if (**str == '(') {
        (*str)++; // Пропуск символа '('.
        while (1) { // Бесконечный цикл для чтения дочерних узлов.
            TreeNode* child = parseExpression(str); // Рекурсивный вызов функции для парсинга дочернего узла.
            if (child) { // Если дочерний узел не NULL, добавляем его к родителю.
                addChild(node, child);
            }
            if (**str == ')') { // Если текущий символ ')', это означает конец группы дочерних узлов.
                (*str)++; // Пропуск символа ')'.
                break; // Выход из цикла.
            }
            if (**str == ',') { // Если текущий символ ',', переходим к следующему дочернему узлу.
                (*str)++;
            } else {
                // Синтаксическая ошибка в выражении.
                fprintf(stderr, "Mismatched parentheses or missing comma in expression\n"); // Вывод сообщения об ошибке.
                freeTree(node); 
                exit(EXIT_FAILURE);
            }
        }
    }
    return node; // Возвращение построенного узла дерева.
}


// Функция для преобразования выражения в строковом виде в дерево.
TreeNode* parseExpressionToTree(const char *expr) {
    const char *str = expr; // Инициализация указателя str для последующего обхода.
    return parseExpression(&str); // Вызов функции parseExpression с адресом указателя str.
}

int main(int argc, char **argv) {
    // Проверка на корректное количество аргументов командной строки.
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Считывание путей к входному и выходному файлам из аргументов командной строки.
    const char *inputFilePath = argv[1];
    const char *outputFilePath = argv[2];

    // Открытие входного файла для чтения.
    FILE *inputFile = fopen(inputFilePath, "r");
    // Проверка успешности открытия входного файла.
    if (!inputFile) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }
    // Открытие выходного файла для записи.
    FILE *outputFile = fopen(outputFilePath, "w");
    if (!outputFile) {
        perror("Error opening output file");
        fclose(inputFile);
        return EXIT_FAILURE;
    }
    // Буфер для хранения одной строки из файла.
    char line[1024];
    // Цикл чтения строк из входного файла.
    while (fgets(line, sizeof(line), inputFile)) {
        // Преобразование строки в дерево.
        TreeNode *tree = parseExpressionToTree(line);
        // Печать дерева в выходной файл.
        printTree(outputFile, tree, 0);
        // Вывод пустой строки для разделения деревьев.
        fprintf(outputFile, "\n");
        // Освобождение памяти, занятой деревом.
        freeTree(tree);
    }
    fclose(outputFile);
    fclose(inputFile);
    return EXIT_SUCCESS;
}
