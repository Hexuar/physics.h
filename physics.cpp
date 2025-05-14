#include "physics.h"
#include "superscript.h"




// UNIT //

std::string si_strings[7] = {"K","m","A","s","mol","kg","cd"};

std::map<std::string, std::string> si_special_names{
    { "s⁻¹", "Hz" },
    { "ms⁻²kg", "N" },
    { "m⁻¹s⁻²kg", "Pa" },
    { "m²s⁻²kg", "J" },
    { "m²s⁻³kg", "W" },
    { "As", "C" },
    { "m²A⁻¹s⁻³kg", "V" },
    { "m⁻²A²s⁴kg⁻¹", "F" },
    { "m²A⁻²s⁻³kg", "Ω" },
    { "m⁻²A²s³kg⁻¹", "S" },
    { "m²A⁻¹s⁻²kg", "Wb" },
    { "A⁻¹s⁻²kg", "T" },
    { "m²A⁻²s⁻²kg", "H" },
    { "m⁻²cd", "lx" },
};

unit::unit(const std::vector<int8_t>& si_units) {
    int size = si_units.size();
    for(int i = 0; i < std::min(7, size); i++) {
        si[i] = si_units[i];
    }
}
unit::unit(const int& si_unit) {
    si[si_unit] = 1;
}
unit::unit(const std::string& si_unit) {
    for(int i = 0; i < 7; i++) {
        si[i] = 0;
        if(si_unit == si_strings[i]) {
            si[i] = 1;
        }
    }
}
unit::unit(const char* si_unit) {
    for(int i = 0; i < 7; i++) {
        si[i] = 0;
        if(si_unit == si_strings[i]) {
            si[i] = 1;
        }
    }
}

std::string unit::to_string() {
    std::string output = "";

    for(int i = 0; i < 7; i++) {
        int8_t u = si[i];
        if(u != 0) {
            output += si_strings[i];
            if(u != 1) {
                output += super(u);
            }
        }
    }

    if(si_special_names[output] != "") output = si_special_names[output];

    return output;
}

unit unit::operator*(const unit& x) {
    std::vector<int8_t> si_units;
    for(int i = 0; i < 7; i++) {
        si_units.push_back(si[i] + x.si[i]);
    }
    return unit(si_units);
}
unit unit::operator/(const unit& x) {
    std::vector<int8_t> si_units;
    for(int i = 0; i < 7; i++) {
        si_units.push_back(si[i] - x.si[i]);
    }
    return unit(si_units);
}





// VAL //

val::val(const double& value, const class unit& unit) {
    this->value = value;
    this->u = unit;
}

std::string val::to_string() {
    return std::to_string(value) + " " + u.to_string();
}

val val::operator+(val& x) {
    if(u.to_string() != x.u.to_string()) throw std::invalid_argument("Unit Error");
    return val(value + x.value, u);
}
val val::operator-(val& x) {
    if(u.to_string() != x.u.to_string()) throw std::invalid_argument("Unit Error");
    return val(value - x.value, u);
}
val val::operator*(val& x) {
    return val(value * x.value, u * x.u);
}
val val::operator/(val& x) {
    return val(value / x.value, u / x.u);
}

val operator*(const float& x, const unit& y){
    return val(x, y);
}
std::string operator+(const std::string& x, val& y){
    return x + y.to_string();
}
