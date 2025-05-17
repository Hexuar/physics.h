#include "physics.h"
#include "superscript.h"

#include <stdexcept>
#include <map>

using namespace physics;





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
val::operator unit() const { return u; }

val val::operator+(val x) const {
  if (u != x.u) throw std::invalid_argument("Unit Error");
  return val(v + x.v, u);
}
val val::operator-(val x) const {
  if (u != x.u) throw std::invalid_argument("Unit Error");
  return val(v - x.v, u);
}
val val::operator*(val x) const { return val(v * x.v, u * x.u); }
val val::operator*(unit x) const { return val(v, u * x); }
val val::operator/(val x) const { return val(v / x.v, u / x.u); }
val val::operator/(unit x) const { return val(v, u / x); }
val val::operator^(int x) const { return val(pow(v, x), u ^ x); }

bool val::operator<(val x) const { return v < x.v; }
bool val::operator>(val x) const { return v > x.v; }
bool val::operator<=(val x) const { return v < x.v; }
bool val::operator>=(val x) const { return v > x.v; }
bool val::operator==(val x) const { return v == x.v && u == x.u; }
bool val::operator!=(val x) const { return v != x.v && u != x.u; }

val physics::operator*(val x, long double y) { return val((long double)x * y, (unit)x); }
val physics::operator*(long double x, val y) { return val((long double)y * x, (unit)y); }
val physics::operator/(val x, long double y) { return val((long double)x / y, (unit)x); }
val physics::operator/(long double x, val y) { return val((long double)y / x, (unit)y); }

val physics::operator*(long double x, unit y) { return val(x, y); }
val physics::operator/(long double x, unit y) { return val(x, y^-1); }
std::string physics::operator+(std::string x, val y) { return x + (std::string)y; }
std::ostream& physics::operator<<(std::ostream &os, const val &v) {
    os << (std::string)v;
    return os;
}