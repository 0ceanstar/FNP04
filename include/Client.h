#pragma once
#include "Elgamal.h"
#include "Poly.h"
#include <vector>

class Client
{
private:
    int kc;

    // test do nothing
    std::vector<mpz_t> x;

    std::vector<mpz_t> a;

    mpz_t p;

    void init(std::vector<mpz_t>&x);
public:
    Client(std::vector<mpz_t> &x);
    
};
