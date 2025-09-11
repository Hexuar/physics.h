#include "value.h"
#include <map>
#include <stdexcept>
#include <math.h>


inline std::map<int8_t, std::string> prefix_names {
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

inline physics::val::val(long double v) {
    this->v = matrix(v);
    this->e = 0;
    this->u = unit();
}
inline physics::val::val(matrix v) {
    this->v = v;
    this->e = 0;
    this->u = unit();
}
inline physics::val::val(matrix v, unit u) {
    this->v = v;
    this->e = 0;
    this->u = u;
    calculate_exponent();
}
inline physics::val::val(matrix v, int8_t e, unit u) {
    this->v = v;
    this->e = e;
    this->u = u;
    calculate_exponent();
}

inline std::string physics::val::operator+(std::string x) const {
    return (std::string)*this + x;
}
inline physics::val::operator std::string() const {
    return (std::string)v + get_prefix() + (std::string)u;
}
inline physics::val::operator int() const { return (int)v; }
inline physics::val::operator float() const { return (float)v; }
inline physics::val::operator double() const { return (double)v; }
inline physics::val::operator long double() const { return (long double)v; }
inline physics::val::operator unit() const { return u; }

inline physics::val physics::val::operator+(val x) const {
  if (u != x.u) throw std::invalid_argument("Unit Error");
  int8_t exp = std::max(e, x.e);
  return val(v * pow(10, e - exp) + x.v * pow(10, x.e - exp), exp, u);
}
inline physics::val physics::val::operator-(val x) const {
  if (u != x.u) throw std::invalid_argument("Unit Error");
  int8_t exp = std::max(e, x.e);
  return val(v * pow(10, e - exp) - x.v * pow(10, x.e - exp), exp, u);
}
inline physics::val physics::val::operator*(val x) const { return val(v * x.v, e + x.e, u * x.u); }
inline physics::val physics::val::operator*(unit x) const { return val(v, e, u * x); }
inline physics::val physics::val::operator/(val x) const { return val(v / x.v, e - x.e, u / x.u); }
inline physics::val physics::val::operator/(unit x) const { return val(v, e, u / x); }
inline physics::val physics::val::operator^(double x) const { return val(v^x, e * x, u ^ x); }

inline physics::val physics::val::operator+=(val x) {
    *this = *this + x;
    return *this;
}
inline physics::val physics::val::operator-=(val x) {
    *this = *this - x;
    return *this;
}

inline bool physics::val::operator<(val x) const { return (e != x.e) ? e < x.e : (long double)v < (long double)x.v; }
inline bool physics::val::operator>(val x) const { return (e != x.e) ? e > x.e : (long double)v > (long double)x.v; }
inline bool physics::val::operator<=(val x) const { return (e != x.e) ? e <= x.e : (long double)v <= (long double)x.v; }
inline bool physics::val::operator>=(val x) const { return (e != x.e) ? e >= x.e : (long double)v >= (long double)x.v; }
inline bool physics::val::operator==(val x) const { return v == x.v && e == x.e && u == x.u; }
inline bool physics::val::operator!=(val x) const { return v != x.v || e != x.e || u != x.u; }

inline physics::val physics::val::T() {
    return val(v.T(), e, u);
}

inline physics::val physics::operator*(val x, long double y) { return val((long double)x * y, x.e, (unit)x); }
inline physics::val physics::operator*(long double x, val y) { return val((long double)y * x, y.e, (unit)y); }
inline physics::val physics::operator/(val x, long double y) { return val((long double)x / y, x.e, (unit)x); }
inline physics::val physics::operator/(long double x, val y) { return val((long double)y / x, -y.e, (unit)y); }

inline physics::val physics::operator*(matrix x, unit y) { return val(x, y); }
inline physics::val physics::operator/(matrix x, unit y) { return val(x, y^-1); }
inline std::string physics::operator+(std::string x, val y) { return x + (std::string)y; }
inline std::ostream& physics::operator<<(std::ostream &os, const val &v) {
    os << (std::string)v;
    return os;
}

inline physics::val physics::operator""_Y(long double v) { return val(v, 24); }
inline physics::val physics::operator""_Z(long double v) { return val(v, 21); }
inline physics::val physics::operator""_E(long double v) { return val(v, 18); }
inline physics::val physics::operator""_P(long double v) { return val(v, 15); }
inline physics::val physics::operator""_T(long double v) { return val(v, 12); }
inline physics::val physics::operator""_G(long double v) { return val(v, 9); }
inline physics::val physics::operator""_M(long double v) { return val(v, 6); }
inline physics::val physics::operator""_k(long double v) { return val(v, 3); }
inline physics::val physics::operator""_h(long double v) { return val(v, 2); }
inline physics::val physics::operator""_da(long double v) { return val(v, 1); }
inline physics::val physics::operator""_d(long double v) { return val(v, -1); }
inline physics::val physics::operator""_c(long double v) { return val(v, -2); }
inline physics::val physics::operator""_m(long double v) { return val(v, -3); }
inline physics::val physics::operator""_mu(long double v) { return val(v, -6); }
inline physics::val physics::operator""_n(long double v) { return val(v, -9); }
inline physics::val physics::operator""_p(long double v) { return val(v, -12); }
inline physics::val physics::operator""_f(long double v) { return val(v, -15); }
inline physics::val physics::operator""_a(long double v) { return val(v, -18); }
inline physics::val physics::operator""_z(long double v) { return val(v, -21); }
inline physics::val physics::operator""_y(long double v) { return val(v, -24); }

inline void physics::val::calculate_exponent() {
    if(v.rows() != 1 || v.cols() != 1) {
        v *= pow(10,e);
        e = 0;
        return;
    }

    if((long double)abs(v) > 1) {
        while((long double)abs(v) >= 10) {
            e++;
            v /= 10;
        }
    }
    else if((long double)abs(v) < 1.0) {
        while((long double)abs(v) <= 1.0) {
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

inline std::string physics::val::get_prefix() const {
    if(e == 0) {
        return u == unit() ? "" : " ";
    };
    if(u == unit() || (long double)abs(e) > 24) return "e" + std::to_string(e) + " ";
    return " " + prefix_names[e];
}