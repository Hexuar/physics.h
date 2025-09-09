#include "physics.h"


using namespace physics;
using namespace constant;

void example_a() {
    print("\nExample A");

    val s = 2000 * M; // Values are defined by multiplying a number with a unit. This will represent 2000 metres.
    val t = 1.0_k * S; // Suffixes can also be used to add exponents to your values, provided they are defined as decimals. This will represent 1000 seconds.
    val v = s / t; // Regular operations can be performed on physics values.

    print(v); // We can print our result to the console using the print command.

    val m = 0.52 * KG;
    val F = m * g; // There are many constants included. physics::constants::g is the gravitational constant at sea level.

    val h = 1.57_k * M;
    val E = m * g * h;

    print(F, E); // The print function can take any number of arguments.
}

void example_b() {
    print("\nExample B");

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

void example_c() {
    print("\nExample C");

    // Calculate the Bohr radius and compare to built-in constant
    print(a_0, (epsilon_0 * (h^2)) / (M_PI * m_e * (e^2)));
}

int main() {
    example_a();
    example_b();
    example_c();
}
