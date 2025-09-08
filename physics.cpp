#include "physics.h"
#include "superscript.h"
#include <stdexcept>
#include <map>


using namespace physics;

// UNIT //
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
std::map<int8_t, std::string> prefix_names {
    {24, "Y"},
    {21, "Z"},
    {18, "E"},
    {15, "P"},
    {12, "T"},
    {9, "G"},
    {6, "M"},
    {3, "k"},
    {2, "h"},
    {1, "dc"},
    {-1, "d"},
    {-2, "c"},
    {-3, "m"},
    {-6, "μ"},
    {-9, "n"},
    {-12, "p"},
    {-15, "f"},
    {-18, "a"},
    {-21, "z"},
    {-24, "y"},
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
    this->e = 0;
    this->u = u;
    calculate_exponent();
}
val::val(double v, int8_t e, unit u) {
    this->v = v;
    this->e = e;
    this->u = u;
    calculate_exponent();
}

val::operator std::string() const {
    return std::to_string(v) + " " + prefix_names[e] + (std::string)u;
}
val::operator int() const { return v; }
val::operator float() const { return v; }
val::operator double() const { return v; }
val::operator long double() const { return v; }
val::operator unit() const { return u; }

val val::operator+(val x) const {
  if (u != x.u) throw std::invalid_argument("Unit Error");
  int8_t exp = std::max(e, x.e);
  return val(v * pow(10, e - exp) + x.v * pow(10, x.e - exp), exp, u);
}
val val::operator-(val x) const {
  if (u != x.u) throw std::invalid_argument("Unit Error");
  int8_t exp = std::max(e, x.e);
  return val(v * pow(10, e - exp) - x.v * pow(10, x.e - exp), exp, u);
}
val val::operator*(val x) const { return val(v * x.v, e + x.e, u * x.u); }
val val::operator*(unit x) const { return val(v, e, u * x); }
val val::operator/(val x) const { return val(v / x.v, e - x.e, u / x.u); }
val val::operator/(unit x) const { return val(v, e, u / x); }
val val::operator^(int x) const { return val(pow(v, x), u ^ x); }

bool val::operator<(val x) const { return (e != x.e) ? e < x.e : v < x.v; }
bool val::operator>(val x) const { return (e != x.e) ? e > x.e : v > x.v; }
bool val::operator<=(val x) const { return (e != x.e) ? e <= x.e : v <= x.v; }
bool val::operator>=(val x) const { return (e != x.e) ? e >= x.e : v >= x.v; }
bool val::operator==(val x) const { return v == x.v && e == x.e && u == x.u; }
bool val::operator!=(val x) const { return v != x.v || e != x.e || u != x.u; }

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

val physics::operator""_Y(long double v) { return val(v, 24); }
val physics::operator""_Z(long double v) { return val(v, 21); }
val physics::operator""_E(long double v) { return val(v, 18); }
val physics::operator""_P(long double v) { return val(v, 15); }
val physics::operator""_T(long double v) { return val(v, 12); }
val physics::operator""_G(long double v) { return val(v, 9); }
val physics::operator""_M(long double v) { return val(v, 6); }
val physics::operator""_k(long double v) { return val(v, 3); }
val physics::operator""_h(long double v) { return val(v, 2); }
val physics::operator""_da(long double v) { return val(v, 1); }
val physics::operator""_d(long double v) { return val(v, -1); }
val physics::operator""_c(long double v) { return val(v, -2); }
val physics::operator""_m(long double v) { return val(v, -3); }
val physics::operator""_mu(long double v) { return val(v, -6); }
val physics::operator""_n(long double v) { return val(v, -9); }
val physics::operator""_p(long double v) { return val(v, -12); }
val physics::operator""_f(long double v) { return val(v, -15); }
val physics::operator""_a(long double v) { return val(v, -18); }
val physics::operator""_z(long double v) { return val(v, -21); }
val physics::operator""_y(long double v) { return val(v, -24); }

void val::calculate_exponent() {

    if(abs(v) > 1) {
        while(abs(v) >= 10) {
            e++;
            v /= 10;
        }
    }
    else if(abs(v) < 1.0) {
        while(abs(v) <= 1.0) {
            e--;
            v *= 10;
        }
    }

    if(e > 3 || e < -3) {
        if(e % 3 == 1 || e % 3 == -2) {
            e--;
            v *= 10;
        }
        if(e % 3 == 2|| e % 3 == -1) {
            e++;
            v /= 10;
        }
    }
}