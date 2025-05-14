#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <map>
#include <stdexcept>

#include "superscript.h"




// Unit
class unit {
public:
    unit(const std::vector<int8_t>& si_units = {0,0,0,0,0,0,0});
    unit(const int& si_unit);
    unit(const std::string& si_unit);
    unit(const char* si_unit);

    std::string to_string();

    unit operator*(const unit& x);
    unit operator/(const unit& x);

private:
    int8_t si[7];
};


// SI Units
const unit K = unit(0);
const unit M = unit(1);
const unit A = unit(2);
const unit S = unit(3);
const unit MOL = unit(4);
const unit KG = unit(5);
const unit CD = unit(6);





// Value
class val {
public:
    long double value;
    unit u;

    val(const double& value, const unit& u = unit());

    std::string to_string();

    val operator+(val& x);
    val operator-(val& x);
    val operator*(val& x);
    val operator/(val& x);
};

val operator*(const float& x, const unit& y);
std::string operator+(const std::string& x, val& y);
