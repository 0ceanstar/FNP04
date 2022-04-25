#include "Server.h"

using namespace std;

Server::Server(std::vector<mpz_t> &y, mpz_t &p)
    : ks(y.size()), y(ks)
{
    init(y);
    mpz_init_set(this->p, p);
}

void Server::init(std::vector<mpz_t> &y)
{
    for (int i = 0; i < ks; i++)
    {
        mpz_init_set(this->y[i], y[i]);
    }
}

void Server::get_enc_data(std::vector<mpz_t> &res,
                          std::vector<mpz_t> &enc_co_2)
{
    for (int i = 0; i < ks; i++)
    {
        mpz_t &cur = res[i];
        mpz_set_ui(cur, 0);
        for (int j = 0; j < enc_co_2.size(); j++)
        {
            mpz_t temp;
            mpz_init(temp);
            mpz_powm_ui(temp, y[i], j, p); // temp = y[i]^j mod(p)

            mpz_mul(temp, temp, enc_co_2[j]); // temp = temp*enc_co
            mpz_mod(temp, temp, p);

            mpz_add(cur, cur, temp);
            mpz_mod(cur, cur, p);

            mpz_clear(temp);
        }
    }
}