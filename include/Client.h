#pragma once
#include "Elgamal.h"
#include "Poly.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <cassert>

class Client
{
private:
    // the size of data x
    int kc;

    std::vector<mpz_t> x;

    // the coefficient of polynomial, the size is kc+1
    std::vector<mpz_t> a;

    // module
    mpz_t p;

public:
    Client(std::vector<mpz_t> &x, mpz_t &p);

    Client();

    /**
     * @brief initialize the data x, and get the coefficient of polynomial
     *
     * @param x
     */
    void init(std::vector<mpz_t> &x);

    void get_co();

    void show_co();

    void get_enc_co(mpz_t &enc_co_1,
                    std::vector<mpz_t> &enc_co_2,
                    elg_pk pk,
                    mpz_t k);

    /**
     * @brief Set the data and initialize, this function must be called after set_p
     *
     * @param x
     */
    void set_data(vector<mpz_t> &x);

    void set_p(mpz_t &p);

    static void sample();
};
