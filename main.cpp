#include "MyVector.h"

#include <iostream>

// Функция вывода содержимого вектора в консоль
template<typename T>
void PrintVector(T temp) {
    for (const auto& elem : temp) {
        std::cout << elem << " ";
    }
    std::cout << "\n" << std::endl;
    std::cout << "Размер контейнера size  = " << temp.size() << " byte" << std::endl;
    std::cout << "Ёмкость контейнера capacity = " << temp.capacity() << " byte" << std::endl;
    std::cout << std::endl;
}

int main(int argc, char const *argv[])
{   
    // Создаем пустой вектор vec типа int 
    Vector<int> vec;
    // заполняем вектор значениями от 0 до 9
    for (auto i = 0; i < 10; ++i) {
        vec.push_back(i);
    }
    PrintVector(vec);

    // Удаляем последний элемент вектрора и вставляем значение '43' по индексу 5
    vec.pop_back();
    vec.insert(5, 43);
    PrintVector(vec);

    // Создаем инициализированный вектор str типа std::string
    Vector<std::string> str {"The", "World", "Is", "Mine", "!"};
    PrintVector(str);

    // Меняем значение в позиции с индексом 4
    str.emplace(4, "?");
    PrintVector(str);

    str.erase(3);
    PrintVector(str);

    return 0;
}