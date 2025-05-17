#pragma once

#include <string>
#include <vector>
#include <math.h>





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





    // Represents a physical value with dimension.
    class val {
    private:
        long double v; // Value
        int8_t e; // Exponent
        unit u; // Unit

    public:
        val(double v, unit u = unit());
        val(double v, int8_t e, unit u = unit());

        // Conversions
        operator std::string() const;
        explicit operator int() const;
        explicit operator float() const;
        explicit operator double() const;
        explicit operator long double() const;
        explicit operator unit() const;

        // Operators
        val operator+(val x) const;
        val operator-(val x) const;
        val operator*(val x) const;
        val operator*(unit x) const;
        val operator/(val x) const;
        val operator/(unit x) const;
        val operator^(int x) const;

        bool operator<(val x) const;
        bool operator>(val x) const;
        bool operator<=(val x) const;
        bool operator>=(val x) const;
        bool operator==(val x) const;
        bool operator!=(val x) const;
    };

    // Additional operators
    val operator*(val x, long double y);
    val operator*(long double x, val y);
    val operator/(val x, long double y);
    val operator/(long double x, val y);

    // Conversion operators
    val operator*(long double x, unit y);
    val operator/(long double x, unit y);
    std::string operator+(std::string x, val y);
    std::ostream& operator<<(std::ostream& os, const val& v);

    // Suffixes
    val operator ""_Y(long double v);
    val operator ""_Z(long double v);
    val operator ""_E(long double v);
    val operator ""_P(long double v);
    val operator ""_T(long double v);
    val operator ""_G(long double v);
    val operator ""_M(long double v);
    val operator ""_k(long double v);
    val operator ""_h(long double v);
    val operator ""_da(long double v);
    val operator ""_d(long double v);
    val operator ""_c(long double v);
    val operator ""_m(long double v);
    val operator ""_mu(long double v);
    val operator ""_n(long double v);
    val operator ""_p(long double v);
    val operator ""_f(long double v);
    val operator ""_a(long double v);
    val operator ""_z(long double v);
    val operator ""_y(long double v);





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

    // Non-SI units
    const val Å = 1e-10 * M; // Ångström
    const val fermi = 1e-15 * M; // Fermi
    const val bohr = 0.529'117 * Å; // Bohr
    const val AU = 1.495'978'70e11 * M; // Astronomical unit
    const val lightyear = 6.32e4 * AU; // Light-year
    const val parsec = 3.262 * lightyear; // Parsec

    // Constants
    const val c_0 = 2.997'924'58e8 * M/S; // Speed of light
    const val μ_0 = 4 * M_PI * 1e-7 * (V*S)/(A*M); // Permeability
    const val ε_0 = (val)1 / (μ_0 * c_0^2); // Permittivity
    const val G = 6.674'08e-11 * (N*(M^2))/(KG^2); // Gravitational constant
    const val g = 9.806'65 * M/S; // Acceleration of gravity at sea level
    const val m_e = 9.109'383'56e-31 * KG; // Electron rest mass
    const val m_μ = 1.883'531'59e-28 * KG; // Muon rest mass
    const val m_p = 1.672'621'90e-27 * KG; // Proton rest mass
    const val m_n = 1.674'927'47e-27 * KG; // Neutron rest mass
    const val m_u = 1.660'539'04e-27 * KG; // Atomic mass constant
    const val e = 1.602'176'634e-19 * C; // Elementary charge
    const val h = 6.626'070'15e-34 * J*S; // Planck constant
    const val k_B = 1.380'649e-23 * J/K; // Boltzmann constant
    const val N_A = 6.022'140'76e+23 / MOL; // Avogadro constant
    const val R = k_B * N_A; // Molar gas constant
};