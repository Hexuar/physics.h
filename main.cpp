#include "physics.h"
#include "print.h"


using namespace physics;

int main() {
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
