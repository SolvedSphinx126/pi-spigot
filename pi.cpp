#include <gmpxx.h>
#include <iostream>

// based on the following paper on formulas for unbounded pi spigot algorithms
// https://www.cs.ox.ac.uk/jeremy.gibbons/publications/spigot.pdf

mpz_class gcd(mpz_class a, mpz_class b) {
    if (a == 0) {
        return b;
    }
    return gcd(b%a, a);
}

class lft {

public:

    mpz_class q;
    mpz_class r;
    mpz_class s;
    mpz_class t;

    lft(int a, int b, int c, int d) {
        q = a;
        r = b;
        s = c;
        t = d;
    }

    lft() {
        lft(0, 0, 0, 0);
    }

    void set(mpz_class a, mpz_class b, mpz_class c, mpz_class d) {
        q = a;
        r = b;
        s = c;
        t = d;
    }

    mpz_class extr(int x) {
        return (q*x + r)/(s*x + t);
    }

    lft operator*(lft &other) {
        lft temp;
        temp.q = q*other.q;
        temp.r = q*other.r + r*other.t;
        temp.s = 0;
        temp.t = t*other.t;

        temp.simplify();
        return temp;
    }

    void simplify() {
        mpz_class gcd1 = gcd(q, r);
        gcd1 = gcd(gcd1, t);
        q /= gcd1;
        r /= gcd1;
        t /= gcd1;
    }

};

int main() {

    lft z = lft(1, 0, 0, 1);
    lft lfti = lft(0, 0, 0, 0);
    lft tmp;

    int k = 1;
    mpz_class n;

    while (k) {
        lfti.set(k, 4*k + 2, 0, 2*k + 1);
        n = z.extr(3);
        if (n == z.extr(4)) {
            tmp.set(10, (-10)*n, 0, 1);
            z = tmp * z;
            std::cout << n << std::flush;
        } else {
            z = z * lfti;
            k++;
        }
    }
}
