#pragma once
#include <cstdint>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <stdexcept>
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

    // Operators
    unit operator*(const unit x) const;
    unit operator/(const unit x) const;

private:
    int8_t si[7];
};





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
};

// Converisons
val operator*(const float x, const unit y);
std::string operator+(const std::string x, val y);

// Value - Unit operations
val operator*(const val x, const unit y);
val operator/(const val x, const unit y);





// SI Units
const unit K = unit(0);
const unit M = unit(1);
const unit A = unit(2);
const unit S = unit(3);
const unit MOL = unit(4);
const unit KG = unit(5);
const unit CD = unit(6);

// Derived units
const unit HZ = unit(std::vector<int8_t>{0,0,0,-1,0,0,0});
const unit N = unit(std::vector<int8_t>{0,1,0,-2,0,1,0});
const unit PA = unit(std::vector<int8_t>{0,-1,0,-2,0,1,0});
const unit J = unit(std::vector<int8_t>{0,2,0,-2,0,1,0});
const unit W = unit(std::vector<int8_t>{0,2,0,-3,0,1,0});
const unit C = unit(std::vector<int8_t>{0,0,1,1,0,0,0});
const unit V = unit(std::vector<int8_t>{0,2,-1,-3,0,1,0});
const unit F = unit(std::vector<int8_t>{0,-2,2,4,0,-1,0});
const unit OHM = unit(std::vector<int8_t>{0,2,-2,-3,0,1,0});
const unit SIEMENS = unit(std::vector<int8_t>{0,-2,2,3,0,-1,0});
const unit WB = unit(std::vector<int8_t>{0,2,-1,-2,0,1,0});
const unit T = unit(std::vector<int8_t>{0,0,-1,-2,0,1,0});
const unit H = unit(std::vector<int8_t>{0,2,-2,-2,0,1,0});
const unit LX = unit(std::vector<int8_t>{0,-2,0,0,0,0,1});



// Constants
const val c_0 = 2.997'924'58 * pow(10, 8) * M/S;
const val μ_0 = 4 * M_PI * pow(10, -7) * (V*S)/(A*M);
const val ε_0 = (val)1 / (μ_0 * c_0 * c_0);
const val G = 6.674'08 * pow(10, -11) * (N*M*M)/(KG*KG);
const val g = 9.806'65 * M/S;
const val m_e = 9.109'383'56 * pow(10,-31) * KG;
const val m_μ = 1.883'531'59 * pow(10,-28) * KG;
const val m_p = 1.672'621'90 * pow(10,-27) * KG;
const val m_n = 1.674'927'47 * pow(10,-27) * KG;
const val m_u = 1.660'539'04 * pow(10,-27) * KG;
const val e = 1.602'176'634 * pow(10,-19) * C;
const val h = 6.626'070'15 * pow(10,-34) * J*S;
const val k_B = 1.380'649 * pow(10,-23) * J/K;
const val N_A = 6.022'140'76 * pow(10,23);
const val R = k_B * N_A;
