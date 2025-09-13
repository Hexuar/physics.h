#include "unit.h"
#include "superscript.h"


inline const std::string si_strings[7] = {"m","kg","s","A","K","cd","mol"};
inline const std::map<physics::unit, std::string> si_derved_names {
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
inline const std::map<physics::unit, std::string> si_special_names {
    { physics::J * physics::S, "Js" },
    { physics::N * physics::S, "Ns" },
    { physics::J / physics::K, "JK" + super::super(-1) },
    { physics::J / (physics::KG * physics::K), "Jkg" + super::super(-1) + "K" + super::super(-1) },
    { physics::C / physics::M, "Cm" + super::super(-1) },
    { physics::C / (physics::M^2), "Cm" + super::super(-2) },
    { physics::C / (physics::M^3), "Cm" + super::super(-3) },
    { physics::T * physics::M, "Tm" },
    { physics::A / (physics::V * physics::M), "AV" + super::super(-1) + "m" + super::super(-1) },
    { physics::V / physics::M, "Vm" + super::super(-1) },
    { physics::W / (physics::M^2), "Wm" + super::super(-2) }
};

inline physics::unit::unit(std::vector<int8_t> si_units) {
    int size = si_units.size();
    for(int i = 0; i < std::min(7, size); i++) {
        si[i] = si_units[i];
    }
}

inline physics::unit::operator std::string() const {
    std::string output;

    // Returns special names if present in map
    if(si_special_names.count(*this) != 0) {
        output = si_special_names.at(*this);
        return output;
    }

    // Returns name of derived unit if present in map
    if(si_derved_names.count(*this) != 0) {
        output = si_derved_names.at(*this);
        return output;
    }

    // Constructs name from base units
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