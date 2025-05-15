#pragma once
#include <cstdint>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <stdexcept>





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
    val operator+(val x);
    val operator-(val x);
    val operator*(val x);
    val operator/(val x);
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