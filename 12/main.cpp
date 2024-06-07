#include <iostream>
#include <set> //контейнер std::set, представляющий множество уникальных и отсортированных элементов.
#include <fstream>
#include <sstream>
#include <vector>  //динамический массив 


class Messages
{
public:

    typedef struct message
    {
        std::string name;        // Имя пользователя
        size_t date = 0;         // Дата сообщения в формате целого числа
        size_t time = 0;         // Время сообщения в миллисекундах
        std::string content;     // Текст сообщения
        bool operator < (const message& other) const {
            if (date != other.date) {
                return date < other.date;
            }
            if (time != other.time) {
                return time < other.time;
            }
            if (name != other.name) {
                return name < other.name;
            }
            return content < other.content; // Сравнение по тексту сообщения, если все предыдущие поля равны
        }
    };

    static void Load(std::string path, std::set<Messages::message>* data);
    static void printMessage(const Messages::message* val);
    static void printMessages(std::set<Messages::message>* data);
    static void printUserMessages(std::string user, std::set<message>* data);
    static void printUserMessagesFromInterval(std::string user, size_t startdate, size_t enddate, size_t starttime, size_t endtime, std::set<Messages::message>* data);
    static void printMessagesFromInterval(size_t startdate, size_t enddate, size_t starttime, size_t endtime, std::set<Messages::message>* data);
    static void removeMessage(std::set<Messages::message>* data, std::set<Messages::message>::iterator it);
    static void removeUser(std::string user, std::set<message>* data);
    static size_t ConvertToDate(int year, int month, int day);
    static size_t ConvertToTime(int hour, int minute, int second, int milisecond);

private:
    static void GetValuesFromDate(size_t time, int* year, int* month, int* day); // Метод для извлечения значений даты из size_t формата
    static size_t GetDateFromString(std::string lexem); // Метод для извлечения даты из строки
    static void GetValuesFromTime(size_t time, int* hour, int* minute, int* second, int* milisecond); // Метод для извлечения времени из size_t формата
    static size_t GetTimeFromString(std::string lexem); // Метод для извлечения времени из строки
    static message GetMessageObject(std::string line); // Метод для создания объекта сообщения из строки
};


void Messages::Load(std::string path, std::set<Messages::message> * data)
{
    std::string line; // Текущая строка текста из файла
    std::ifstream in(path); // Открывает файловый поток чтения
    if (!in.is_open()) // Проверка, успешно ли открылся файл
        throw std::logic_error("File is not open"); // Если файл не удалось открыть, бросаем исключение
    while (std::getline(in, line)) // Чтение файла построчно, до конца файла
    {
        try // Проводим обработку строки в блоке try-catch для обработки потенциальных ошибок
        {
            auto obj = GetMessageObject(line); // Парсим строку и получаем объект сообщения
            data->insert(obj); // Вставляем объект сообщения в множество `data`
        }
            // Ловим все исключения, возникающие при обработке строки
        catch (std::exception e)
        {
            throw; // Повторно выбрасываем пойманное исключение, не обрабатывая его на месте
        }
    }
    in.close(); // Закрываем файловый поток
}

Messages::message Messages::GetMessageObject(std::string line)
{
    Messages::message message; // Создаем объект сообщения, который будем заполнять
    std::string lexem; // Строковая переменная для хранения отдельных лексем
    std::stringstream ss; // Создаем строковый поток для работы с `line`
    ss << line; // Записываем содержимое строки в поток

    std::getline(ss, lexem, ' '); // Считываем первую лексему (имя), разделенную пробелом
    message.name = lexem; // Устанавливаем логин в сообщение

    std::getline(ss, lexem, ' '); // Считываем следующую лексему (дату), разделенную пробелом
    try
    {
        message.date = GetDateFromString(lexem); // Преобразуем строку в дату
    }
    catch (std::invalid_argument e)
    {
        throw; // Если возникает ошибка в преобразовании, выбрасываем исключение
    }

    std::getline(ss, lexem, ' '); // Считываем следующую лексему (время), разделенную пробелом
    try
    {
        message.time = GetTimeFromString(lexem); // Преобразуем строку в время
    }
    catch (std::invalid_argument e)
    {
        throw; // Если возникает ошибка в преобразовании, выбрасываем исключение
    }

    std::getline(ss, lexem, ':'); // Считываем оставшуюся часть (текст сообщения), до двоеточия
    message.content = lexem; // Устанавливаем текст сообщения

    return message; // Возвращаем заполненный объект сообщения
}


void Messages::printMessages(std::set<Messages::message>* data) // Просто печать всех сообщений из инпута
{
    // Проходит по всем элементам в множестве сообщений
    for (auto& val : *data)
    {
        // Печатает каждое сообщение, вызывая функцию `printMessage`
        printMessage(&val);
    }
}

void Messages::printUserMessages(std::string user, std::set<Messages::message>* data)
{
    // Проходит по всем элементам в множестве сообщений
    for (auto& val : *data)
    {
        // Если логин сообщения совпадает с заданным пользователем
        if (val.name == user)
            // Печатает сообщение, вызывая функцию `printMessage`
            printMessage(&val);
    }
}

void Messages::printMessage(const Messages::message * val)
{
    int year, month, day, hour, minute, second, milisecond;

    // Извлекает значения даты из строки в формате `val->date`
    GetValuesFromDate(val->date, &year, &month, &day);

    // Извлекает значения времени из строки в формате `val->time`
    GetValuesFromTime(val->time, &hour, &minute, &second, &milisecond);

    // Печатает сообщение в консоль с форматированием
    std::cout
            << "Message from "
            << val->name
            << "\t"
            << year << "." << month << "." << day << " "
            << hour << ":" << minute << ":" << second << ":" << milisecond <<" \t"
            << val->content
            <<"\n";
}

void Messages::printUserMessagesFromInterval(std::string user, size_t startdate, size_t enddate, size_t starttime, size_t endtime,  std::set<Messages::message>* data)
{
    // Проходит по всем элементам в множестве сообщений
    for (auto& val : *data)
    {
        // Проверка логина и интервала даты и времени
        if (val.name == user && (val.date > startdate && val.date < enddate || val.date == startdate && val.time > starttime || val.date == enddate && val.time < endtime))
        {
            // Печатает сообщение, если оно соответствует критериям
            printMessage(&val);
        }
    }
}


void Messages::printMessagesFromInterval(size_t startdate, size_t enddate, size_t starttime, size_t endtime, std::set<Messages::message>* data)
{
    // Проходит по всем элементам в множестве сообщений
    for (auto& val : *data)
    {
        // Проверка интервала даты и времени
        if (val.date > startdate && val.date < enddate || val.date == startdate && val.time > starttime || val.date == enddate && val.time < endtime)
        {
            // Печатает сообщение, если оно соответствует критериям
            printMessage(&val);
        }
    }
}

void Messages::removeMessage(std::set<Messages::message>* data, std::set<Messages::message>::iterator msg)
{
    // Удаляет элемент из множества сообщений по итератору
    data->erase(msg);
}

void Messages::removeUser(std::string user, std::set<Messages::message>* data)
{
    std::vector <std::set<Messages::message>::iterator> iterators; // Вектор для хранения итераторов на сообщения, которые нужно удалить
    auto iter{ data->begin() }; // Итератор для прохода по множеству
    while (iter != data->end()) // Цикл проходит по всем сообщениям в множестве
    {
        if (iter->name == user)
        {
            // Сохраняет итератор на это сообщение
            iterators.push_back(iter);
        }
        // Переходит к следующему сообщению
        ++iter;
    }
    for (auto x : iterators) // Удаляет все сообщения, итераторы на которые были сохранены
    {
        data->erase(x);
    }
}

size_t Messages::ConvertToDate(int year, int month, int day)
{
    // Преобразует год, месяц и день в формат YYMMDD
    return year * 10000 + month * 100 + day;
}

void Messages::GetValuesFromDate(size_t time, int* year, int* month, int* day)
{
    *day = time % 100; // Вычисляет день, используя остаток от деления на 100.
    time /= 100; //Удаляет последние две цифры (день) из `time`.
    *month = time % 100; // Вычисляет месяц как остаток от деления на 100.
    time /= 100; // Удаляет последние две цифры (месяц) из `time`
    *year = time; // Остаток чисел представляет год
}
size_t Messages::GetDateFromString(std::string lexem)
{
    int year, month, day;
    std::string part; // Временная переменная для хранения частей строки
    std::stringstream ss; // Инициализирует строковый поток `ss` значением `lexem`
    ss << lexem;
    try
    {
        std::getline(ss, part, '/'); // Извлекает день из потока `ss` и преобразует его в целое число
        day = stoi(part); // преобразование в инт
        std::getline(ss, part, '/');
        month = stoi(part);
        std::getline(ss, part, '/');
        year = stoi(part);
    }
    catch (std::invalid_argument e)
    {
        return 0; // Если при преобразовании строки в число возникает исключение, возвращается 0.
    }
    return ConvertToDate(year, month, day); // Возвращает значение в формате даты (YYMMDD), используя функцию `ConvertToDate`.
}

size_t Messages::ConvertToTime(int hour, int minute, int second, int milisecond)
{
    return hour * 10000000 + minute * 100000 + second*1000 + milisecond;
    //Возвращает время в формате HHMMSSms, умножая часы на 10000000, добавляя минуты, умноженные на 100000, секунды, умноженные на 1000, и миллисекунды.
}

void Messages::GetValuesFromTime(size_t time, int *hour, int* minute, int* second, int* milisecond)
{
    *milisecond = time % 1000; // Вычисляет миллисекунды как остаток от деления на 1000.
    time /= 1000; // Удаляет последние три цифры (миллисекунды) из `time`
    *second = time % 100; // Вычисляет секунды как остаток от деления на 100
    time /= 100; // Удаляет последние две цифры (секунды) из `time`
    *minute = time % 100; // Вычисляет минуты как остаток от деления на 100.
    time /= 100; // Удаляет последние две цифры (минуты) из `time`.
    *hour = time; // Остаток чисел представляет часы
}

size_t Messages::GetTimeFromString(std::string lexem)
{
    int hour, minute, second, milisecond;
    std::string part; // Хранение частей строки
    std::stringstream ss; //Инициализирует строковый поток `ss` значением строки `lexem`.
    ss << lexem;
    try
    {
        std::getline(ss, part, '/'); //  Извлекает часы и преобразует их в целое число
        hour = stoi(part);
        std::getline(ss, part, '/');
        minute = stoi(part);
        std::getline(ss, part, '/');
        second = stoi(part);
        std::getline(ss, part, '/');
        milisecond = stoi(part);
    }
    catch (std::invalid_argument e)
    {
        return 0; // Если при преобразовании строки в число возникает исключение, возвращается 0.
    }
    return ConvertToTime(hour, minute, second, milisecond);
    // Возвращает значение в формате времени (HHMMSSms), используя функцию `ConvertToTime`
}

int main()
{
    std::set<Messages::message>  data; // Объявление множества data, которое хранит объекты типа Messages::message.
    // std::set обеспечивает хранение уникальных значений в отсортированном порядке.

    Messages::Load("input.txt", &data); // Вызов функции Load класса Messages,
    // которая загружает сообщения из файла input.txt и сохраняет их в контейнере data.




    std::cout << "The initial list of messages:\n"; // Вывод первоначального списка сообщений
    Messages::printMessages(&data);

    std::cout << "\nMessage from Christina:\n";
    Messages::printUserMessages("Christina", & data);

    std::cout << "\nAll message from 10.10.2023 to 15.10.2023:\n";
    Messages::printMessagesFromInterval(Messages::ConvertToDate(2023, 10, 10),
                                        Messages::ConvertToDate(2023, 10, 15),  Messages::ConvertToTime(8, 0, 0, 0),
                                        Messages::ConvertToTime(15, 0, 0, 0), &data);

    std::cout << "\nAll message from Bob from 10.10.2023 to 15.10.2023:\n";
    Messages::printUserMessagesFromInterval("Bob", Messages::ConvertToDate(2023, 10, 10),
                                            Messages::ConvertToDate(2023, 10, 15), Messages::ConvertToTime(8, 0, 0, 0),
                                            Messages::ConvertToTime(15, 0, 0, 0), &data);

    Messages::removeMessage(&data, data.begin());
    Messages::removeUser("Sergey", &data);
    std::cout << "\nAll messages after remove:\n";
    Messages::printMessages(&data);

}