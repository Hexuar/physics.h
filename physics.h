#pragma once

#include <string>
#include <vector>
#include <math.h>





// Represents a physical dimension.
// Holds an int8_t array with the exponents of each SI unit.
class unit {
public:
    unit(const std::vector<int8_t> si_units = {0,0,0,0,0,0,0});
    unit(const int si_unit);
    unit(const std::string si_unit);
    unit(const char* si_unit);

    // String conversion
    std::string to_string() const;
    operator std::string() const;

    // Operators
    unit operator*(const unit x) const;
    unit operator/(const unit x) const;
    unit operator^(int x) const;

    bool operator<(const unit x) const;

private:
    int8_t si[7];
};

std::ostream& operator<<(std::ostream& os, const unit& v);





// Represents a physical value with dimension.
class val {
public:
    long double v;
    unit u;

    val(const double v, const unit u = unit());

    // String conversion
    std::string to_string() const;
    operator std::string() const;

    // Operators
    val operator+(val x) const;
    val operator-(val x) const;
    val operator*(val x) const;
    val operator/(val x) const;
    val operator^(int x) const;

    bool operator<(val x) const;
    bool operator>(val x) const;
};

// Converisons
val operator*(const float x, const unit y);
std::string operator+(const std::string x, val y);

// Value - Unit operations
val operator*(const val x, const unit y);
val operator/(const val x, const unit y);

// Stream
std::ostream& operator<<(std::ostream& os, const val& v);





// SI Units
const unit M = unit(0);
const unit KG = unit(1);
const unit S = unit(2);
const unit A = unit(3);
const unit K = unit(4);
const unit CD = unit(5);
const unit MOL = unit(6);


// Derived units
const unit HZ = (unit)1 / S;
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