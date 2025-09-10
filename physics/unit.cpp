#include "unit.h"
#include "superscript.h"


inline std::string si_strings[7] = {"m","kg","s","A","K","cd","mol"};
inline std::map<physics::unit, std::string> si_special_names {
    { physics::HZ, "Hz" },
    { physics::N, "N" },
    { physics::J, "J" },
    { physics::W, "W" },
    { physics::PA, "Pa" },
    { physics::V, "V" },
    { physics::C, "C" },
    { physics::OHM, "Ω" },
    { physics::F, "F" },
    { physics::H, "H" },
    { physics::SIEMENS, "S" },
    { physics::WB, "Wb" },
    { physics::T, "T" }
};

inline physics::unit::unit(std::vector<int8_t> si_units) {
    int size = si_units.size();
    for(int i = 0; i < std::min(7, size); i++) {
        si[i] = si_units[i];
    }
}

inline physics::unit::operator std::string() const {
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
inline physics::unit::operator std::vector<int8_t>() const {
    return std::vector<int8_t>(std::begin(this->si), std::end(this->si));
}

inline physics::unit physics::unit::operator*(unit x) const {
    std::vector<int8_t> si_units;

    for(int i = 0; i < 7; i++) {
        si_units.push_back(si[i] + x.si[i]);
    }

    return unit(si_units);
}
inline physics::unit physics::unit::operator/(unit x) const {
    std::vector<int8_t> si_units;

    for(int i = 0; i < 7; i++) {
        si_units.push_back(si[i] - x.si[i]);
    }

    return unit(si_units);
}
inline physics::unit physics::unit::operator^(int x) const {
    std::vector<int8_t> si_units;

    for(int i = 0; i < 7; i++) {
        si_units.push_back(si[i] * x);
    }

    return unit(si_units);
}

inline bool physics::unit::operator<(unit x) const {
    return (std::vector<int8_t>)*this < (std::vector<int8_t>)x;
}
inline bool physics::unit::operator==(unit x) const {
    return (std::vector<int8_t>)*this == (std::vector<int8_t>)x;
}
inline bool physics::unit::operator!=(unit x) const {
    return (std::vector<int8_t>)*this != (std::vector<int8_t>)x;
}

inline std::ostream& physics::operator<<(std::ostream& os, const unit& u) {
    os << (std::string)u;
    return os;
}