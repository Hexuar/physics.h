#pragma once

#include <string>
#include <map>


namespace super {
    std::map<char, std::string> supertable{
        {'0', "\u2070"},
        {'1', "\u00b9"},
        {'2', "\u00b2"},
        {'3', "\u00b3"},
        {'4', "\u2074"},
        {'5', "\u2075"},
        {'6', "\u2076"},
        {'7', "\u2077"},
        {'8', "\u2078"},
        {'9', "\u2079"},
        {'+', "\u207A"},
        {'-', "\u207B"}
    };

    std::string super(char c) {
        return supertable[c];
    }
    std::string super(int n) {
        std::string out;
        if(n < 0) {
            out += "\u207B";
            n *= -1;
        }

        for(char c : std::to_string(n)) {
            out += super(c);
        }
        return out;
    }
};

