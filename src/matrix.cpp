#include "matrix.h"
#include <stdexcept>
#include <math.h>


inline int physics::matrix::rows() const { return data.size(); }
inline int physics::matrix::cols() const { return data[0].size(); }
inline long double physics::matrix::first() const { return data[0][0]; }
inline int physics::matrix::size() const { return data.size() * data[0].size(); }

inline bool physics::matrix::is_scalar() const { return rows() == 1 && cols() == 1; }
inline bool physics::matrix::is_vector() const { return rows() == 1 || cols() == 1; }


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
    if(!is_scalar()) throw std::invalid_argument("Only 1x1 matrices can be converted to scalar values.");
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
    if(x.is_scalar()) return *this * x.first();
    if(is_scalar()) return first() * x;

    // Automatically transpose vectors
    if(x.is_vector() && cols() != x.rows()) x = x.T();

    if(cols() != x.rows()) throw std::invalid_argument("Incompatible matrices.");

    matrix out;
    for(int i = 0; i < rows(); i++) {
        std::vector<long double> newRow;
        for(int j = 0; j < x.cols(); j++) {
            long double sum = 0;
            for(int k = 0; k < cols(); k++) {
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
    if(!m.is_scalar()) throw std::invalid_argument("Dividing by matrix of size other than 1x1 is undefined.");
    return *this * (1/m.first());
}

inline physics::matrix physics::matrix::operator^(double x) const {
    if(!is_scalar()) throw std::invalid_argument("Exponentiation only possible for 1x1 matrices");
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
    // Size check
    if(rows() != x.rows() || cols() != x.cols()) return false;

    // Value check
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


inline physics::matrix physics::matrix::T() const {
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

inline physics::matrix physics::cross(matrix m1, matrix m2) {
    if(!m1.is_vector() || !m2.is_vector()) throw std::invalid_argument("Cross product only possible for 3D vectors");
    if(m1.size() != 3 || m2.size() != 3) throw std::invalid_argument("Cross product only possible for 3D vectors");

    std::vector<long double> result(3);
    std::vector<long double> a = m1.rows() == 1 ? m1.data[0] : m1.T().data[0];
    std::vector<long double> b = m2.rows() == 1 ? m2.data[0] : m2.T().data[0];

    result[0] = a[1] * b[2] - a[2] * b[1];
    result[1] = a[2] * b[0] - a[0] * b[2];
    result[2] = a[0] * b[1] - a[1] * b[0];

    return matrix(result);
}