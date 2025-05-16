#include "physics.h"
#include "superscript.h"




// UNIT //

std::string si_strings[7] = {"K","m","A","s","mol","kg","cd"};

std::map<std::vector<int8_t>, std::string> si_special_names{
    { std::vector<int8_t>{0,0,0,-1,0,0,0}, "Hz" },
    { std::vector<int8_t>{0,1,0,-2,0,1,0}, "N" },
    { std::vector<int8_t>{0,-1,0,-2,0,1,0}, "Pa" },
    { std::vector<int8_t>{0,2,0,-2,0,1,0}, "J" },
    { std::vector<int8_t>{0,2,0,-3,0,1,0}, "W" },
    { std::vector<int8_t>{0,0,1,1,0,0,0}, "C" },
    { std::vector<int8_t>{0,2,-1,-3,0,1,0}, "V" },
    { std::vector<int8_t>{0,-2,2,4,0,-1,0}, "F" },
    { std::vector<int8_t>{0,2,-2,-3,0,1,0}, "Ω" },
    { std::vector<int8_t>{0,-2,2,3,0,-1,0}, "S" },
    { std::vector<int8_t>{0,2,-1,-2,0,1,0}, "Wb" },
    { std::vector<int8_t>{0,0,-1,-2,0,1,0}, "T" },
    { std::vector<int8_t>{0,2,-2,-2,0,1,0}, "H" },
    { std::vector<int8_t>{0,-2,0,0,0,0,1}, "lx" },
};

unit::unit(const std::vector<int8_t> si_units) {
    int size = si_units.size();
    for(int i = 0; i < std::min(7, size); i++) {
        si[i] = si_units[i];
    }
}
unit::unit(const int si_unit) {
    si[si_unit] = 1;
}
unit::unit(const std::string si_unit) {
    for(int i = 0; i < 7; i++) {
        si[i] = 0;
        if(si_unit == si_strings[i]) {
            si[i] = 1;
        }
    }
}
unit::unit(const char* si_unit) {
    for(int i = 0; i < 7; i++) {
        si[i] = 0;
        if(si_unit == si_strings[i]) {
            si[i] = 1;
        }
    }
}

std::string unit::to_string() const {

    // Returns special character if present in map
    std::vector<int8_t> si_vector = std::vector<int8_t>(si, si + sizeof si / sizeof si[0]);
    std::string output = si_special_names[si_vector];

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

unit unit::operator*(const unit x) const {
    std::vector<int8_t> si_units;

    for(int i = 0; i < 7; i++) {
        si_units.push_back(si[i] + x.si[i]);
    }

    return unit(si_units);
}
unit unit::operator/(const unit x) const {
    std::vector<int8_t> si_units;

    for(int i = 0; i < 7; i++) {
        si_units.push_back(si[i] - x.si[i]);
    }

    return unit(si_units);
}





// VAL //

val::val(const double value, const class unit unit) {
    this->v = value;
    this->u = unit;
}

std::string val::to_string() const {
    return std::to_string(v) + " " + u.to_string();
}
val::operator std::string() const {
    return this->to_string();
}

val val::operator+(val x) const {
    if(u.to_string() != x.u.to_string()) throw std::invalid_argument("Unit Error");
    return val(v + x.v, u);
}
val val::operator-(val x) const {
    if(u.to_string() != x.u.to_string()) throw std::invalid_argument("Unit Error");
    return val(v - x.v, u);
}
val val::operator*(val x) const {
    return val(v * x.v, u * x.u);
}
val val::operator/(val x) const {
    return val(v / x.v, u / x.u);
}

val operator*(const float x, const unit y){
    return val(x, y);
}
std::string operator+(const std::string x, val y){
    return x + y.to_string();
}

val operator*(const val x, const unit y){
    return val(x.v, x.u * y);
}
val operator/(const val x, const unit y){
    return val(x.v, x.u / y);
}
