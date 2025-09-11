#pragma once

#include <iostream>


namespace physics {
    inline void print() {
        std::cout << std::endl;
    };

    template <typename T, typename... Types>
    void print(T var1, Types...var2) {
        std::cout << var1 << "\t";
        print(var2...);
    }
}