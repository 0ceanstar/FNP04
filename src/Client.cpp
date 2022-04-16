#include "Client.h"

Client::Client(std::vector<mpz_t> &x, mpz_t &p) : kc(x.size()), x(kc), a(kc + 1)
{
    mpz_init_set(this->p, p);
    init(x);
}
Client::Client()
{
}

void Client::init(vector<mpz_t> &x)
{
    for (int i = 0; i < kc; i++)
    {
        mpz_init_set(this->x[i], x[i]);
    }

    Poly poly(this->x, p);

    poly.get_co(a);

    // printf("The coefficient of polynomial is :\n");
    // for (int i = 0; i < kc + 1; i++)
    // {
    //     gmp_printf("%Zd\t", a[i]);
    // }
    // printf("\n");
}

void Client::get_enc_co(mpz_t &enc_co_1,
                        std::vector<mpz_t> &enc_co_2,
                        elg_pk pk,
                        mpz_t k)
{
    for (int i = 0; i < a.size(); i++)
    {
        Elgamal::elg_enc(enc_co_1, enc_co_2[i], a[i], pk, k);
    }
}

void Client::set_data(vector<mpz_t> &x)
{
    kc = x.size();
    init(x);
}

void Client::set_p(mpz_t &p)
{
    mpz_init_set(this->p, p);
}