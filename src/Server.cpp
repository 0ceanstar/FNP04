#include "Server.h"

using namespace std;

Server::Server(std::vector<mpz_t> &y) : ks(y.size()), y(ks)
{
    init(y);
}

void Server::init(std::vector<mpz_t> &y)
{
    for (int i = 0; i < ks; i++)
    {
        mpz_init_set(this->y[i], y[i]);
    }
}