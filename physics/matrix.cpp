#include "matrix.h"


using namespace physics;

matrix::matrix() {}
matrix::matrix(long double value) {
    data.push_back({value});
}
matrix::matrix(std::vector<long double> values) {
    data.push_back({values});
}
matrix::matrix(std::vector<std::vector<long double>> values) {
    data = values;
}

matrix::operator std::string() const {
    std::string string = "[ ";
    for(std::vector<long double> row : data) {
        string += "[ ";
        for(long double value : row) {
            string += std::to_string(value) + " ";
        }
        string += "]";
    }
    string += " ]";
    return string;
}

matrix matrix::operator*(long double x) {
    matrix mat;
    for(std::vector<long double> row : data) {
        std::vector<long double> newRow;
        for(long double value : row) {
            newRow.push_back(value * x);
        }
        mat.data.push_back(newRow);
    }
    return mat;
}

matrix matrix::operator*=(long double x) {
    *this = *this * x;
    return *this;
}


std::ostream& physics::operator<<(std::ostream &os, const matrix &m) {
    os << (std::string)m;
    return os;
}