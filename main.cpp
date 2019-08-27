#include <iostream>
#include <time.h>
#include <string>

// подключаем собственные заголовочные файлы
#include "book.h"
#include "dll.h"

using namespace std;

// используем собственные пространства имен
using namespace book;
using namespace dll;

void f(DLL<Book> dll) {
    cout << "Скопированный список: " << dll << endl;
}

void proc(Book& b) {
    cout << "Изменяем книгу " << b << "..." << endl;
    b.set_isbn(b.get_isbn() + 1);
}

// Запуск
int main() {
    // инициализация генератора случайных чисел (привязка ко времени)
    srand((unsigned int)time(nullptr));

    // создаем пустой список книг
    DLL<Book> book_list;

    // создаем несколько книг
    Book b1(1, "first");
    Book b2(2, "second");
    Book b3(3, "third");
    Book b4(4, "fourth");
    Book b5(5, "fifth");

    // добавляем книгу в конец списка, сохраняя на нее указатель
    DLL<Book>::Node* bp = book_list.push_back(b4);
    // добавляем книгу в конец списка
    book_list.push_back(b5);

    // добавляем книгу в начало списка
    book_list.push_front(b2);

    // добавляем книгу по указателю
    book_list.insert(bp, b3);
    // добавляем книгу по индекску, сохраняя на нее указатель
    bp = book_list.insert(2, b1);

    // выводим список книг
    cout << "После добавлений:" << book_list << ", " << book_list.get_size() << endl;

    // удаляем книгу по указателю
    book_list.erase(bp);
    cout << "После удаления:" << book_list << ", " << book_list.get_size() << endl;

    // находим требуемую книгу
    DLL<Book>::Node* pointer = book_list.find(b3);
    cout << "Найденная:" << pointer->data << endl;

    // применяем функцию-обработчик к каждой книге списка
    book_list.map(proc);
    cout << "После обработки:" << book_list << endl;

    // проверяем работу конструктора копии списка
    f(book_list);

    return 0;
}