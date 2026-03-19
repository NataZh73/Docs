// Lab3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
// Лабораторная работа 81-82.Схема БД. Основы проектирования. Меню программы
// Вариант 6.
// Файлы: Сотрудники, Проекты
// Поля:
// •Сотрудники : Сотрудник_ID, Имя, Фамилия, Проект_ID
// •Проекты : Проект_ID, Название, Дата_начала
//разработать консольное меню

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <vector>
#include <algorithm>

using namespace std;

int _stateMenu;
// Меню \033[35m
void menu() {
    //cout << GREEN << "===== МЕНЮ =====" << RESET << endl;
    cout << "\033[36m+---------------------------------+\033[0m" << endl;
    cout << "\033[46m===== МЕНЮ =====\033[0m" << endl;
    cout << "\033[36m+---------------------------------+\033[0m" << endl;
    cout << "\033[35m1.\033[0m Добавить сотрудника\n";
    cout << "\033[35m2.\033[0m Добавить проект\n";
    cout << "\033[35m3.\033[0m Назначить сотрудника на проект\n";
    cout << "\033[35m4.\033[0m Показать сотрудников\n";
    cout << "\033[35m5.\033[0m Показать проекты\n";
    cout << "\033[35m6.\033[0m Показать участие\n";
    cout << "\033[31m0.\033[0m Выход\n";
    cout << "\033[36m+---------------------------------+\033[0m" << endl;
    cout << "Ваш выбор: ";
    cin >> _stateMenu;
}


// чтение id сотрудников из файла в массив vector
vector<int> getEmployees()
{
    // Чтение данных из текстового файла 
    string filename = "Employees.txt";
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Ошибка: не удалось открыть файл " << filename << endl;
    }
    vector<int> ids;
    string line;
    getline(file, line);
    getline(file, line);

    // цикл чтения строк файла
    while (std::getline(file, line))
    {
        unsigned int id;
        // извлечение id из стороки
        int res = sscanf_s(line.c_str(), "%d ", &id);
        if (res == 1) // Проверяем успешность извлечения
        {
            ids.push_back(id);// добавить в массив
        }
    }
    file.close();

    return ids;
}

// Добавить сотрудника
int addEmployee() 
{
    vector<int> ids = getEmployees(); // чтение id сотрудников из файла

    // поиск максимального id сотрудника
    //int maxID = 0;
    //if (!ids.empty())
    //{
    //    maxID = *max_element(ids.begin(), ids.end()); // поиск максимального
    //}
    //if (!ids.empty())
    //{
    //    maxID = ids[0];
    //    for (const auto& id : ids)
    //    {
    //        if (id > maxID)
    //            maxID = id;
    //    }
    //}

    // поиск подходящего id
    sort(ids.begin(), ids.end()); // сортировка
    int newID = 1;
    for (int id : ids) // цикл по элементам массива (существующие id)
    {
        if (id == newID)
        {
            newID++;
        }
        else if (id > newID)
        {
            break;
        }
    }

    // ввод данных
    string name, surname;
    int id;
    cout << "Введите id сотрудника (" << newID <<"): ";
    cin >> id;
    cout << "Введите фамилию сотрудника: ";
    cin >> surname;
    cout << "Введите имя сотрудника: ";
    cin >> name;

    // запись в файл
    string line = to_string(id) + "\t" + surname + "\t" + name;
    const string& filename = "Employees.txt";
    ofstream file(filename, ios::app);
    if (!file.is_open()) 
    {
        cout << "Ошибка: не удалось открыть файл " << filename << endl;
        return(0);
    }
    file << line << endl;
    file.close();

    cout << "Сотрудник добавлен" << endl;
    return(1);
}

// Добавить проект
int addProject()
{
    // ввод данных
    string name, start_date;
    int id;
    cout << "Введите id проекта: ";
    cin >> id;
    cout << "Введите название проекта: ";
    cin.ignore();
    getline(cin, name);
    cout << "Введите дату начала проекта: ";
    cin >> start_date;

    // запись в файл
    string line = to_string(id) + "\t" + name + "\t\t" + start_date;
    string filename = "Projects.txt";
    ofstream file(filename, ios::app);
    if (!file.is_open())
    {
        cout << "Ошибка: не удалось открыть файл " << filename << endl;
        return(0);
    }
    file << line << endl;
    file.close();

    cout << "Проект добавлен" << endl;
    return(1);
}

// Назначить сотрудника на проект
int addEmployeeProject()
{
    // ввод данных
    int idRecord, idEmployee, idProject;
    cout << "Введите id назначения: ";
    cin >> idRecord;
    cout << "Введите id проекта: ";
    cin >> idProject;
    cout << "Введите id сотрудника: ";
    cin >> idEmployee;

    // запись в файл
    string line = to_string(idRecord) + "\t" + to_string(idEmployee) + "\t\t" + to_string(idProject);
    string filename = "EmployeeProject.txt";
    ofstream file(filename, ios::app);
    if (!file.is_open())
    {
        cout << "Ошибка: не удалось открыть файл " << filename << endl;
        return(0);
    }
    file << line << endl;
    file.close();

    cout << "Сотрудник назначен на проект" << endl;
    return(1);
}

// Вывести список сотрудников
int printEmployees() 
{
    string filename = "Employees.txt";
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Ошибка: не удалось открыть файл " << filename << endl;
        return(0);
    }
    string line;
    cout << "Список сотрудников:\n";
    while (getline(file, line)) 
    {
        cout << line << endl;
    }
    file.close();
}

// Вывести список проектов
int printProjects()
{
    string filename = "Projects.txt";
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Ошибка: не удалось открыть файл " << filename << endl;
        return(0);
    }
    string line;
    cout << "Список проектов:\n";
    while (getline(file, line))
    {
        cout << line << endl;
    }
    file.close();
}

// Вывести участие сотрудников в проектах
int printEmployeeProject()
{
    string filename = "EmployeeProject.txt";
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Ошибка: не удалось открыть файл " << filename << endl;
        return(0);
    }
    string line;
    cout << "Участие сотрудников в проектах:\n";
    while (getline(file, line))
    {
        cout << line << endl;
    }
    file.close();
}

int main()
{
    setlocale(LC_CTYPE, "RU");
    SetConsoleCP(1251);

    menu();
    while (_stateMenu != 0) 
    {

        switch (_stateMenu)
        {
        case 1:
            system("cls");   // очистка консоли
            addEmployee();   // Добавить сотрудника
            system("pause"); // задержка консоли
            system("cls");
            menu();
            break;
        case 2:
            system("cls");
            addProject();  // Добавить проект
            system("pause");
            system("cls");
            menu();
            break;
        case 3:
            system("cls");
            addEmployeeProject(); // Назначить сотрудника на проект
            system("pause");
            system("cls");
            menu();
            break;
        case 4:
            system("cls");
            printEmployees(); //  Вывести список сотрудников
            system("pause");
            system("cls");
            menu();
            break;
        case 5:
            system("cls");
            printProjects(); //  Вывести список проектов
            system("pause");
            system("cls");
            menu();
            break;
        case 6:
            system("cls");
            printEmployeeProject(); // Вывести участие сотрудников в проектах
            system("pause");
            system("cls");
            menu();
            break;
        default:
            system("cls");
            cout << "Неверно введен номер действия!" << endl;
            system("pause");
            system("cls");
            menu();
            break;
        }
    }

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
