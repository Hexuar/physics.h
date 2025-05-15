#pragma once
#include <string>
#include <map>


namespace super {
    extern std::map<char, std::string> supertable;
    std::string super(char c);
    std::string super(int n);
};

