#pragma once

#include "value.h"
#include <cmath>


namespace physics {

    // Non-SI units
    namespace units {
        const val angstrom = 1e-10 * M; // Ångström
        const val fermi = 1e-15 * M; // Fermi
        const val AU = 1.495'978'70e11 * M; // Astronomical unit
        const val lightyear = 6.32e4 * AU; // Light-year
        const val parsec = 3.262 * lightyear; // Parsec
        const val barn = 1e-28 * M^2; // Barn
        const val kcal = 4184 * J; // Kilocalorie
        const val atm = 1.013'25e5 * PA; // Atmosphere
        const val D = 3.33564e-30 * C * M; // Debye
        const val eV = 1.602'176'634e-19 * J; // Electron volt
    }

    // Constants
    namespace constants {
        // Empty Space
        const val c_0 = 2.997'924'58e8 * M/S; // Speed of light
        const val mu_0 = 4 * M_PI * 1e-7 * (V*S)/(A*M); // Permeability
        const val epsilon_0 = 8.854'187'817e-12 * (A*S)/(V*M); // Permittivity

        // Gravitation
        const val G = 6.674'08e-11 * (N*(M^2))/(KG^2); // Gravitational constant
        const val g = 9.806'65 * M/(S^2); // Acceleration of gravity at sea level

        // Particle Masses
        const val m_e = 9.109'383'56e-31 * KG; // Electron rest mass
        const val m_mu = 1.883'531'59e-28 * KG; // Muon rest mass
        const val m_p = 1.672'621'90e-27 * KG; // Proton rest mass
        const val m_n = 1.674'927'47e-27 * KG; // Neutron rest mass
        const val m_u = 1.660'539'04e-27 * KG; // Atomic mass constant

        // Atomic Quantities
        const val r_e = 2.817'940'37e-15 * M; // Classical electron radius
        const val a_0 = 5.29177219e-11 * M; // Bohr radius
        const val lambda_e = 2.426'310'28e-12 * M; // Compton electron wavelength
        const val lambda_p = 1.321'409'87e-15 * M; // Compton proton wavelength
        const val E_H = 1.312'750e6 * J/MOL; // Hydrogen atom ground state energy

        // Electric Charge and Magnetic Moment
        const val e = 1.602'176'634e-19 * C; // Elementary charge
        const val mu_B = 9.274'010'22e-24 * J/T; // Bohr magneton
        const val mu_N = 5.050'783'82e-27 * J/T; // Nuclear magneton
        const val mu_e = -9.284'7646e-24 * J/T; // Electron magnetic moment
        const val mu_p = 1.410'606'787e-26 * J/T; // Proton magnetic moment
        const val mu_n = -0.966'2365e-26 * J/T; // Neutron magnetic moment
        const val mu_mu = -4.490'448'26 * J/T; // Muon magnetic moment

        // Quantum Physics, Radiation
        const val h = 6.626'070'15e-34 * J*S; // Planck constant
        const val hbar = h / (2 * M_PI);
        const val R_inf = 1.097'373'1569e7 / M; // Rydberg constant
        const val alpha = 7.297'352'566e-3; // Fine-structure constant
        const val sigma = 5.670'374e-8 * W/((M^2) * (K^4)); // Stefan-Boltzmann constant
        const val k_B = 1.380'649e-23 * J/K; // Boltzmann constant
        const val L = 2.443'004'45e-8 * (V^2)/(K^2); // Lorenz constant

        // Quantities Related to Amount of Substance
        const val N_A = 6.022'140'76e23 / MOL; // Avogadro constant
        const val R = 8.314'462'618 * J/(MOL*K); // Molar gas constant
        const val F = 9.648'533'212e4 * C/MOL; // Faraday constant
    };
};