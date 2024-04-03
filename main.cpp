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

    Vector<int> num {1, 2, 3, 4, 5 ,6, 7, 8, 9};
    for (const auto& el : num) {
        std::cout << el << " ";
    }
    std::cout<< std::endl;
    std::cout << num.size() << std::endl;

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
    std::cout << num.size() << std::endl;


    num.insert(5, 65);
    for (const auto& el : num) {
        std::cout << el << " ";
    }
    std::cout<< std::endl;
    std::cout << num.size()<< std::endl;
    num.insert(12, 45);
    std::cout << num.size()<< std::endl;
    num.insert(12, 45);
    std::cout << num.size()<< std::endl;

    num.insert(12, 45);
    std::cout << num.size()<< std::endl;
    num.insert(-4, 78);
    for (const auto& el : num) {
        std::cout << el << " ";
    }
    std::cout<< std::endl;
//
    std::cout << num.size() << " " << num.capacity() << "\n";
//    num.erase(2);
//    for (const auto& el : num) {
//        std::cout << el << " ";
//    }
//    std::cout<< std::endl;

//    num.emplace(4, 15);
//    for (const auto& el : num) {
//        std::cout << el << " ";
//    }
//    std::cout<< std::endl;

//    std::cout << num.max_size() << std::endl;

    //Vector<int> g(10);

    Vector<char> str {'o', 'f', 'c'};
    //Vector<char> str;
    std::cout << "size - " << str.size() << " capacity - " << str.capacity() << std::endl;
    std::cout << "первый элемент - " << str.front() << std::endl;
    std::cout << "последний элемент - " << str.back() << std::endl;

    Vector<size_t> d {1, 2, 3, 4, 5};
    std::cout << "первый элемент - " << d.front() << std::endl;
    std::cout << "последний элемент - " << d.back() << std::endl;
    std::cout << str.at(0) << std::endl;
    std::cout << std::endl;
    std::cout << "/////////////////////" << std::endl;
    Vector<int> v {1, 2, 3, 4, 5, 6, 7};
    Vector<double> v3;
    Vector<std::string> v1;

    std::cout << &v[0] << "\t" << &v1[0] << "\t" << &v3[0] << std::endl; //
    std::cout << v.data() << "\t" << v1.data() << "\t" << v3.data() << std::endl;
    std::cout << "-----------------------------" << std::endl;

    Vector<std::string> s {"MY", "LOVE", "IS"};
    for (auto i : s) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}
