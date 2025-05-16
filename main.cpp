#include "physics.h"
#include "print.h"

int main() {
    val u = 12 * V;
    val r_1 = 10'000 * OHM;
    val r_2 = 5'000 * OHM;

    val r_tot = (r_1 * r_2) / (r_1 + r_2);
    val i = u / r_tot;

    val i_1 = i * r_1 / (r_1 + r_2);
    val i_2 = i * r_2 / (r_1 + r_2);

    print(i, i_1, i_2);

    print(N_A);
}