#include <string>

namespace my_exception {

class MyException {
protected:
    std::string msg;

public:
    MyException(const std::string& msg) {
        this->msg = msg;
    }

    std::string get_msg() {
        return "ОШИБКА: " + msg;
    }
    void set_msg(const std::string& msg) {
        this->msg = msg;
    }
};

class MyMemoryException : MyException {
public:
    MyMemoryException(const std::string& msg) : MyException(msg) {}

    std::string get_msg() {
        return "ОШИБКА ПАМЯТИ: " + msg;
    }
};

}
