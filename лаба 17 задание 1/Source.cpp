#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
using namespace std;
struct Worker {
    char surname[50];
    char gender;     
    double salary;  
    int experience;
    void print() const {
        setlocale(LC_ALL, "ru_RU.UTF-8");
        cout << "Фамилия: " << surname
            << ", Пол: " << gender
            << ", Зарплата: " << fixed << setprecision(2) << salary
            << ", Стаж: " << experience << " лет" << endl;
    }
};
void addWorker(const string& filename) {
    ofstream out(filename, ios::binary | ios::app);
    if (!out) {
        cerr << "Ошибка открытия файла для записи!" << endl;
        return;
    }
    Worker worker;
    cout << "Введите фамилию рабочего: ";
    cin >> worker.surname;
    cout << "Введите пол (M/F): ";
    cin >> worker.gender;
    cout << "Введите зарплату: ";
    cin >> worker.salary;
    cout << "Введите стаж работы: ";
    cin >> worker.experience;

    out.write(reinterpret_cast<char*>(&worker), sizeof(Worker));
    out.close();
}
void searchByExperience(const string& filename) {
    ifstream in(filename, ios::binary);
    if (!in) {
        cerr << "Ошибка открытия файла для чтения!" << endl;
        return;
    }
    int targetExp;
    cout << "Введите стаж для поиска: ";
    cin >> targetExp;
    Worker worker;
    bool found = false;
    while (in.read(reinterpret_cast<char*>(&worker), sizeof(Worker))) {
        if (worker.experience == targetExp) {
            worker.print();
            found = true;
        }
    }
    if (!found) {
        cout << "Рабочих со стажем " << targetExp << " лет не найдено." << endl;
    }
    in.close();
}
void findMaxSalaryWorker(const string& filename) {
    ifstream in(filename, ios::binary);
    if (!in) {
        cerr << "Ошибка открытия файла для чтения!" << endl;
        return;
    }
    Worker worker, maxWorker;
    double maxSalary = -1.0;
    bool hasWorkers = false;

    while (in.read(reinterpret_cast<char*>(&worker), sizeof(Worker))) {
        if (worker.salary > maxSalary) {
            maxSalary = worker.salary;
            maxWorker = worker;
        }
        hasWorkers = true;
    }
    in.close();
    if (hasWorkers) {
        cout << "Рабочий с максимальной зарплатой:" << endl;
        maxWorker.print();
    }
    else {
        cout << "Файл не содержит данных о рабочих." << endl;
    }
}
void displayAllWorkers(const string& filename) {
    ifstream in(filename, ios::binary);
    if (!in) {
        cerr << "Ошибка открытия файла для чтения!" << endl;
        return;
    }
    Worker worker;
    cout << "Список всех рабочих:" << endl;
    while (in.read(reinterpret_cast<char*>(&worker), sizeof(Worker))) {
        worker.print();
    }
    in.close();
}
int main() {
    const string filename = "workers.bin";
    int choice;
    do {
        cout << "\nМеню:\n";
        cout << "1. Добавить рабочего\n";
        cout << "2. Поиск по стажу\n";
        cout << "3. Найти рабочего с максимальной зарплатой\n";
        cout << "4. Показать всех рабочих\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;
        switch (choice) {
        case 1:
            addWorker(filename);
            break;
        case 2:
            searchByExperience(filename);
            break;
        case 3:
            findMaxSalaryWorker(filename);
            break;
        case 4:
            displayAllWorkers(filename);
            break;
        case 0:
            cout << "Выход из программы.\n";
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);
    return 0;
}