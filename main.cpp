#include "physics.h"


using namespace physics;
using namespace constant;

void example_a() {
    print("\nExample A");

    // A 12V battery with two resistors wired in parallel
    val u = 12 * V;
    val r_1 = 10'000 * OHM;
    val r_2 = 5.0_k * OHM;

    // Parallel wiring & Ohms law
    val r = (r_1 * r_2) / (r_1 + r_2);
    val i = u / r;

    // Current sharing
    val i_1 = i * r_1 / (r_1 + r_2);
    val i_2 = i * r_2 / (r_1 + r_2);

    // Print resistances
    print(r, r_1, r_2);

    // Print currents
    print(i, i_1, i_2);
}

void example_b() {
    print("\nExample B");

    // Calculate the Bohr radius and compare to built-in constant
    print(a_0, (epsilon_0 * (h^2)) / (M_PI * m_e * (e^2)));
}

int main() {
    example_a();
    example_b();
}
