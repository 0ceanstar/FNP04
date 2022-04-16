#pragma once
#include "Elgamal.h"
#include "Poly.h"
#include <vector>

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

    /**
     * @brief initialize the data x, and get the coefficient of polynomial
     *
     * @param x
     */

public:
    Elgamal elgamal;
    Client(std::vector<mpz_t> &x);
    void init(std::vector<mpz_t> &x);

    /**
     * @brief Get the encrypted coefficient
     *
     * @param enc_co_1 elgamal ciphertext c1
     * @param enc_co_2 size = kc+1, elgamal ciphertext c2
     * @param co size = kc+1
     * @param pk elgamal public key
     */
    void get_enc_co(mpz_t &enc_co_1,
                    std::vector<mpz_t> &enc_co_2);
};
