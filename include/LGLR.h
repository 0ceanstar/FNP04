#pragma once
#include <iostream>
#include <vector>
#include <gmp.h>
class LGLR
{
private:
    int n;

    std::vector<mpz_t> a; // the coefficient of polynomial

    std::vector<mpz_t> x, b, c, temp, y;

    gmp_randstate_t grt;

    mpz_t p;

    // To initialize all data, and get the result
    void init();

    void qm(mpz_t &res, mpz_t a, mpz_t b);

public:
    LGLR(std::vector<mpz_t> &x, mpz_t p);

    // TODO: do not forget to free the useless space
    ~LGLR();

    static void sample();
};