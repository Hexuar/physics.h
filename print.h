#pragma once

#include <iostream>

void print() {
    std::cout << std::endl;
};

template <typename... Types>
void print(std::string var1, Types...var2) {
    std::cout << var1 << " ";
    print(var2...);
}
