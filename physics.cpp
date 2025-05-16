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

unit::operator std::vector<int8_t>() const {
    return std::vector<int8_t>(std::begin(this->si), std::end(this->si));
}

std::ostream& operator<<(std::ostream& os, const unit& u) {
    os << (std::string)u;
    return os;
}





// VAL //
val::val(double v, unit u) {
    this->v = v;
    this->u = u;
}

val::operator std::string() const {
    return std::to_string(v) + " " + (std::string)u;
}
val::operator int() const { return v; }
val::operator float() const { return v; }
val::operator double() const { return v; }
val::operator long double() const { return v; }

val operator+(val x, val y) {
    if(x.u != y.u) throw std::invalid_argument("Unit Error");
    return val(x.v + y.v, x.u);
}
val operator-(val x, val y) {
    if(x.u != y.u) throw std::invalid_argument("Unit Error");
    return val(x.v - y.v, x.u);
}
val operator*(val x, val y) {
    return val(x.v * y.v, x.u * y.u);
}
val operator/(val x, val y) {
    return val(x.v / y.v, x.u / y.u);
}
val operator^(val x, int y) {
    return val(pow(x.v,y), x.u^y);
}

bool operator<(val x, val y) {
    return x.v < y.v;
}
bool operator>(val x, val y) {
    return x.v > y.v;
}
bool operator<=(val x, val y) {
    return x.v < y.v;
}
bool operator>=(val x, val y) {
    return x.v > y.v;
}
bool operator==(val x, val y) {
    return x.v == y.v && x.u == y.u;
}
bool operator!=(val x, val y) {
    return x.v != y.v && x.u != y.u;
}

val operator*(val x, long double y) {
    return val(x.v * y, x.u);
}
val operator*(long double x, val y) {
    return val(y.v * x, y.u);
}
val operator/(val x, long double y) {
    return val(x.v / y, x.u);
}
val operator/(long double x, val y) {
    return val(y.v / x, y.u);
}

val operator*(float x, unit y){
    return val(x, y);
}
std::string operator+(std::string x, val y){
    return x + (std::string)y;
}

val operator*(val x, unit y){
    return val(x.v, x.u * y);
}
val operator/(val x, unit y){
    return val(x.v, x.u / y);
}

std::ostream& operator<<(std::ostream& os, const val& v) {
    os << (std::string)v;
    return os;
}