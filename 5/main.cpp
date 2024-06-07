//Иванов Иван Иванович {
//Договор No1 нач. 01.01.2018 кон. 02.03.2018 Работа 123 Стоимость 12500;
//Договор No12 нач. 18.04.2019 кон. 20.06.2019 Работа 1234 Стоимость 1550;
//Договор No14 нач. 19.05.2019 кон. нв Работа 1235 Стоимость 17500;
//}
//Петров Петр Петрович {
//Договор No2 нач. 05.02.2018 кон. 10.04.2018 Работа 234 Стоимость 8000;
//Договор No15 нач. 20.06.2019 кон. 22.09.2019 Работа 678 Стоимость 9500;
//}

#include <iostream>
#include <map>         // хранение пар ключ-значение.
#include <string>
#include <vector>      // динамический массив.
#include <fstream>
#include <sstream>     //   std::istringstream, обработка строк как потоков.
#include <algorithm>   //   std::max_element.
#include <memory>      //   умные указатели, std::unique_ptr.
#include <limits>      //   лимиты различных типов данных.
#include <ctime>       //   работа с датами и временем, std::tm и функции mktime.

struct Contract {
    std::string contract_number;  // Номер контракта
    std::string start_date;       // Дата начала контракта
    std::string end_date;         // Дата окончания контракта
    std::string job;              // Описание работы по контракту
    double cost;                  // Стоимость контракта

    // Конструктор, инициализирующий поля структуры
    Contract(std::string cn, std::string sd, std::string ed, std::string j, double c)
            : contract_number(cn), start_date(sd), end_date(ed), job(j), cost(c) {}
};

struct Employee {
    std::string fullname;           // Полное имя сотрудника
    std::vector<Contract> contracts; // Вектор контрактов сотрудника
    Employee(std::string fn) : fullname(fn) {}   // Конструктор, инициализирующий имя сотрудника
    double total_cost() {  // общая стоимость всех контрактов сотрудника
        double sum = 0; // сумма стоимости контрактов
        for (const auto& contract : contracts) { // Перебираем все контракты
            sum += contract.cost; // Добавляем стоимость текущего контракта к сумме
        }
        return sum; // Возвращаем общую стоимость
    }
    // Метод, возвращающий указатель на самый дорогой контракт сотрудника
    Contract* most_expensive_contract() {
        if (contracts.empty()) return nullptr; // Если нет контрактов, возвращаем nullptr
        return &*std::max_element(contracts.begin(), contracts.end(), [&](const Contract& a, const Contract& b) {
            return a.cost < b.cost; // Сравниваем контракты по стоимости
        });
    }
    // Метод, возвращающий указатель на самый длинный контракт сотрудника
    Contract* longest_contract() {
        if (contracts.empty()) return nullptr; // Если нет контрактов, возвращаем nullptr
        // Лямбда-функция для парсинга даты из строки
        auto parse_date = [](const std::string& date) -> std::tm {
            std::tm tm = {}; // Инициализируем структуру std::tm нулями
            std::istringstream ss(date); // Создаем поток для парсинга строки даты
            if (date != "нв") ss >> std::get_time(&tm, "%d.%m.%Y"); // Парсим дату, если она не равна "нв" (настоящее время)
            return tm; // Возвращаем структуру std::tm
        };
        // Находим самый длинный контракт
        return &*std::max_element(contracts.begin(), contracts.end(), [&](const Contract& a, const Contract& b) {
            std::tm start_a = parse_date(a.start_date); // Парсим дату начала контракта a
            std::tm end_a = a.end_date == "нв" ? std::tm() : parse_date(a.end_date); // Парсим дату окончания контракта a (если "нв", используем пустую структуру)
            std::tm start_b = parse_date(b.start_date); // Парсим дату начала контракта b
            std::tm end_b = b.end_date == "нв" ? std::tm() : parse_date(b.end_date); // Парсим дату окончания контракта b (если "нв", используем пустую структуру)

            auto duration_a = mktime(&end_a) - mktime(&start_a); // Вычисляем продолжительность контракта a в секундах
            auto duration_b = mktime(&end_b) - mktime(&start_b); // Вычисляем продолжительность контракта b в секундах

            return duration_a < duration_b; // Сравниваем продолжительности контрактов
        });
    }
};


class Company { // Объявление класса Company, представляющего компанию с сотрудниками и методами для управления данными о них
    std::map<std::string, std::unique_ptr<Employee>> employees; // связь имени сотрудника с уникальным указателем на объект Employee

public:
    // Метод для загрузки данных из файла
    void load_data(const std::string& filename) {
        std::ifstream file(filename); // Открываем файл для чтения
        if (!file) {
            std::cerr << "Cannot open file " << filename << std::endl;
            return;
        }
        std::string line; // Строка для хранения текущей строки из файла
        Employee* current_employee = nullptr; // Указатель на текущего сотрудника, для которого добавляются контракты
        while (getline(file, line)) { // Читаем файл построчно
            if (line.empty()) continue; // Пропускаем пустые строки
            if (line.back() == '{') { // Если строка заканчивается на '{', это начало записи сотрудника
                std::string fullname = line.substr(0, line.length() - 2); // Извлекаем имя сотрудника (без последних двух символов: ' {' )
                employees[fullname] = std::make_unique<Employee>(fullname); // Создаем нового сотрудника и добавляем его
                current_employee = employees[fullname].get(); // Устанавливаем текущего сотрудника
            } else if (line == "}") { // Если строка содержит только '}', это конец записи сотрудника
                current_employee = nullptr; // Сбрасываем указатель на текущего сотрудника
            } else if (current_employee) { // Если есть текущий сотрудник, это строка с данными о контракте
                std::istringstream iss(line); // Создаем поток для парсинга строки
                std::string contract_word, contract_number, start_word, start_date, end_word, end_date, job_word, job, cost_word;
                double cost; // Переменные для хранения данных контракта

                iss >> contract_word >> contract_number >> start_word >> start_date >> end_word >> end_date >> job_word >> job >> cost_word >> cost; // Извлекаем данные из строки

                if (contract_word == "Договор" && start_word == "нач." && end_word == "кон." && job_word == "Работа" && cost_word == "Стоимость") { // Проверяем корректность формата строки
                    current_employee->contracts.emplace_back(contract_number, start_date, end_date, job, cost); // Добавляем контракт текущему сотруднику
                }
            }
        }
    }
    // Метод для поиска сотрудника по имени
    Employee* find_employee(const std::string& fullname) {
        auto it = employees.find(fullname); // Ищем сотрудника
        if (it == employees.end()) return nullptr; // Если сотрудник не найден, возвращаем nullptr
        return it->second.get(); // Возвращаем указатель на сотрудника
    }
    // Метод для удаления сотрудника по имени
    void delete_employee(const std::string& fullname) {
        auto it = employees.find(fullname); // Ищем сотрудника
        if (it != employees.end()) { // Если сотрудник найден
            employees.erase(it); // Удаляем запись о сотруднике из карты
            std::cout << "Employee record deleted.\n"; // Выводим сообщение об успешном удалении
        } else {
            std::cout << "Employee not found.\n"; // Выводим сообщение, если сотрудник не найден
        }
    }
};

void display_menu() {
    std::cout << "1. Display total cost of all contracts for an employee.\n";
    std::cout << "2. Display all contracts for an employee.\n";
    std::cout << "3. Find the longest contract for an employee.\n";
    std::cout << "4. Find the most expensive contract for an employee.\n";
    std::cout << "5. Delete employee record.\n";
    std::cout << "6. Exit.\n";
}

int main() {
    Company company;
    company.load_data("input.txt");
    while (true) {
        display_menu();
        int option;
        std::cout << "Enter an option: ";
        while (!(std::cin >> option) || option < 1 || option > 6) {
            std::cout << "Invalid input, please enter a number from 1 to 6: ";
            std::cin.clear(); // Сброс флага ошибки потока
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        if (option == 6) break;
        std::string fullname; // Переменная для хранения полного имени сотрудника
        std::cout << "Enter employee's full name: ";
        std::cin.ignore(); // Игнорируем оставшийся символ новой строки после ввода варианта
        std::getline(std::cin, fullname); // Чтение полного имени сотрудника
        Employee* employee = company.find_employee(fullname); // Поиск сотрудника по имени
        if (!employee && option != 5) { // Если сотрудник не найден и выбран не вариант 5 (удаление)
            std::cout << "Employee not found.\n"; // Вывод сообщения, что сотрудник не найден
            continue; // Переход к следующей итерации цикла
        }
        switch (option) {
            case 1: { // Вариант 1: расчет общей стоимости всех контрактов сотрудника
                double total_cost = employee->total_cost(); // Вызов метода для расчета общей стоимости
                std::cout << "Total cost of all contracts: " << total_cost << "\n";
                break;
            }
            case 2: { // Вариант 2: вывод информации о всех контрактах сотрудника
                for (const auto& contract : employee->contracts) { // Цикл по всем контрактам сотрудника
                    std::cout << "Contract Number: " << contract.contract_number << "\n"; // Вывод номера контракта
                    std::cout << "Start Date: " << contract.start_date << "\n"; // Вывод даты начала контракта
                    std::cout << "End Date: " << contract.end_date << "\n"; // Вывод даты окончания контракта
                    std::cout << "Job: " << contract.job << "\n"; // Вывод описания работы
                    std::cout << "Cost: " << contract.cost << "\n"; // Вывод стоимости контракта
                    std::cout << "--------------------------\n";
                }
                break;
            }
            case 3: { // Вариант 3: поиск и вывод информации о самом длительном контракте сотрудника
                Contract* longest_contract = employee->longest_contract(); // Вызов метода для поиска самого длительного контракта
                if (longest_contract) { // Если контракт найден
                    std::cout << "Longest contract: " << longest_contract->contract_number << "\n"; // Вывод номера контракта
                    std::cout << "Start Date: " << longest_contract->start_date << "\n"; // Вывод даты начала контракта
                    std::cout << "End Date: " << longest_contract->end_date << "\n"; // Вывод даты окончания контракта
                    std::cout << "Job: " << longest_contract->job << "\n"; // Вывод описания работы
                    std::cout << "Cost: " << longest_contract->cost << "\n"; // Вывод стоимости контракта
                } else { // Если контракты не найдены
                    std::cout << "No contracts found.\n"; // Вывод сообщения о отсутствии контрактов
                }
                break;
            }
            case 4: { // Вариант 4: поиск и вывод информации о самом дорогом контракте сотрудника
                Contract* most_expensive_contract = employee->most_expensive_contract(); // Вызов метода для поиска самого дорогого контракта
                if (most_expensive_contract) { // Если контракт найден
                    std::cout << "Most expensive contract: " << most_expensive_contract->contract_number << "\n"; // Вывод номера контракта
                    std::cout << "Start Date: " << most_expensive_contract->start_date << "\n"; // Вывод даты начала контракта
                    std::cout << "End Date: " << most_expensive_contract->end_date << "\n"; // Вывод даты окончания контракта
                    std::cout << "Job: " << most_expensive_contract->job << "\n"; // Вывод описания работы
                    std::cout << "Cost: " << most_expensive_contract->cost << "\n"; // Вывод стоимости контракта
                } else { // Если контракты не найдены
                    std::cout << "No contracts found.\n"; // Вывод сообщения об отсутствии контрактов
                }
                break;
            }
            case 5: { // Вариант 5: удаление сотрудника
                company.delete_employee(fullname); // Вызов метода для удаления сотрудника
                break;
            }
            default: // Обработка некорректных вариантов
                break;
        }
    }
    return 0;
}