#include "matrix.h"
#include <stdexcept>
#include <math.h>


inline int physics::matrix::rows() const { return data.size(); }
inline int physics::matrix::cols() const { return data[0].size(); }
inline long double physics::matrix::first() const { return data[0][0]; }


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

    if(cols() != x.rows()) throw std::invalid_argument("Incompatible matrices.");

    matrix out;
    for(int i = 0; i < rows(); i++) {
        std::vector<long double> newRow;
        for(int j = 0; j < x.cols(); j++) {
            long double sum = 0;
            for(int k = 0; k < rows(); k++) {
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


inline physics::matrix physics::matrix::T() {
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