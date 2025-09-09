#include <string>
#include <vector>

namespace physics {

    class matrix {
        std::vector<std::vector<long double>> data;

    public:
        int rows() const;
        int cols() const;

    public:
        matrix();
        matrix(long double value);
        matrix(std::vector<long double> values);
        matrix(std::vector<std::vector<long double>> values);

        operator std::string() const;

        matrix operator+(matrix m) const;
        matrix operator-(matrix m) const;
        matrix operator*(long double x) const;
        matrix operator*(matrix m) const;
        matrix operator/(long double x) const;

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

}