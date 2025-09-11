

// begin --- matrix.cpp --- 



// begin --- matrix.h --- 

#pragma once

#include <string>
#include <vector>

namespace physics {

    struct matrix {
    public:
        std::vector<std::vector<long double>> data;

        int rows() const;
        int cols() const;
        long double first() const;
        int size() const;

        bool is_scalar() const;
        bool is_vector() const;

    public:
        matrix();
        matrix(long double value);
        matrix(std::vector<long double> values);
        matrix(std::vector<std::vector<long double>> values);

        std::string operator+(std::string x) const;
        operator std::string() const;
        explicit operator int() const;
        explicit operator float() const;
        explicit operator double() const;
        explicit operator long double() const;

        matrix operator+(matrix m) const;
        matrix operator-(matrix m) const;
        matrix operator*(long double x) const;
        matrix operator*(matrix m) const;
        matrix operator/(long double x) const;
        matrix operator/(matrix m) const;
        matrix operator^(double) const;

        matrix operator+=(matrix m);
        matrix operator-=(matrix m);
        matrix operator*=(long double x);
        matrix operator*=(matrix m);
        matrix operator/=(long double x);

        bool operator==(matrix m) const;
        bool operator!=(matrix m) const;

        // Transpose
        matrix T() const;
    };

    matrix operator*(long double x, matrix m);

    std::string operator+(std::string x, matrix m);
    std::ostream& operator<<(std::ostream &os, const matrix &m);

    matrix abs(matrix m);
    matrix cross(matrix m1, matrix m2);
}

// end --- matrix.h --- 


#include <stdexcept>
#include <math.h>


inline int physics::matrix::rows() const { return data.size(); }
inline int physics::matrix::cols() const { return data[0].size(); }
inline long double physics::matrix::first() const { return data[0][0]; }
inline int physics::matrix::size() const { return data.size() * data[0].size(); }

inline bool physics::matrix::is_scalar() const { return rows() == 1 && cols() == 1; }
inline bool physics::matrix::is_vector() const { return rows() == 1 || cols() == 1; }


inline physics::matrix::matrix() {}
inline physics::matrix::matrix(long double value) { data.push_back({value}); }
inline physics::matrix::matrix(std::vector<long double> values) { data.push_back({values}); }
inline physics::matrix::matrix(std::vector<std::vector<long double>> values) { data = values; }


inline std::string physics::matrix::operator+(std::string x) const {
    return (std::string)*this + x;
}

inline physics::matrix::operator std::string() const {
    std::string string;
    if(rows() > 1) string = "[";
    for(std::vector<long double> row : data) {
        if(cols() > 1) string += "[ ";
        for(long double value : row) {
            string += std::to_string(value) + " ";
        }
        if(cols() > 1) string += "]";
    }
    if(rows() > 1) string += "]";
    return string;
}

inline physics::matrix::operator int() const { return (long double)*this; }
inline physics::matrix::operator float() const { return (long double)*this; }
inline physics::matrix::operator double() const { return (long double)*this; }
inline physics::matrix::operator long double() const {
    if(rows() != 1 || cols() != 1) throw std::invalid_argument("Only 1x1 matrices can be converted to scalar values.");
    return first();
}

inline physics::matrix physics::matrix::operator+(matrix m) const {
    if(rows() != m.rows() || cols() != m.cols()) throw std::invalid_argument("Incompatible matrices.");

    matrix out;
    for(int i = 0; i < data.size(); i++) {
        std::vector<long double> newRow;
        for(int j = 0; j < data[0].size(); j++) {
            newRow.push_back(data[i][j] + m.data[i][j]);
        }
        out.data.push_back(newRow);
    }
    return out;
}

inline physics::matrix physics::matrix::operator-(matrix m) const {
    return *this + -1 * m;
}

inline physics::matrix physics::matrix::operator*(long double x) const {
    matrix out;
    for(std::vector<long double> row : data) {
        std::vector<long double> newRow;
        for(long double value : row) {
            newRow.push_back(value * x);
        }
        out.data.push_back(newRow);
    }
    return out;
}

inline physics::matrix physics::matrix::operator*(matrix x) const {
    // Multiplication by 1x1 matrix should be regarded as scalar multiplication
    if(x.rows() == 1 && x.cols() == 1) return *this * x.first();
    if(rows() == 1 && cols() == 1) return first() * x;

    // Automatically transpose vectors
    if((x.rows() == 1 || x.cols() == 1) && cols() != x.rows()) x = x.T();
    if(rows() == 1 && x.rows() == 1) x = x.T();

    if(cols() != x.rows()) throw std::invalid_argument("Incompatible matrices.");

    matrix out;
    for(int i = 0; i < rows(); i++) {
        std::vector<long double> newRow;
        for(int j = 0; j < x.cols(); j++) {
            long double sum = 0;
            for(int k = 0; k < cols(); k++) {
                sum += data[i][k] * x.data[k][j];
            }
            newRow.push_back(sum);
        }
        out.data.push_back(newRow);
    }
    return out.T();
}

inline physics::matrix physics::matrix::operator/(long double x) const {
    return *this * (1/x);
}

inline physics::matrix physics::matrix::operator/(matrix m) const {
    if(m.rows() != 1 || m.cols() != 1) throw std::invalid_argument("Dividing by matrix of size other than 1x1 is undefined.");
    return *this * (1/m.first());
}

inline physics::matrix physics::matrix::operator^(double x) const {
    if(rows() != 1 || cols() != 1) throw std::invalid_argument("Exponentiation only possible for 1x1 matrices");
    return pow((long double)*this,x);
}


inline physics::matrix physics::matrix::operator+=(matrix m) {
    *this = *this + m;
    return *this;
}

inline physics::matrix physics::matrix::operator-=(matrix m) {
    *this = *this - m;
    return *this;
}

inline physics::matrix physics::matrix::operator*=(long double x) {
    *this = *this * x;
    return *this;
}

inline physics::matrix physics::matrix::operator*=(matrix m) {
    *this = *this * m;
    return *this;
}

inline physics::matrix physics::matrix::operator/=(long double x) {
    *this = *this / x;
    return *this;
}


inline bool physics::matrix::operator==(matrix x) const {
    if(rows() != x.rows() || cols() != x.cols()) return false;
    for(int i = 0; i < data.size(); i++) {
        for(int j = 0; j < data.size(); j++) {
            if(data[i][j] != x.data[i][j]) return false;
        }
    }
    return true;
}

inline bool physics::matrix::operator!=(matrix x) const {
    return !(*this == x);
}


inline physics::matrix physics::matrix::T() const {
    matrix out;
    for(int i = 0; i < data[0].size(); i++) {
        std::vector<long double> newRow;
        for(int j = 0; j < data.size(); j++) {
            newRow.push_back(data[j][i]);
        }
        out.data.push_back(newRow);
    }
    return out;
}


inline physics::matrix physics::operator*(long double x, matrix m) {
    return m * x;
}

inline std::string physics::operator+(std::string x, matrix m) {
    return x + (std::string)m;
}
inline std::ostream& physics::operator<<(std::ostream &os, const matrix &m) {
    os << (std::string)m;
    return os;
}

inline physics::matrix physics::abs(matrix m) {
    matrix out;
    for(std::vector<long double> row : m.data) {
        std::vector<long double> newRow;
        for(long double value : row) {
            newRow.push_back(std::abs(value));
        }
        out.data.push_back(newRow);
    }
    return out;
}

inline physics::matrix physics::cross(matrix m1, matrix m2) {
    if(!m1.is_vector() || !m2.is_vector()) throw std::invalid_argument("Cross product only possible for 3D vectors");
    if(m1.size() != 3 || m2.size() != 3) throw std::invalid_argument("Cross product only possible for 3D vectors");

    std::vector<long double> result(3);
    std::vector<long double> a = m1.rows() == 1 ? m1.data[0] : m1.T().data[0];
    std::vector<long double> b = m2.rows() == 1 ? m2.data[0] : m2.T().data[0];

    result[0] = a[1] * b[2] - a[2] * b[1];
    result[1] = a[2] * b[0] - a[0] * b[2];
    result[2] = a[0] * b[1] - a[1] * b[0];

    return matrix(result);
}

// end --- matrix.cpp --- 



// begin --- value.cpp --- 



// begin --- value.h --- 

#pragma once

// begin --- unit.h --- 

#pragma once

#include <string>
#include <vector>


namespace physics {
    // Represents a physical dimension.
    // Holds an int8_t array with the exponents of each SI unit.
    class unit {
    private:
        int8_t si[7];

    public:
        explicit unit(std::vector<int8_t> si_units = {0,0,0,0,0,0,0});

        // Conversions
        operator std::string() const;
        explicit operator std::vector<int8_t>() const;

        // Operators
        unit operator*(unit x) const;
        unit operator/(unit x) const;
        unit operator^(int x) const;

        bool operator<(unit x) const;
        bool operator==(unit x) const;
        bool operator!=(unit x) const;
    };
    std::ostream& operator<<(std::ostream& os, const unit& u);

    // SI Units
    const unit M = unit(std::vector<int8_t>{1,0,0,0,0,0,0}); // Metre
    const unit KG = unit(std::vector<int8_t>{0,1,0,0,0,0,0}); // Kilogram
    const unit S = unit(std::vector<int8_t>{0,0,1,0,0,0,0}); // Second
    const unit A = unit(std::vector<int8_t>{0,0,0,1,0,0,0}); // Ampere
    const unit K = unit(std::vector<int8_t>{0,0,0,0,1,0,0}); // Kelvin
    const unit CD = unit(std::vector<int8_t>{0,0,0,0,0,1,0}); // Candela
    const unit MOL = unit(std::vector<int8_t>{0,0,0,0,0,0,1}); // Mole

    // Derived units
    const unit HZ = S^-1; // Hertz
    const unit N = KG * M / (S^2); // Newton
    const unit J = N * M; // Joule
    const unit W = J / S; // Watt
    const unit PA = N / (M^2); // Pascal
    const unit V = W / A; // Volt
    const unit C = A * S; // Coulomb
    const unit OHM = V / A; // Ohm
    const unit F = C / V; // Farad
    const unit H = OHM * S; // Henry
    const unit SIEMENS = A / V; // Siemens
    const unit WB = V * S; // Weber
    const unit T = WB / (M^2); // Tesla
}

// end --- unit.h --- 




namespace physics {
    // Represents a physical value with dimension.
    class val {
    public:
        matrix v; // Value
        int8_t e; // Exponent
        unit u; // Unit

    public:
        val(long double v);
        val(matrix v);
        val(matrix v, unit u = unit());
        val(matrix v, int8_t e, unit u = unit());

        // Conversions
        std::string operator+(std::string x) const;
        operator std::string() const;
        explicit operator int() const;
        explicit operator float() const;
        explicit operator double() const;
        explicit operator long double() const;
        explicit operator unit() const;

        // Operators
        val operator+(val x) const;
        val operator-(val x) const;
        val operator*(val x) const;
        val operator*(unit x) const;
        val operator/(val x) const;
        val operator/(unit x) const;
        val operator^(double x) const;

        val operator+=(val x);
        val operator-=(val x);

        bool operator<(val x) const;
        bool operator>(val x) const;
        bool operator<=(val x) const;
        bool operator>=(val x) const;
        bool operator==(val x) const;
        bool operator!=(val x) const;

        // Transpose
        val T();

    private:
        void calculate_exponent();
        std::string get_prefix() const;
    };

    // Additional operators
    val operator*(val x, long double y);
    val operator*(long double x, val y);
    val operator/(val x, long double y);
    val operator/(long double x, val y);

    // Conversion operators
    val operator*(matrix x, unit y);
    val operator/(matrix x, unit y);
    std::string operator+(std::string x, val y);
    std::ostream& operator<<(std::ostream& os, const val& v);

    val abs(val v);
    val cross(val v1, val v2);

    // Suffixes
    val operator ""_Y(long double); // Yotta
    val operator ""_Z(long double); // Zetta
    val operator ""_E(long double); // Exa
    val operator ""_P(long double); // Peta
    val operator ""_T(long double); // Tera
    val operator ""_G(long double); // Giga
    val operator ""_M(long double); // Mega
    val operator ""_k(long double); // Kilo
    val operator ""_h(long double); // Hecto
    val operator ""_da(long double); // Deca
    val operator ""_d(long double); // Deci
    val operator ""_c(long double); // Centi
    val operator ""_m(long double); // Milli
    val operator ""_mu(long double); // Micro
    val operator ""_n(long double); // Nano
    val operator ""_p(long double); // Pico
    val operator ""_f(long double); // Femto
    val operator ""_a(long double); // Atto
    val operator ""_z(long double); // Zepto
    val operator ""_y(long double); // Yocto
}



// end --- value.h --- 


#include <cstdint>
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

inline physics::val physics::abs(physics::val v) { return val(abs(v.v), v.e, v.u); }
inline physics::val physics::cross(val v1, val v2) { return val(cross(v1.v, v2.v), v1.e + v2.e, v1.u * v2.u); }

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
    if(u == unit() || (long double)std::abs(e) > 24) return "e" + std::to_string(e) + " ";
    return " " + prefix_names[e];
}

// end --- value.cpp --- 



// begin --- unit.cpp --- 



// begin --- superscript.h --- 

#pragma once

#include <string>
#include <map>


namespace super {
    inline std::map<char, std::string> supertable {
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

    // Returns a string of exponent characters corresponding to the input char or int.
    inline std::string super(char c) {
        return supertable[c];
    }
    inline std::string super(int n) {
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



// end --- superscript.h --- 




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

// end --- unit.cpp --- 



// begin --- print.h --- 

#pragma once

#include <iostream>


namespace physics {
    inline void print() {
        std::cout << std::endl;
    };

    template <typename T, typename... Types>
    void print(T var1, Types...var2) {
        std::cout << var1 << "\t";
        print(var2...);
    }
}

// end --- print.h --- 



// begin --- constants.h --- 

#pragma once
#include <cmath>


namespace physics {
    // Source: Physics Handbook by Carl Nordling & Jonny Österman, Studentlitteratur 2020.

    // Non-SI units
    namespace units {
        // Length
        const val angstrom = 1e-10 * M; // Ångström
        const val XU = 1.002'08e-13 * M; // X-unit
        const val fermi = 1e-15 * M; // Fermi
        const val AU = 1.495'978'70e11 * M; // Astronomical unit
        const val lightyear = 9.460'55e15 * M; // Light-year
        const val parsec = 3.0857e16 * M; // Parsec

        // Area
        const val barn = 1e-28 * M^2; // Barn

        // Time
        const val tropical_year = 31.556'925'974e6 * S; // Tropical year (solar year)
        const val sidereal_year = 31.558'150e6 * S; // Sidereal year (stellar year)
        const val calender_year = 31.536e6 * S; // Calender year
        const val leap_year = 31.6224e6 * S; // Leap year

        // Speed
        const val kmph = 1/3.6 * M/S; // Kilometers per hour

        // Energy
        const val eV = 1.602'176'634e-19 * J; // Electron volt
        const val kcal = 4184 * J; // Kilocalorie

        // Pressure
        const val atm = 1.013'25e5 * PA; // Atmosphere

        // Other
        const val D = 3.33564e-30 * C * M; // Debye
    }

    // Constants
    namespace constants {
        // Empty Space
        const val c_0 = 2.997'924'58e8 * M/S; // Speed of light
        const val mu_0 = 4 * M_PI * 1e-7 * (V*S)/(A*M); // Permeability
        const val epsilon_0 = 8.854'187'817e-12 * (A*S)/(V*M); // Permittivity

        // Gravitation
        const val G = 6.674'08e-11 * (N*(M^2))/(KG^2); // Gravitational constant
        const val g = 9.806'65 * M/(S^2); // Acceleration of gravity at sea level

        // Particle Masses
        const val m_e = 9.109'383'56e-31 * KG; // Electron rest mass
        const val m_mu = 1.883'531'59e-28 * KG; // Muon rest mass
        const val m_p = 1.672'621'90e-27 * KG; // Proton rest mass
        const val m_n = 1.674'927'47e-27 * KG; // Neutron rest mass
        const val m_u = 1.660'539'04e-27 * KG; // Atomic mass constant

        // Atomic Quantities
        const val r_e = 2.817'940'37e-15 * M; // Classical electron radius
        const val a_0 = 5.29177219e-11 * M; // Bohr radius
        const val lambda_e = 2.426'310'28e-12 * M; // Compton electron wavelength
        const val lambda_p = 1.321'409'87e-15 * M; // Compton proton wavelength
        const val E_H = 1.312'750e6 * J/MOL; // Hydrogen atom ground state energy

        // Electric Charge and Magnetic Moment
        const val e = 1.602'176'634e-19 * C; // Elementary charge
        const val mu_B = 9.274'010'22e-24 * J/T; // Bohr magneton
        const val mu_N = 5.050'783'82e-27 * J/T; // Nuclear magneton
        const val mu_e = -9.284'7646e-24 * J/T; // Electron magnetic moment
        const val mu_p = 1.410'606'787e-26 * J/T; // Proton magnetic moment
        const val mu_n = -0.966'2365e-26 * J/T; // Neutron magnetic moment
        const val mu_mu = -4.490'448'26 * J/T; // Muon magnetic moment

        // Quantum Physics, Radiation
        const val h = 6.626'070'15e-34 * J*S; // Planck constant
        const val hbar = h / (2 * M_PI);
        const val R_inf = 1.097'373'1569e7 / M; // Rydberg constant
        const val alpha = 7.297'352'566e-3; // Fine-structure constant
        const val sigma = 5.670'374e-8 * W/((M^2) * (K^4)); // Stefan-Boltzmann constant
        const val k_B = 1.380'649e-23 * J/K; // Boltzmann constant
        const val L = 2.443'004'45e-8 * (V^2)/(K^2); // Lorenz constant

        // Quantities Related to Amount of Substance
        const val N_A = 6.022'140'76e23 / MOL; // Avogadro constant
        const val R = 8.314'462'618 * J/(MOL*K); // Molar gas constant
        const val F = 9.648'533'212e4 * C/MOL; // Faraday constant
    };
};

// end --- constants.h --- 

