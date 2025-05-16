#include "physics.h"
#include "superscript.h"

#include <stdexcept>
#include <map>




// UNIT //
std::string si_strings[7] = {"m","kg","s","A","K","cd","mol"};
std::map<unit, std::string> si_special_names{
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
bool unit::operator<(const unit x) const {
    std::vector<int8_t> si_vector, si_vectorx;

    for(int i = 0; i < 7; i++) {
        si_vector.push_back(si[i]);
        si_vectorx.push_back(x.si[i]);
    }

    return si_vector < si_vectorx;
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
