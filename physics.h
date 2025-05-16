#pragma once

#include <string>
#include <vector>
#include <math.h>





// Represents a physical dimension.
// Holds an int8_t array with the exponents of each SI unit.
class unit {
private:
    int8_t si[7];

public:
    unit(std::vector<int8_t> si_units = {0,0,0,0,0,0,0});

    // String conversion
    operator std::string() const;

    // Operators
    unit operator*(unit x) const;
    unit operator/(unit x) const;
    unit operator^(int x) const;

    bool operator<(unit x) const;
    bool operator!=(unit x) const;
};
std::ostream& operator<<(std::ostream& os, const unit& v);





// Represents a physical value with dimension.
class val {
public:
    long double v;
    unit u;

    val(double v, unit u = unit());

    // Conversions
    operator std::string() const;
    explicit operator int() const;
    explicit operator float() const;
    explicit operator double() const;
    explicit operator long double() const;
};

// Operators
val operator+(val x, val y);

val operator-(val x, val y);

val operator*(val x, val y);
val operator*(val x, long double y);
val operator*(long double x, val y);
val operator*(val x, unit y);

val operator/(val x, val y);
val operator/(val x, long double y);
val operator/(long double x, val y);
val operator/(val x, unit y);

val operator^(val x, int y);

bool operator<(val x, val y);
bool operator>(val x, val y);

// Converison operators
val operator*(float x, unit y);
std::string operator+(std::string x, val y);
std::ostream& operator<<(std::ostream& os, const val& v);





// SI Units
const unit M = unit(std::vector<int8_t>{1,0,0,0,0,0,0});
const unit KG = unit(std::vector<int8_t>{0,1,0,0,0,0,0});
const unit S = unit(std::vector<int8_t>{0,0,1,0,0,0,0});
const unit A = unit(std::vector<int8_t>{0,0,0,1,0,0,0});
const unit K = unit(std::vector<int8_t>{0,0,0,0,1,0,0});
const unit CD = unit(std::vector<int8_t>{0,0,0,0,0,1,0});
const unit MOL = unit(std::vector<int8_t>{0,0,0,0,0,0,1});

// Derived units
const unit HZ = unit() / S;
const unit N = KG * M / (S^2);
const unit J = N * M;
const unit W = J / S;
const unit PA = N / (M^2);
const unit V = W / A;
const unit C = A * S;
const unit OHM = V / A;
const unit F = C / V;
const unit H = OHM * S;
const unit SIEMENS = A / V;
const unit WB = V * S;
const unit T = WB / (M^2);

// Constants
const val c_0 = 2.997'924'58e8 * M/S;
const val μ_0 = 4 * M_PI * 1e-7 * (V*S)/(A*M);
const val ε_0 = (val)1 / (μ_0 * c_0^2);
const val G = 6.674'08e-11 * (N*(M^2))/(KG^2);
const val g = 9.806'65 * M/S;
const val m_e = 9.109'383'56e-31 * KG;
const val m_μ = 1.883'531'59e-28 * KG;
const val m_p = 1.672'621'90e-27 * KG;
const val m_n = 1.674'927'47e-27 * KG;
const val m_u = 1.660'539'04e-27 * KG;
const val e = 1.602'176'634e-19 * C;
const val h = 6.626'070'15e-34 * J*S;
const val k_B = 1.380'649e-23 * J/K;
const val N_A = 6.022'140'76e+23 / MOL;
const val R = k_B * N_A;