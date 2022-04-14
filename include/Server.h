#pragma once

#include "gmp.h"
#include <vector>

class Server
{
private:
    int ks;

    std::vector<mpz_t> y;

    void init(std::vector<mpz_t> &y);

public:
    Server(std::vector<mpz_t> &y);
};
