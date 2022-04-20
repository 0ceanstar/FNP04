#include "LGLR.h"
using namespace std;

LGLR::LGLR(vector<mpz_t> &x, mpz_t p) : n(x.size()), a(n + 1), x(n)
{
    mpz_init_set(this->p, p);
    for (int i = 0; i < n; i++)
    {
        mpz_init_set(this->x[i], x[i]);
    }

    init();
}

void LGLR::init()
{
    // TODO: main function here
}

void LGLR::qm(mpz_t &res, mpz_t a, mpz_t b)
{
    mpz_init_set_si(res, 1);
    mpz_t aa;
    mpz_init_set(aa, a);
    mpz_t bb;
    mpz_init_set(bb, b);
    while (mpz_cmp_si(b, 0) != 0)
    {
        if (mpz_odd_p(b))
        {
            mpz_mul(res, res, a);
            mpz_mod(res, res, p);
        }
        mpz_mul(a, a, a);
        mpz_mod(a, a, p);
        mpz_fdiv_q_2exp(b, b, 1);
    }

    mpz_clear(aa);
    mpz_clear(bb);
}

