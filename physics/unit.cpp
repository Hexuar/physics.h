#include "unit.h"
#include <map>
#include "superscript.h"


using namespace physics;

std::string si_strings[7] = {"m","kg","s","A","K","cd","mol"};
std::map<unit, std::string> si_special_names {
    { HZ, "Hz" },
    { N, "N" },
    { J, "J" },
    { W, "W" },
    { PA, "Pa" },
    { V, "V" },
    { C, "C" },
    { OHM, "Ω" },
    { F, "F" },
    { H, "H" },
    { SIEMENS, "S" },
    { WB, "Wb" },
    { T, "T" }
};

unit::unit(std::vector<int8_t> si_units) {
    int size = si_units.size();
    for(int i = 0; i < std::min(7, size); i++) {
        si[i] = si_units[i];
    }
}

unit::operator std::string() const {
    // Returns special character if present in map
    std::string output = si_special_names[*this];
    if(output != "") {
        return output;
    }

    // Appends all units to output string
    for(int i = 0; i < 7; i++) {
        int8_t u = si[i];
        if(u != 0) {
            output += si_strings[i];
            if(u != 1) {
                output += super::super(u);
            }
        }
    }
    return output;
}
unit::operator std::vector<int8_t>() const {
    return std::vector<int8_t>(std::begin(this->si), std::end(this->si));
}

unit unit::operator*(unit x) const {
    std::vector<int8_t> si_units;

    for(int i = 0; i < 7; i++) {
        si_units.push_back(si[i] + x.si[i]);
    }

    return unit(si_units);
}
unit unit::operator/(unit x) const {
    std::vector<int8_t> si_units;

    for(int i = 0; i < 7; i++) {
        si_units.push_back(si[i] - x.si[i]);
    }

    return unit(si_units);
}
unit unit::operator^(int x) const {
    std::vector<int8_t> si_units;

    for(int i = 0; i < 7; i++) {
        si_units.push_back(si[i] * x);
    }

    return unit(si_units);
}

bool unit::operator<(unit x) const {
    return (std::vector<int8_t>)*this < (std::vector<int8_t>)x;
}
bool unit::operator==(unit x) const {
    return (std::vector<int8_t>)*this == (std::vector<int8_t>)x;
}
bool unit::operator!=(unit x) const {
    return (std::vector<int8_t>)*this != (std::vector<int8_t>)x;
}

std::ostream& physics::operator<<(std::ostream& os, const unit& u) {
    os << (std::string)u;
    return os;
}