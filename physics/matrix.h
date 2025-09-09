#pragma once

#include <string>
#include <vector>

namespace physics {

    struct matrix {
    public:
        std::vector<std::vector<long double>> data;

        int rows() const;
        int cols() const;
        long double first() const;

    public:
        matrix();
        matrix(long double value);
        matrix(std::vector<long double> values);
        matrix(std::vector<std::vector<long double>> values);

        std::string operator+(std::string x) const;
        operator std::string() const;
        explicit operator int() const;
        explicit operator float() const;
        explicit operator double() const;
        explicit operator long double() const;

        matrix operator+(matrix m) const;
        matrix operator-(matrix m) const;
        matrix operator*(long double x) const;
        matrix operator*(matrix m) const;
        matrix operator/(long double x) const;
        matrix operator/(matrix m) const;
        matrix operator^(double) const;

        matrix operator+=(matrix m);
        matrix operator-=(matrix m);
        matrix operator*=(long double x);
        matrix operator*=(matrix m);
        matrix operator/=(long double x);

        bool operator==(matrix m) const;
        bool operator!=(matrix m) const;

        // Transpose
        matrix T();
    };

    matrix operator*(long double x, matrix m);

    std::string operator+(std::string x, matrix m);
    std::ostream& operator<<(std::ostream &os, const matrix &m);

    matrix abs(matrix m);

}