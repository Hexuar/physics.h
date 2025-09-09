#include <string>
#include <vector>

namespace physics {

    struct matrix {
        std::vector<std::vector<long double>> data;

        matrix();
        matrix(long double value);
        matrix(std::vector<long double> values);
        matrix(std::vector<std::vector<long double>> values);

        operator std::string() const;

        matrix operator*(long double x);

        matrix operator*=(long double x);
    };

    std::ostream& operator<<(std::ostream &os, const matrix &m);

}