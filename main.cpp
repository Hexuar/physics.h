#include "physics.h"
#include "print.h"

void test() {
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
}

int main() {
    test();
}
