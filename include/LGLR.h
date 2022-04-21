#pragma once
#include <iostream>
#include <vector>
#include <gmp.h>
#include "Elgamal.h"
class LGLR
{
private:
    int n;

    std::vector<mpz_t> a; // the coefficient of polynomial

    std::vector<mpz_t> x;

    std::vector<mpz_t> temp;

    std::vector<mpz_t> b;

    std::vector<mpz_t> c;

    mpz_t y1;

    gmp_randstate_t grt;

    mpz_t p;

    // To initialize all data, and get the result
    void init();

    void mul(std::vector<mpz_t> &f, int len, mpz_t t);

    void dev(std::vector<mpz_t> &f, std::vector<mpz_t> &r, mpz_t t);

public:
    LGLR(std::vector<mpz_t> &x, mpz_t p);

    // TODO: do not forget to free the useless space
    ~LGLR();

    void get_co(std::vector<mpz_t> &a);

    static void sample();
};