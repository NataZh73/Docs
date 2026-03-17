#include <iostream>
#include <string>
#include <iomanip>
// Лабораторная работа 42. Структурные типы данных
// Дополнительное задание 1.
// Определить структуру для представления информации о сданных студентом экзаменах, 
// содержащую поля : ФИО студента, число экзаменов, полученные оценки.
// Определить функции для обработки отдельного объекта
// (например, для проверки, сданы ли все экзамены на 4 и 5).
// Написать функцию для обработки массива структур.
// В результате обработки требуется вычислить характеристику успеваемости студентов, 
// то есть отношение числа студентов, сдавших экзамены на 4 и 5, к общему числу студентов, в процентах.

using namespace std;

//Перечисление возможных оценок
enum Mark {One = 1, Two = 2, Three = 3, Four = 4, Five = 5 };

// Структура Студент
struct Student 
{
    std::string fio; //ФИО
    int numExams;    // число экзаменов
    Mark* marks;     // массив оценок
};

// Глобальный массив студентов
const int MAX_STUDENTS = 5;
Student students[MAX_STUDENTS];

// Функция проверки, все ли оценки 4 и 5
bool isAll45(const Student& student);
// Вывод списка студентов
void printStudents(int count);
// Расчет успеваимости
double getGrade(int count);

int main() 
{
    setlocale(LC_CTYPE, "Russian");

    const int numStudents = MAX_STUDENTS;

    // Ввод данных
    students[0].fio = "Иванов Иван Иванович"; 
    students[0].numExams = 3; 
    students[0].marks = new Mark[3]{ Five, Four, Five };

    students[1].fio = "Петрова Мария Петровна"; 
    students[1].numExams = 4; 
    students[1].marks = new Mark[4]{ Five, Five, Three, Five };

    students[2].fio = "Сидоров Алексей Сергеевич"; 
    students[2].numExams = 3; 
    students[2].marks = new Mark[3]{ Four, Four, Four };

    students[3].fio = "Козлова Елена Владимировна"; 
    students[3].numExams = 4; 
    students[3].marks = new Mark[4]{ Five, Four, Five, Four };

    students[4].fio = "Морозов Дмитрий Алексеевич"; 
    students[4].numExams = 2; 
    students[4].marks = new Mark[2]{ Two, Five };

    // Вывод списка студентов
    printStudents(numStudents);

    // Расчет успеваемости
    double grade = getGrade(numStudents);
    cout << "Процент студентов, сдавших все экзамены на 4 и 5: ";
    cout << fixed << setprecision(2) << grade << "%" << endl;

    // освобождение памяти
    for (int i = 0; i < numStudents; ++i) 
    {
        delete[] students[i].marks;
    }

    return 0;
}

// Функция проверки, все ли оценки 4 и 5
bool isAll45(const Student& student) 
{
    for (int j = 0; j < student.numExams; j++) 
    {
        if (student.marks[j] != Four && student.marks[j] != Five) 
        {
            return false;
        }
    }
    return true;
}

// Вывод списка студентов
void printStudents(int count) 
{
    cout << "\n=== Список студентов ===\n";
    for (int i = 0; i < count; ++i) 
    {
        cout << "ФИО: " << students[i].fio << ", Экзаменов: " << students[i].numExams << ", Оценки: ";
        for (int j = 0; j < students[i].numExams; ++j) 
        {
            cout << students[i].marks[j]; 
            if (j < students[i].numExams - 1) cout << ", ";
        }
        // Проверка: все ли оценки 4 или 5?
        cout << " (Все 4/5: " << (isAll45(students[i]) ? "Да" : "Нет") << ")" << endl;
    }
}

// Расчет успеваимости
double getGrade(int count) 
{
    int count45 = 0;
    for (int i = 0; i < count; ++i) 
    {
        if (isAll45(students[i])) 
        {
            count45++;
        }
    }
    return (count > 0) ? (static_cast<double>(count45) / count) * 100.0 : 0.0;
}