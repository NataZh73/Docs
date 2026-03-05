// Lab2_1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
// 
 
// Лабораторная работа 3. Классы памяти
// Дополнительное задание 2.
// Система голосования
//Реализуйте подсчёт голосов за кандидатов :
//•	Статический массив для результатов голосования
//•	Глобальную переменную для количества кандидатов
//•	Локальные переменные для обработки выбора
//•	Регистровую переменную для подсчёта максимального значения


#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// максимальное количество кондидатов
static const int MAX_CANDIDATES = 20; 

//статический массив результатов голосования 
static int votes[MAX_CANDIDATES] = { 0 }; // заполняется нулями

// количество кандидатов (глобальная переменная)
int g_numCandidates = 0; 

//Функция для отображения результатов
void showResults()
{
    cout << "\n=== Результаты голосования ===\n";
    for (int i = 0; i < g_numCandidates; i++)
        cout << setw(3) << (i + 1) << ". "
        << "Кандидат " << (i + 1) << ": "
        << votes[i] << " голосов\n";
}

// Функция для поиска победителя
int findWinner()
{
    register int maxVotes = 0; // регистровая переменная
    int winnerIdx = -1;
    for (int i = 0; i < g_numCandidates; ++i)
        if (votes[i] > maxVotes) 
        { 
            maxVotes = votes[i]; 
            winnerIdx = i; 
        }
    return winnerIdx;
}

// Функция «Добавить голос»
bool addVote(int candidate)
{
    // Проверяем диапазон номера кандидата
    if (candidate < 1 || candidate > g_numCandidates) 
    {
        cerr << "Неверный номер кандидата.\n";
        return false;
    }

    // Увеличиваем счётчик голосов
    votes[candidate - 1]++;

    cout << "Голос добавлен к кандидату " << candidate << ".\n";
    return true;
}

int main()
{
    setlocale(LC_CTYPE, "Russian");

    cout << "=== Система голосования ===\n";

    int num; //локальная переменная
    cout << "Введите количество кандидатов (до " << MAX_CANDIDATES << "): ";
    cin >> num;

    if (num <= 0 || num > MAX_CANDIDATES) 
    {
        cerr << "Неверное количество кандидатов.\n";
        return 1;
    }

    g_numCandidates = num;

    char choice; //локальная переменная
    do 
    {
        
        cout << "Добавить голос? (y/n): ";
        cin >> choice;
        cin.ignore();  // очищаем буфер

        if (choice == 'y')
        {
            int candidate;
            cout << "Введите номер кандидата (1.." << g_numCandidates << "): ";
            cin >> candidate;
            cin.ignore();  // очищаем буфер

            addVote(candidate);  
        }
    } while (choice == 'y');

    //  вывод результатов голосования
    showResults();

    // определяем победителя
    int winner = findWinner();
    if (winner != -1) 
    {
        cout << "\nПобедитель: Кандидат " << (winner + 1)
            << " с " << votes[winner] << " голосами.\n";
    }
    else {
        std::cout << "\nНикаких голосов не было.\n";
    }

    return 0;
}

// Лабораторная работа 3. Классы памяти
// Дополнительное задание 4.
// Реализуйте менеджер списка покупок:
// •	Глобальный массив структур(название, категория)
// •	Статический счётчик для каждой категории
// •	Локальные переменные для ввода нового элемента
// •	Регистровую переменную для временного хранения категории

//#include <iostream>
//#include <string>
//#include <windows.h>
//
//using namespace std;
//
//const int MAX_ITEMS = 100;
//
//// Структура покупок
//struct Item 
//{
//    string name;
//    int categoryCode;
//};
//
//// Глобальный массив покупок
//Item shoppingList[MAX_ITEMS];
//
//// Статические счётчики по категориям
//static int countVegetables = 0;
//static int countFruits = 0;
//static int countDrinks = 0;
//
//// Текщее количество элементов покупки
//static int itemCount = 0;
//
//// Функция для получения имени категории по коду
//string getCategoryName(int code) 
//{
//    // Регистровая переменная для временного хранения категории
//    register string categoryName;
//
//    switch (code) 
//    {
//        case 1: categoryName = "овощи";
//        case 2: categoryName = "фрукты";
//        case 3: categoryName = "напитки";
//        default: categoryName = "неизвестно";
//    }
//    return categoryName;
//}
//
//// Добавление нового элемента в список
//void addItem(const string& name, int categoryCode)
//{
//    if (itemCount >= MAX_ITEMS) 
//    {
//        cout << "Список заполнен!\n";
//        return;
//    }
//
//    shoppingList[itemCount].name = name;
//    shoppingList[itemCount].categoryCode = categoryCode;
//
//    switch (categoryCode)
//    {
//        case 1: countVegetables++; break;
//        case 2: countFruits++; break;
//        case 3: countDrinks++; break;
//        default: cout << "Неизвестная категория.\n"; break;
//    }
//
//    itemCount++;
//    cout << "Товар добавлен: " << shoppingList[itemCount - 1].name << " (" 
//        << getCategoryName(shoppingList[itemCount - 1].categoryCode) << ")\n";
//}
//
//// Вывод списка покупок
//void printShoppingList() 
//{
//    if (itemCount == 0) 
//    {
//        cout << "Список покупок пуст.\n";
//        return;
//    }
//
//    cout << "\nСписок покупок:\n";
//    for (register int i = 0; i < itemCount; i++) 
//    {
//        cout << i + 1 << ". " << shoppingList[i].name << " (" 
//            << getCategoryName(shoppingList[i].categoryCode) << ")\n";
//    }
//
//    cout << "\nСтатистика по категориям:\n";
//    cout << "Овощи: " << countVegetables << "\n";
//    cout << "Фрукты: " << countFruits << "\n";
//    cout << "Напитки: " << countDrinks << "\n";
//}
//
//int main() 
//{
//    setlocale(LC_CTYPE, "Russian");
//    SetConsoleCP(1251);
//
//    // Локальные переменные для ввода
//    string name;
//    int categoryCode;
//    char choice;
//
//    do {
//        cout << "Добавить товар в список покупок? (y/n): ";
//        cin >> choice;
//        cin.ignore();  // очищаем буфер
//
//        if (choice == 'y') 
//        {
//            cout << "Введите название товара: ";
//            getline(cin, name);
//
//            cout << "Введите категорию (1-овощи, 2-фрукты, 3-напитки): ";
//            cin >> categoryCode;
//            cin.ignore();  // очищаем буфер
//
//            addItem(name, categoryCode);
//        }
//    } while (choice == 'y');
//
//    printShoppingList();
//
//    return 0;
//}

//// Лабораторная работа 3. Классы памяти
//// Дополнительное задание 1.
//// Учёт книг в библиотеке
//// Создайте систему для учета взятых книг.Используйте:
//// •	Глобальный массив для хранения названий книг
//// •	Статическую переменную для подсчёта общего количества
//// •	Локальные переменные для ввода данных пользователем
//// •	Регистровую переменную для временного хранения ID книги
//
//
//#include <iostream>
//#include <string>
//
//using namespace std;
//
//// Максимальное количество книг
//const int MAX_BOOKS = 100;
//
//// Глобальный массив для хранения названий книг
//string books[MAX_BOOKS];
//
//// Глобальная статическая переменная для подсчёта общего количества взятых книг
//static int bookCount = 0;
//
//// Функция для добавления книги
//void addBook(string& bookName) 
//{
//    if (bookCount >= MAX_BOOKS) 
//    {
//        cout << "Максимальное количество книг достигнуто.\n";
//        return;
//    }
//    books[bookCount] = bookName;
//    bookCount++;
//    cout << "Книга \"" << bookName << "\" взята.\n";
//}
//
//// Функция для вывода всех взятых книг
//void printBooks() 
//{
//    if (bookCount == 0) 
//    {
//        cout << "Нет взятых книг.\n";
//        return;
//    }
//    cout << "Взятые книги:\n";
//    for (register int i = 0; i < bookCount; ++i) 
//    {
//        cout << i + 1 << ". " << books[i] << "\n";
//    }
//}
//
//int main() 
//{
//
//    setlocale(LC_CTYPE, "Russian");
//
//    // Локальные переменные для ввода
//    string inputName;
//    char choice;
//
//    do {
//        cout << "Добавить книгу? (y/n): ";
//        cin >> choice;
//        cin.ignore(); // Чтобы убрать символ новой строки из буфера после ввода choice
//
//        if (choice == 'y') 
//        {
//            cout << "Введите название книги: ";
//            getline(cin, inputName);
//
//            // Добавляем книгу
//            addBook(inputName);
//        }
//    } while (choice == 'y');
//
//    printBooks();
//
//    cout << "Общее количество взятых книг: " << bookCount << "\n";
//
//    return 0;
//}

// 
// Лабораторная работа 3. Классы памяти
// Вариант 6. Индивидуальное задание.
// Напишите класс, который управляет динамическим массивом. 
// Используйте статические переменные для отслеживания общего количества созданных массивов 
// и локальные переменные для работы с элементами массива.
//
//#include <iostream>
//
//using namespace std;
//
//class DynamicArray 
//{
//private:
//    int* arr;          // указатель на динамический массив
//    int size;          // размер массива
//    static int count;  // статическая переменная — счетчик созданных объектов
//
//public:
//    // Конструктор: создает массив заданного размера
//    DynamicArray(int n) 
//    {
//        size = n;
//        arr = new int[size];
//        for (int i = 0; i < size; ++i) 
//        {
//            arr[i] = 0;  // инициализация нулями
//        }
//        count++; // увеличиваем счетчик при создании объекта
//    }
//
//    // Деструктор: освобождает память и уменьшает счетчик
//    ~DynamicArray() 
//    {
//        delete[] arr;
//        count--;
//    }
//
//    // Метод для установки значения по индексу
//    void set(int index, int value) 
//    {
//        if (index >= 0 && index < size) 
//        {
//            arr[index] = value;
//        }
//        else 
//        {
//            cout << "Index out of bounds\n";
//        }
//    }
//
//    // Метод для получения значения по индексу
//    int get(int index)
//    {
//        if (index >= 0 && index < size) 
//        {
//            return arr[index];
//        }
//        cout << "Index out of bounds\n";
//        return -1; // ошибка
//    }
//
//    // Метод для вывода всех элементов массива
//    void print()
//    {
//        for (int i = 0; i < size; ++i) 
//        {
//            cout << arr[i] << " ";
//        }
//        cout << "\n";
//    }
//
//    // Статический метод для получения количества созданных массивов
//    static int getCount() 
//    {
//        return count;
//    }
//};
//
//// Инициализация статической переменной (обязательно)
//int DynamicArray::count = 0;
//
//// Пример использования
//int main() 
//{
//    setlocale(LC_CTYPE, "Russian");
//
//    DynamicArray a1(5);
//    a1.set(0, 10);
//    a1.set(1, 20);
//    a1.print();
//
//    DynamicArray a2(3);
//    a2.set(0, 100);
//    a2.print();
//
//    std::cout << "Количество созданных массивов: " << DynamicArray::getCount() << "\n";
//
//    return 0;
//}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
