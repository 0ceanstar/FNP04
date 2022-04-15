#include "Client.h"

Client::Client(std::vector<mpz_t> &x) : kc(x.size()), x(kc), a(kc + 1)
{
    init(x);
}

void Client::init(vector<mpz_t> &x)
{
    for (int i = 0; i < kc; i++)
    {
        mpz_init_set(this->x[i], x[i]);
    }

    elgamal.get_mod(p);

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
                        vector<mpz_t> &enc_co_2)
{
    for (int i = 0; i < kc + 1; i++)
    {
        elgamal.elg_enc(enc_co_1, enc_co_2[i], a[i], elgamal.pk);
    }
}
