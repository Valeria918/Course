#include <iostream>
#include <vector>

// DO NOT TOUCH

struct mystring {
    std::string s;

    mystring(const std::string& _s) : s(_s) {
        std::cout << "[string created]" << std::endl;
    }

    mystring(const mystring& other) : s(other.s) {
        std::cout << "[string copied]" << std::endl;
    }

    mystring(mystring&& other) : s(std::move(other.s)) {
        std::cout << "[string moved]" << std::endl;
    }
};

// AFTER THIS POINT YOU CAN EDIT

// void print(const std::vector<mystring>& myStringVector) {
//     // const& — элементы не копируются при итерации
//     for (const mystring& x : myStringVector) {
//         std::cout << x.s << " ";
//     }
//     std::cout << std::endl;
// }

// int main() {
//     std::vector<mystring> v;

//     v.reserve(3);

//     mystring s("hello");
//     v.push_back(std::move(s));

//     mystring s2("world");
//     v.push_back(std::move(s2));

//     mystring s3("!");
//     v.push_back(std::move(s3));

//     print(v);

//     return 0;
// }

void print(const std::vector<mystring>& myStringVector) {
    // const& — элементы не копируются при итерации
    for (const mystring& x : myStringVector) {
        std::cout << x.s << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<mystring> v;
    // reserve — вектор не перевыделяет память, существующие элементы не копируются
    v.reserve(3);

    v.emplace_back("hello");
    v.emplace_back("world");
    v.emplace_back("!");

    print(v);

    return 0;
}