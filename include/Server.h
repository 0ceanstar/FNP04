#pragma once

#include "gmp.h"
#include <vector>

class Server
{
private:
    // the size of data y
    int ks;

    std::vector<mpz_t> y;

    // get the fragment of secret key
    mpz_t ti;

    // module
    mpz_t p;

    void init(std::vector<mpz_t> &y);

public:
    Server(std::vector<mpz_t> &y, mpz_t &ti, mpz_t &p);

    /**
     * @brief Set the fragment of secret key ti
     *
     * @param ti
     */
    void set_ti(mpz_t &ti) { mpz_init_set(this->ti, ti); }

    /**
     * @brief Get the encrypted data y
     *
     * @param res the result, size = ks
     * @param enc_co_1 the ciphertext c1 using elgamal protocol to encrypt polynomial
     * @param enc_co_2 the ciphertext c2 using elgamal protocol to encrypt polynomial
     * @param p module
     */
    void get_enc_data(std::vector<mpz_t> &res,
                      std::vector<mpz_t> &enc_co_2);
};
