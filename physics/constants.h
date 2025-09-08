#pragma once

#include "value.h"
#include <cmath>


namespace physics {
    // Non-SI units
    const val angstrom = 1e-10 * M; // Ångström
    const val fermi = 1e-15 * M; // Fermi
    const val AU = 1.495'978'70e11 * M; // Astronomical unit
    const val lightyear = 6.32e4 * AU; // Light-year
    const val parsec = 3.262 * lightyear; // Parsec

    // Constants
    namespace constant {
        const val c_0 = 2.997'924'58e8 * M/S; // Speed of light
        const val mu_0 = 4 * M_PI * 1e-7 * (V*S)/(A*M); // Permeability
        const val epsilon_0 = (val)1 / (mu_0 * (c_0^2)); // Permittivity
        const val G = 6.674'08e-11 * (N*(M^2))/(KG^2); // Gravitational constant
        const val g = 9.806'65 * M/S; // Acceleration of gravity at sea level
        const val m_e = 9.109'383'56e-31 * KG; // Electron rest mass
        const val m_mu = 1.883'531'59e-28 * KG; // Muon rest mass
        const val m_p = 1.672'621'90e-27 * KG; // Proton rest mass
        const val m_n = 1.674'927'47e-27 * KG; // Neutron rest mass
        const val m_u = 1.660'539'04e-27 * KG; // Atomic mass constant
        const val a_0 = 5.29177219e-11 * M; // Bohr radius
        const val e = 1.602'176'634e-19 * C; // Elementary charge
        const val h = 6.626'070'15e-34 * J*S; // Planck constant
        const val k_B = 1.380'649e-23 * J/K; // Boltzmann constant
        const val N_A = 6.022'140'76e+23 / MOL; // Avogadro constant
        const val R = k_B * N_A; // Molar gas constant
    };
};