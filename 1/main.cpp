#include <iostream>
#include <map>       // хранение пар ключ-значение.
#include <string>
#include <set>       //контейнер std::set, представляющий множество уникальных и отсортированных элементов.
#include <sstream>
#include <fstream>
#include <vector>    // динамический массив.

class Expression
{
private:
    // Статический контейнер, хранящий переменные и их значения типа float.
    static std::map <std::string, float> variables;

    // Статический контейнер, хранящий функции. Ключ - имя функции,
    // значение - пара, где первый элемент - строка с телом функции,
    // второй элемент - множество строк с именами аргументов функции.
    static std::map <std::string, std::pair<std::string, std::set<std::string>>> methods;
    static float getVariableValue(std::string str); // получение значения переменной по ее имени.
    static std::pair<std::string, std::set<std::string>> getMethodValue(std::string str); // получение значения функции по ее имени.
    // Метод для замены вызова функции в строке выражением, которое нужно вычислить.
    static std::string getMethodReplacement(std::string *name, std::vector<std::string>* replacement);
    // Метод для замены переменной в строке выражением, вычисленным на основе оригинальных переменных и замен.
    static std::string getVariableReplacement(std::string val, std::set<std::string>* original, std::vector<std::string>* replacement);
    // Метод для выполнения арифметической операции над двумя числами.
    static float applyOperation(float a, float b, char op);
    // Метод для проверки, является ли строка числом.
    static bool isNumber(const std::string& s);
    // Метод для вычисления значения операнда из строки.
    static float calculateOperand(std::string cmd);
    // Метод для вычисления значения выражения из строки.
    static float calculateExpression(std::string cmd);
    // Метод для обработки и выполнения команды "print".
    static void startfuncPrint(std::string line);
    // Метод для добавления функций из строки.
    static void appendMethodsFromString(std::string line);
    // Метод для добавления переменных из строки.
    static void appendVariablesFromString(std::string line);
    // Метод для получения имени переменной и выражения для вычисления из строки присваивания.
    static void getAssignmentExpressionFromString(std::string line, std::string* name, std::string* calc);

public:
    static void execute(std::string cmd);
    static void printVariables();
};

std::map<std::string, float> Expression::variables; // Инициализация статического контейнера переменных.
std::map <std::string, std::pair<std::string, std::set<std::string>>> Expression::methods; // Инициализация статического контейнера функций.

void Expression::execute(std::string commands)
{
    std::ifstream in(commands); // Открывает файл с именем, переданным в аргументе commands.
    if (!in.is_open()) throw std::logic_error("File is not open");
    std::string line; // для хранения отдельных строк из файла.
    while (std::getline(in, line))  // читает файл построчно.
    {
        // Если строка содержит символы '(' и '):', добавляет метод.
        if (line.find("(") > 0 && line.find("):") != std::string::npos)
        {
            appendMethodsFromString(line);
            continue;
        }
        // Если строка содержит символы '(' и ')=', добавляет переменную.
        if (line.find("(") > 0 && line.find(")=") != std::string::npos)
        {
            try
            {
                appendVariablesFromString(line);
            }
            catch (std::exception e)
            {
                throw;
            }
            continue;
        }
        // Если строка содержит символ '=', значит это присваивание переменной.
        if (line.find('=') != std::string::npos)
        {
            std::string name, cmd;
            // Извлекает имя переменной и выражение для вычисления из строки.
            getAssignmentExpressionFromString(line, &name, &cmd);
            try
            {
                // Вычисляет значение выражения и присваивает его переменной.
                variables[name] = calculateExpression(cmd);
            }
            catch (const std::exception e)
            {
                throw; // Повторно выбрасывает пойманное исключение.
            }
            continue; // Переходит к следующей итерации цикла.
        }
        // Если строка содержит "print", обрабатывает команду "print".
        if (line.find("print") != std::string::npos)
        {
            try
            {
                startfuncPrint(line);
            }
            catch (const std::exception& e)
            {
                throw;
            }
            continue;
        }
    }
}

void Expression::appendVariablesFromString(std::string line)
{
    std::stringstream ss;  // Создаем строковый поток для обработки строки.
    std::string name;  // Инициализируем переменную для хранения имени переменной.
    bool recorded = false;  // Флаг для отслеживания, записано ли значение.
    for (auto c : line)  // Проходим по каждому символу в строке.
    {
        // Если имя переменной еще не записано и найден символ '(', записываем имя переменной.
        if (!recorded && c == '(')
        {
            name = ss.str(); // Получаем имя переменной из потока.
            ss.str(""); // Очищаем поток.
            continue; // Переходим к следующему символу.
        }
        // Если значение еще не записано и найден символ '=', переходим к чтению значения.
        if (!recorded && c == '=')
        {
            recorded = true; // Устанавливаем флаг, что значение будет записано.
            ss.str(""); // Очищаем поток.
            continue; // Переходим к следующему символу.
        }
        // Если найден символ ';', конец строки, выходим из цикла.
        if (c == ';')
        {
            break;
        }
        ss << c;  // Добавляем текущий символ в поток.
    }
    try
    {
        // Преобразуем строку из потока в число и сохраняем его в переменной с именем name.
        variables[name] = std::stof(ss.str());
    }
    catch (const std::exception)
    {
        // Если преобразование не удалось, выбрасываем исключение с сообщением "Invalid argument".
        throw std::logic_error("Invalid argument");
    }
}

void Expression::appendMethodsFromString(std::string line)
{
    std::stringstream ss;  // Создаем строковый поток для обработки строки.
    std::string name;  // Инициализируем переменную для хранения имени метода.
    bool variablesRecordMode = false;  // Флаг для отслеживания режима записи переменных.
    bool recorded = false;  // Флаг для отслеживания записи тела метода.
    for (auto c : line)  // Проходим по каждому символу в строке.
    {
        // Если имя метода еще не записано и найден символ '(', записываем имя метода.
        if (!recorded && c == '(')
        {
            name = ss.str(); // Получаем имя метода из потока.
            ss.str(""); // Очищаем поток.
            variablesRecordMode = true; // Переходим в режим записи переменных.
            continue; // Переходим к следующему символу.
        }
        // Если режим записи переменных и найден символ ',', добавляем переменную метода.
        if (!recorded && c == ',' && variablesRecordMode)
        {
            methods[name].second.insert(ss.str()); // Добавляем переменную в сет переменных метода.
            ss.str(""); // Очищаем поток.
            continue; // Переходим к следующему символу.
        }
        // Если режим записи переменных и найден символ ')', завершаем запись переменных.
        if (!recorded && c == ')')
        {
            methods[name].second.insert(ss.str()); // Добавляем переменную в сет переменных метода.
            ss.str(""); // Очищаем поток.
            variablesRecordMode = false; // Выходим из режима записи переменных.
            continue; // Переходим к следующему символу.
        }
        // Если тело метода еще не записано и найден символ ':', начинаем запись тела метода.
        if (!recorded && c == ':')
        {
            recorded = true; // Устанавливаем флаг, что тело метода будет записано.
            ss.str(""); // Очищаем поток.
            continue; // Переходим к следующему символу.
        }
        // Если найден символ ';', конец строки, выходим из цикла.
        if (c == ';')
        {
            break;
        }
        ss << c;  // Добавляем текущий символ в поток.
    }
    methods[name].first = ss.str();  // Назначаем содержимое потока телом метода.
}

// Метод для извлечения имени переменной и выражения для вычисления из строки
void Expression::getAssignmentExpressionFromString(std::string line, std::string* name, std::string* calc)
{
    std::stringstream ss;  // Создаем строковый поток для обработки строки
    bool recorded = false;  // Флаг для отслеживания, записано ли имя переменной
    for (auto c : line)  // Проходим по каждому символу в строке
    {
        // Если имя переменной еще не записано и найден символ '=', записываем имя переменной
        if (!recorded && c == '=')
        {
            *name = ss.str(); // Получаем имя переменной из потока и сохраняем в указатель 'name'
            ss.str(""); // Очищаем поток
            recorded = true; // Устанавливаем флаг, что имя переменной записано
            continue; // Переходим к следующему символу
        }
        // Если найден символ ';', конец строки, выходим из цикла
        if (c == ';')
        {
            break;
        }
        ss << c;  // Добавляем текущий символ в поток
    }
    *calc = ss.str();  // Записываем оставшееся выражение в указатель 'calc'
}


float Expression::calculateExpression(std::string cmd)
{
    std::cout << "The expression to be calculated: " << cmd << "\n" << "-------------------" << "\n";  // Выводим команду для вычисления в консоль
    size_t inside = false;  // Переменная для отслеживания нахождения внутри скобок
    std::vector<float> numbers;  // Векторы для чисел и операций
    std::vector<char> operations;
    std::stringstream ss;  // Буферный поток для накопления символов и конструирования числовых строк
    size_t count = 0;  // Счетчик для внешних операций (не внутри скобок)
    // Проходим по каждому символу строки `cmd`
    for (auto c : cmd)
    {
        // Если символ равен '(', увеличиваем счетчик вложенности
        if (c == '(')
        {
            ++inside;
            continue;
        }
        // Если символ равен ')', уменьшаем счетчик вложенности
        if (c == ')')
        {
            --inside;
            continue;
        }
        // Если не находимся внутри скобок, увеличиваем счетчик внешних операций
        if (inside == 0) ++count;
    }
    // Если нет внешних операций и строка окружена скобками, удаляем их
    if (count == 0 && cmd[0] == '(' && cmd[cmd.size() - 1] == ')')
    {
        cmd = cmd.substr(1, cmd.size() - 2);
    }
    // Проходим по каждому символу строки `cmd` снова
    for (auto c : cmd)
    {
        if (c == '(')
        {
            ++inside;
        }
        if (c == ')')
        {
            --inside;
        }
        // Если не находимся внутри скобок и текущий символ является оператором
        if (inside == 0 && (c == '*' || c == '/' || c == '+' || c == '-'))
        {
            // Добавляем оператор в вектор `operations`
            operations.push_back(c);
            float val;
            try {
                // Преобразуем строку в число и сохраняем его в вектор `numbers`
                val = calculateOperand(ss.str());
            }
            catch (const std::exception& e) {
                throw;
            }
            numbers.push_back(val);
            ss.str(""); // Очищаем строковый поток для следующего числа
            continue;
        }
        ss << c; // Добавляем текущий символ в поток
    }
    try {
        // Преобразуем последний буферный поток в число и добавляем его в `numbers`
        numbers.push_back(calculateOperand(ss.str()));
    }
    catch (const std::exception& e) {
        throw;
    }
    float first, second;  // Порядок выполнения операций (сначала умножение/деление, затем сложение/вычитание)
    // Выполняем все операции умножения/деления
    for (int i = 0; i < operations.size(); i++)
    {
        if (operations.at(i) == '*' || operations.at(i) == '/')
        {
            first = numbers.at(i);
            second = numbers.at(i + 1);
            // Применяем операцию и сохраняем результат
            numbers.at(i) = applyOperation(first, second, operations.at(i));
            numbers.erase(std::next(numbers.begin(), i + 1));
        }
    }
    // Удаляем выполненные операции умножения/деления из вектора операций
    for (int i = 0; i < operations.size(); i++)
    {
        if (operations.at(i) == '*' || operations.at(i) == '/')
        {
            operations.erase(std::next(operations.begin(), i));
        }
    }
    // Выполняем все операции сложения/вычитания
    for (int i = 0; i < operations.size(); i++)
    {
        if (operations.at(i) == '+' || operations.at(i) == '-')
        {
            first = numbers.at(i);
            second = numbers.at(i + 1);
            // Применяем операцию и сохраняем результат
            numbers.at(i) = applyOperation(first, second, operations.at(i));
            numbers.erase(std::next(numbers.begin(), i + 1));
        }
    }
    std::cout << "The result of calculations: " << numbers.at(0) << "\n" << "-------------------" << "\n"; // Выводим результат в консоль
    return numbers.at(0);  // Возвращаем результат
}

float Expression::calculateOperand(std::string cmd)
{
    // Проверяем, является ли строка числом
    if (isNumber(cmd))
    {
        // Преобразуем строку в число и возвращаем его
        return atof(cmd.c_str());
    }
    // Проверяем, нет ли в строке скобок (значит, это переменная)
    if (cmd.find('(') == std::string::npos && cmd.find(')') == std::string::npos)
    {
        try
        {
            // Пытаемся получить значение переменной
            return getVariableValue(cmd);
        }
        catch (const std::exception& e)
        {
            throw;
        }
    }
    // Проверка на окружение скобками, то есть выражение должно быть внутри
    if (cmd[0] == '(' && cmd[cmd.size() - 1] == ')')
    {
        try
        {
            // Вызываем метод для вычисления выражения внутри скобок
            return calculateExpression(cmd);
        }
        catch (const std::exception& ex)
        {
            throw;
        }
    }
    std::stringstream ss;  // Строковый поток для накопления символов
    std::string name;  // Для хранения имени метода или переменной
    std::vector<std::string> replacement;  // Вектор для хранения строк, представляющих аргументы метода
    bool isNameRecorded = false;  // Флаг, который указывает, записано ли имя метода/переменной
    size_t depth = 0;  // Переменная для отслеживания глубины вложенности (количество открытых скобок)
    // Проходим по каждому символу строки
    for (auto c : cmd)
    {
        // Уменьшаем глубину, если встречаем закрывающую скобку
        if (c == ')') --depth;
        // Увеличиваем глубину, если встречаем открывающую скобку
        if (c == '(')
        {
            ++depth;
            // Если имя ещё не записано, сохраняем его
            if (isNameRecorded == false)
            {
                // Устанавливаем флаг, что имя записано
                isNameRecorded = true;
                // Сохраняем имя метода/переменной
                name = ss.str();
                // Очищаем строковый поток для накопления аргументов
                ss.str("");
                continue;
            }
        }
        // Если имя уже записано и текущий символ - запятая или закрывающая скобка на текущей вложенности
        if (isNameRecorded && (c == ',' || (c == ')' && depth == 0)))
        {
            try
            {
                // Вычисляем выражение внутри аргумента и добавляем в `replacement`
                replacement.push_back(std::to_string(calculateExpression(ss.str())));
            }
            catch (const std::exception& ex)
            {
                throw;
            }
            // Очищаем строковый поток для следующего аргумента
            ss.str("");
            continue;
        }
        ss << c;  // Добавляем текущий символ в строковый поток
    }
    std::string res;
    try
    {
        res = getMethodReplacement(&name, &replacement);  // Получаем строковую замену для метода с его аргументами
    }
    catch (const std::exception& e)
    {
        throw;
    }
    try
    {
        return calculateExpression(res);  // Вычисляем конечное выражение после замены и возвращаем результат
    }
    catch (const std::exception& ex)
    {
        throw;
    }
}


std::string Expression::getMethodReplacement(std::string* name, std::vector<std::string>* replacement)
{
    std::pair<std::string, std::set<std::string>> methodValues;  // Переменная для хранения тела метода и его аргументов
    try
    {
        methodValues = getMethodValue(*name); // Получаем тело метода (строка) и список его аргументов
    }
    catch (const std::exception& e)
    {
        throw;
    }
    std::string result = methodValues.first;  // Получаем тело метода (строка)
    std::set<std::string>* original = &methodValues.second;  // Получаем оригинальный набор аргументов метода
    std::stringstream ss, finalFunction; // Создаём строковый поток для выражения и финальной функции
    // Проверяем соответствие количества аргументов оригинала и замен
    if (original->size() != replacement->size())
        throw std::logic_error("Incorrect function arguments");
    // Проходим по каждой букве в строке тела метода
    for (auto& c : result)
    {
        // Проверяем, является ли символ одной из специальных операций или скобкой
        if (c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/')
        {
            // Из строки, собранной в ss, получаем замены переменных и добавляем в итоговую функцию
            finalFunction << getVariableReplacement(ss.str(), original, replacement);
            // Добавляем текущий специальный символ в итоговую функцию
            finalFunction << c;
            // Очищаем строковый поток для следующей части переменной или идентификатора
            ss.str("");
        }
        else
        {
            // Накопим текущий символ в строковый поток
            ss << c;
            // Если это последний символ строки, то добавляем и его в функцию
            if (&c == &result.back())
                finalFunction << getVariableReplacement(ss.str(), original, replacement);
        }
    }
    // Сформированную строку функции возвращаем в виде результата
    return finalFunction.str();
}


std::string Expression::getVariableReplacement(std::string val, std::set<std::string>* original, std::vector<std::string>* replacement)
{
    int i = 0;  // Индекс для замены переменной
    // Проходим по каждому элементу оригинального набора аргументов метода
    for (auto x : *original)
    {
        // Если переменная совпадает с текущим именем, возвращаем соответствующую замену из вектора
        if (x == val) return replacement->at(i);
        // Переходим к следующему элементу в заменах
        ++i;
    }
    return val;  // Если совпадений не найдено, возвращаем исходное значение
}


float Expression::getVariableValue(std::string str)
{
    float v; // Переменная для хранения значения
    try
    {
        // Получаем значение переменной из словаря
        v = variables[str];
    }
    catch (const std::exception& e)
    {
        // Если переменная не существует, выбрасываем логическую ошибку
        throw std::logic_error("Variable does not exist");
    }
    return v; // Возвращаем найденное значение переменной
}

std::pair<std::string, std::set<std::string>> Expression::getMethodValue(std::string name)
{
    std::pair<std::string, std::set<std::string>> v; // Переменная для хранения значения (тела метода и его аргументов)
    try
    {
        // Получаем тело метода и его аргументы
        v = methods[name];
    }
    catch (const std::exception& e)
    {
        // Если метод не существует, выбрасываем логическую ошибку
        throw std::logic_error("Method does not exist");
    }
    return v;  // Возвращаем найденное значение метода
}

void Expression::startfuncPrint(std::string line)
{
    std::stringstream ss;  // Создаём строковый поток из переданной строки
    ss << line;  // Записываем строку в поток
    std::getline(ss, line, ' ');  // Считываем слово из потока до пробела и записываем его в переменную `line`

    // Проверяем, равно ли считанное слово "print;"
    if (line == "print;")
    {
        // Если да, вызываем метод для печати переменных
       printVariables();
    }
    else
    {
        // Иначе, снова считываем до пробела следующее слово
        std::getline(ss, line, ' ');

        // Удаляем символ `;` в конце строки, если он присутствует
        if (line.find(";") != std::string::npos)
            line = line.substr(0, line.size() - 1);
        try
        {
            // Пытаемся получить значение переменной и вывести его на экран
            std::cout << "The value of the variable " << line << ": "<< getVariableValue(line) << "\n";
        }
        catch (const std::exception& e)
        {
            // Если переменная не найдена или возникает другая ошибка, пробрасываем исключение
            throw;
        }
    }
}

void Expression::printVariables()
{
    std::cout << "Values of variables: " << "\n";
    // Проходим по всем переменным из контейнера `variables`
    for (auto x : variables)
    {
        // Выводим имя переменной и её значение
        std::cout << x.first << "=" << x.second << "; " << "\n";
    }
    std::cout << "\n";
}

bool Expression::isNumber(const std::string& s)
{
    // Проходим по каждому символу строки
    for (auto c : s)
    {
        // Если символ не является цифрой и не точкой, возвращаем ложь
        if (!(isdigit(c) || c == '.')) return false;
    }
    // Если все символы строки - цифры или точки, возвращаем истину
    return true;
}

float Expression::applyOperation(float a, float b, char op)
{
    // Определяем операцию по символу и выполняем соответствующее действие
    switch (op)
    {
        case '+': return a + b; // Сложение
        case '-': return a - b; // Вычитание
        case '*': return a * b; // Умножение
        case '/': return a / b; // Деление
        default: return 0; // Неверная операция возвращает 0
    }
}

int main()
{
    try
    {
        Expression::execute("program.txt");
    }
    catch (std::exception e)
    {
        // Если возникает исключение, выводим его сообщение
        std::cout << e.what();
    }
}