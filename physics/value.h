#pragma once

#include "unit.h"


namespace physics {
    // Represents a physical value with dimension.
    class val {
    public:
        long double v; // Value
        int8_t e; // Exponent
        unit u; // Unit

    public:
        val(double v, unit u = unit());
        val(double v, int8_t e, unit u = unit());

        //
        void calculate_exponent();
        std::string get_prefix() const;

        // Conversions
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
        val operator^(int x) const;

        bool operator<(val x) const;
        bool operator>(val x) const;
        bool operator<=(val x) const;
        bool operator>=(val x) const;
        bool operator==(val x) const;
        bool operator!=(val x) const;
    };

    // Additional operators
    val operator*(val x, long double y);
    val operator*(long double x, val y);
    val operator/(val x, long double y);
    val operator/(long double x, val y);

    // Conversion operators
    val operator*(long double x, unit y);
    val operator/(long double x, unit y);
    std::string operator+(std::string x, val y);
    std::ostream& operator<<(std::ostream& os, const val& v);

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

