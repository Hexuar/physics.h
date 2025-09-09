#include "matrix.h"
#include <iostream>
#include <stdexcept>

using namespace physics;

int matrix::rows() const {
    return data.size();
}
int matrix::cols() const {
    return data[0].size();
}

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

matrix matrix::operator+(matrix m) const {
    if(rows() != m.rows() || cols() != m.cols()) throw std::invalid_argument("Incompatible matrices");

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
matrix matrix::operator-(matrix m) const {
    return *this + -1 * m;
}
matrix matrix::operator*(long double x) const {
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
matrix matrix::operator*(matrix x) const {
    if(cols() != x.rows()) throw std::invalid_argument("Incompatible matrices");

    matrix out;
    for(int i = 0; i < data.size(); i++) {
        std::vector<long double> newRow;
        for(int j = 0; j < data.size(); j++) {
            long double sum = 0;
            for(int k = 0; k < data[0].size(); k++) {
                sum += data[j][k] * x.T().data[i][k];
            }
            newRow.push_back(sum);
        }
        out.data.push_back(newRow);
    }
    return out.T();
}
matrix matrix::operator/(long double x) const {
    return *this * (1/x);
}

matrix matrix::operator+=(matrix m) {
    *this = *this + m;
    return *this;
}
matrix matrix::operator-=(matrix m) {
    *this = *this - m;
    return *this;
}
matrix matrix::operator*=(long double x) {
    *this = *this * x;
    return *this;
}
matrix matrix::operator*=(matrix m) {
    *this = *this * m;
    return *this;
}
matrix matrix::operator/=(long double x) {
    *this = *this / x;
    return *this;
}

bool matrix::operator==(matrix x) const {
    if(rows() != x.rows() || cols() != x.cols()) return false;
    for(int i = 0; i < data.size(); i++) {
        for(int j = 0; j < data.size(); j++) {
            if(data[i][j] != x.data[i][j]) return false;
        }
    }
    return true;
}
bool matrix::operator!=(matrix x) const {
    return !(*this == x);
}

matrix matrix::T() {
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

matrix physics::operator*(long double x, matrix m) {
    return m * x;
}

std::string physics::operator+(std::string x, matrix m) {
    return x + (std::string)m;
}
std::ostream& physics::operator<<(std::ostream &os, const matrix &m) {
    os << (std::string)m;
    return os;
}