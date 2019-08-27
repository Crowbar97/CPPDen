#include <iostream>

namespace dll {

// Двусвязный список (Doubly Linked List)
template<class T>
class DLL {

public:
    // Узел списка
    class Node {
    public:
        // данные
        T data;
        // указатель на следующий узел
        Node* next;
        // указатель на предыдущий узел
        Node* prev;

        // конструктор
        Node(T data) {
            std::cout << "node created!" << std::endl;
            this->data = data;
        }
    };

private:
    // указатель на голову (первый узел) списка
    Node* head;
    // указатель на хвост (последний узел) списка
    Node* tail;
    // размер списка
    size_t size;

public:
    DLL();
    ~DLL();
    DLL(const DLL<T> &target);

    Node* push_front(const T& data);

    Node* push_back(const T& data);

    Node* insert(Node* next_node, const T& data);
    Node* insert(size_t ind, const T& data);

    Node* erase(Node* node);

    Node* find(const T& data);

    void map(void(processor)(T&));

    std::pair<T*, size_t> to_array();

    size_t get_size() {
        return size;
    }

    template<class S>
    friend std::ostream& operator<<(std::ostream& stream, const DLL<S>& d);
};

//-Реализация------------------------------------------------------------------------

// конструктор
template<class T>
DLL<T>::DLL() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}
// деструктор
template<class T>
DLL<T>::~DLL() {
        Node* pointer = head;
        while (pointer)
            pointer = erase(pointer);
        std::cout << "Список разрушен!" << std::endl;
    }
// конструктор копии
template<class T>
DLL<T>::DLL(const DLL<T> &target) {
    head = nullptr;
    tail = nullptr;
    size = 0;

    Node* tp = target.head;
    while (tp) {
        push_back(tp->data);
        tp = tp->next;
    }

    std::cout << "Список скопирован!" << std::endl;
}

// добавление узла в начало списка
// data - данные, которые нужно записать в новый узел списка
template<class T>
typename DLL<T>::Node* DLL<T>::push_front(const T& data) {
    // [ сначала отдельно создадим и наполним новый узел списка ]
    // создаем новый узел (ставим указатель на выделенную память)
    Node* new_node = new Node(data);

    // [ теперь проведем связи ОТ нового узла К соседнему ]
    // задаем для него следующий узел тот, который раньше был первым
    new_node->next = head;
    // задаем для него, что предыущего узла для него нет (т.к. он теперь первый)
    new_node->prev = nullptr;

    // [ теперь проведем связи ОТ соседнего узла К новому ]
    // если список не пустой,
    if (head)
        // то задаем для бывшего первого узла новый узел в качестве предыдущего
        head->prev = new_node;
    else
        // иначе ставим указатель хвоста на новый узел
        tail = new_node;

    // ставим указатель головы списка на новый узел
    head = new_node;

    // увеличиваем значение счетчика размера списка
    size++;
    // возвращаем указатель на вставленный элемент
    return new_node;
}

// добавление узла в конец списка
// data - данные, которые нужно записать в новый узел списка
template<class T>
typename DLL<T>::Node* DLL<T>::push_back(const T& data) {
    // [ сначала отдельно создадим и наполним новый узел списка ]
    // создаем новый узел (ставим указатель на выделенную память)
    Node* new_node = new Node(data);

    // [ теперь проведем связи ОТ и К новому узлу ]
    // задаем для него, что следующего узла для него нет (т.к. он теперь последний)
    new_node->next = nullptr;
    // в случае, если список пустой,
    if (!head) {
        // то задаем для нового узла, что предыущего узла для него тоже нет (т.к. он же теперь и первый)
        new_node->prev = nullptr;
        // ставим на него указатель головы
        head = new_node;
        // ставим на него указатель хвоста
        tail = new_node;
    } else {
        // иначе задаем для последнего элемента, что следующим для него теперь является новый узел
        tail->next = new_node;
        // задаем для нового узла, что предыдущим для него является бывший последний узел
        new_node->prev = tail;
        // обновляем указатель хвоста
        tail = new_node;
    }

    // увеличиваем значение счетчика размера списка
    size++;
    // возвращаем указатель на вставленный элемент
    return new_node;
}

// вставка узла ПЕРЕД указанным узлом
// next_node - указатель на следующий (целевой) узел для вставляемого
// data - данные, которые нужно записать в новый узел списка
template<class T>
typename DLL<T>::Node* DLL<T>::insert(Node* next_node, const T& data) {
    // [ осуществим необходимые проверки ]
    // проверяем, передан ли указатель на существующий узел
    if (!next_node) {
        std::cout << "Указан несуществующий узел!";
        // указываем, что вставить новый узел не удалось
        return nullptr;
    }

    // [ сначала отдельно создадим и наполним новый узел списка ]
    // создаем новый узел (ставим указатель на выделенную память)
    Node* new_node = new Node(data);

    // [ теперь проведем связи ОТ НОВОГО УЗЛА к соседним ]
    // для нового узла задаем,
    // что предыдущим для него является тот узел,
    // который был предыдущим для целевого
    new_node->prev = next_node->prev;
    // а следующим для него является целевой
    new_node->next = next_node;

    // [ теперь проведем связи ОТ СОСЕДНИХ УЗЛОВ к новому ]
    // для целевого узла задаем,
    // что предыдущим для него теперь является новый узел
    next_node->prev = new_node;
    // если новый узел не оказался первым в списке,
    if (new_node->prev)
        // то для предыдущего для него узла задаем,
        // что следующим для него теперь является новый
        new_node->prev->next = new_node;
    else
        // иначе ставим на новый узел указатель головы
        head = new_node;

    // увеличиваем значение счетчика размера списка
    size++;
    // возвращаем указатель на вставленный элемент
    return new_node;
}
// вставка узла ПЕРЕД указанным узлом
// ind - индекс следующего (целевого) узла для вставляемого
// data - данные, которые нужно записать в новый узел списка
template<class T>
typename DLL<T>::Node* DLL<T>::insert(size_t ind, const T& data) {
        // [ осуществим необходимые проверки ]
        // установим указатель на целевой узел
        Node* next_node = head;
        for (int i = 0; i < ind; i++)
            if (next_node->next)
                next_node = next_node->next;
            else {
                std::cout << "Узла с таким индексом не существует!";
                // указываем, что вставить новый узел не удалось
                return nullptr;
            }

        // [ сначала отдельно создадим и наполним новый узел списка ]
        // создаем новый узел (ставим указатель на выделенную память)
        Node* new_node = new Node(data);

        // [ теперь проведем связи ОТ НОВОГО УЗЛА к соседним ]
        // для нового узла задаем,
        // что предыдущим для него является тот узел,
        // который был предыдущим для целевого
        new_node->prev = next_node->prev;
        // а следующим для него является целевой
        new_node->next = next_node;

        // [ теперь проведем связи ОТ СОСЕДНИХ УЗЛОВ к новому ]
        // для целевого узла задаем,
        // что предыдущим для него теперь является новый узел
        next_node->prev = new_node;
        // если новый узел не оказался первым в списке,
        if (new_node->prev)
            // то для предыдущего для него узла задаем,
            // что следующим для него теперь является новый
            new_node->prev->next = new_node;
        else
            // иначе ставим на новый узел указатель головы
            head = new_node;

        // увеличиваем значение счетчика размера списка
        size++;
        // возвращаем указатель на вставленный элемент
        return new_node;
    }

// удаление узла
// node - указатель на удаляемый узел
template<class T>
typename DLL<T>::Node* DLL<T>::erase(Node* node) {
    // [ осуществим необходимые проверки ]
    // проверяем, передан ли указатель на существующий узел
    if (!node) {
        std::cout << "Указан несуществующий узел!";
        // указываем, что удалить узел не удалось
        return nullptr;
    }
    // проверяем список на пустоту
    if (!head) {
        std::cout << "Список пуст!";
        // указываем, что удалить узел не удалось
        return nullptr;
    }

    // сохраняем указатель на следующий за удаляемым узел
    Node* next = node->next;

    // [ удалим связи от соседних узлов к удаляемому ]
    // если удаляемый узел не является последним,
    if (node->next)
        // то задаем для следующего для удаляемого узла,
        // что предыдущим для него теперь является тот узел,
        // который был предыдущим для удаляемого
        node->next->prev = node->prev;
    else
        // иначе переставляем указатель хвоста на предыдущий для удаляемого узел
        tail = node->prev;

    // если удаляемый узел не является первым,
    if (node->prev)
        // то задаем для предыдущего для удаляемого узла,
        // что следующим для него теперь является тот узел,
        // который был следующим для удаляемого
        node->prev->next = node->next;
    else
        // иначе переставляем указатель головы на следующий за удаляемым узел
        head = node->next;

    // освобождаем память, которая была выделена для удаляемого узла
    delete node;
    // уменьшаем значение счетчика размера списка
    size--;
    // возвращаем указатель на следующий за удаленным узел
    return next;
}

// получение массива из списка
// возвращает пару (массив, размер)
template<class T>
std::pair<T* , size_t> DLL<T>::to_array() {
    // создаем массив размера списка
    T* array = new int[size];
    // проходим по всему списку
    Node* pointer = head;
    for (int i = 0; i < size; i++, pointer = pointer->next)
        // записываем значения узлов в массив
        array[i] = pointer->data;
    // возвращаем массив и его размер
    return make_pair(array, size);
}

// поиск
template<class T>
typename DLL<T>::Node* DLL<T>::find(const T& data) {
    Node* pointer = head;
    while (pointer && pointer->data != data)
        pointer = pointer->next;
    return pointer;
}

// применение операции к каждому элементу
template<class T>
void DLL<T>::map(void(processor)(T&)) {
    Node* pointer = head;
    while (pointer) {
        processor(pointer->data);
        pointer = pointer->next;
    }
}

//-Дополнительно------------------------------------------------------------------------

// перегрузка оператора вывода
template<class S>
std::ostream& operator<<(std::ostream& stream, const DLL<S>& d) {
        typename DLL<S>::Node* pointer = d.head;
        stream << "[";
        while (pointer) {
            stream << pointer->data;
            if (pointer->next)
                stream << ", ";
            pointer = pointer->next;
        }
        stream << "]";
        return stream;
    }

}