#include "MyVector.h"

int main()
{
    Vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    std::cout << vec.empty() << std::endl;

    for (const auto& el : vec) {
        std::cout << el << " ";
    }
    std::cout.put('\n');

    Vector<int> num {1, 2, 3};
    for (const auto& el : num) {
        std::cout << el << " ";
    }
    std::cout<< std::endl;

    //num.pop_back();


    for (const auto& el : num) {
        std::cout << el << " ";
    }
    std::cout<< std::endl;

    num.insert(2, 56);

    for (const auto& el : num) {
        std::cout << el << " ";
    }
    std::cout<< std::endl;

    num.erase(2);
    for (const auto& el : num) {
        std::cout << el << " ";
    }
    std::cout<< std::endl;
    return 0;
}
