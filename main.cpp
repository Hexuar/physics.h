#include "physics.h"
#include "print.h"

int main() {
    val s = 10 * M;
    val t = 4 * S;
    val m = 20 * KG;

    val v = s / t;
    val a = v / t;
    val f = a * m;
    val w = f * s;
    val p = w / t;

    print("v: " + v);
    print("a: " + a);
    print("f: " + f);
    print("w: " + w);
    print("p: " + p);

    val v_2 = 14 * M / S;
    print(v_2);

    val f1 = 7 * N;
    val f2 = 12 * N;
    val f3 = f1+f2;

    print(f1);
    print(f2);
    print(f3);
}