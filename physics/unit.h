#pragma once

#include <string>
#include <vector>


namespace physics {
    // Represents a physical dimension.
    // Holds an int8_t array with the exponents of each SI unit.
    class unit {
    private:
        int8_t si[7];

    public:
        explicit unit(std::vector<int8_t> si_units = {0,0,0,0,0,0,0});

        // Conversions
        operator std::string() const;
        explicit operator std::vector<int8_t>() const;

        // Operators
        unit operator*(unit x) const;
        unit operator/(unit x) const;
        unit operator^(int x) const;

        bool operator<(unit x) const;
        bool operator==(unit x) const;
        bool operator!=(unit x) const;
    };
    std::ostream& operator<<(std::ostream& os, const unit& u);

    // SI Units
    const unit M = unit(std::vector<int8_t>{1,0,0,0,0,0,0}); // Metre
    const unit KG = unit(std::vector<int8_t>{0,1,0,0,0,0,0}); // Kilogram
    const unit S = unit(std::vector<int8_t>{0,0,1,0,0,0,0}); // Second
    const unit A = unit(std::vector<int8_t>{0,0,0,1,0,0,0}); // Ampere
    const unit K = unit(std::vector<int8_t>{0,0,0,0,1,0,0}); // Kelvin
    const unit CD = unit(std::vector<int8_t>{0,0,0,0,0,1,0}); // Candela
    const unit MOL = unit(std::vector<int8_t>{0,0,0,0,0,0,1}); // Mole

    // Derived units
    const unit HZ = S^-1; // Hertz
    const unit N = KG * M / (S^2); // Newton
    const unit J = N * M; // Joule
    const unit W = J / S; // Watt
    const unit PA = N / (M^2); // Pascal
    const unit V = W / A; // Volt
    const unit C = A * S; // Coulomb
    const unit OHM = V / A; // Ohm
    const unit F = C / V; // Farad
    const unit H = OHM * S; // Henry
    const unit SIEMENS = A / V; // Siemens
    const unit WB = V * S; // Weber
    const unit T = WB / (M^2); // Tesla
}