#pragma once

#include "gmp.h"
#include <vector>

class Server
{
private:
    // the size of data y
    int ks;

    std::vector<mpz_t> y;

    // module
    mpz_t p;

    void init(std::vector<mpz_t> &y);

public:
    Server(std::vector<mpz_t> &y, mpz_t &p);

    /**
     * @brief Get the encrypted data y
     *
     * @param res the result, size = ks
     * @param enc_co_2 the ciphertext c2 using elgamal protocol to encrypt polynomial
     */
    void get_enc_data(std::vector<mpz_t> &res,
                      std::vector<mpz_t> &enc_co_2);
};
