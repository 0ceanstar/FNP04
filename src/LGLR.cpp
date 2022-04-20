#include "LGLR.h"
using namespace std;

LGLR::LGLR(vector<mpz_t> &x, mpz_t p)
    : n(x.size() + 1), a(n), x(n + 1), c(n + 1), temp(n + 1), y(n + 1)
{
    mpz_init_set(this->p, p);

    mpz_t x1;
    mpz_init(x1);
    mpz_t y1;
    mpz_init(y1);

    gmp_randinit_default(grt);
    gmp_randseed_ui(grt, clock());

    do
    {
        // FIXME: to generate x1 and y1
    } while (0 != mpz_cmp_si(y1, 0));

    for (int i = 2; i <= n; i++)
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
    while (mpz_cmp_si(bb, 0) != 0)
    {
        if (mpz_odd_p(bb))
        {
            mpz_mul(res, res, aa);
            mpz_mod(res, res, p);
        }
        mpz_mul(aa, aa, aa);
        mpz_mod(aa, aa, p);
        mpz_fdiv_q_2exp(bb, bb, 1);
    }

    mpz_clear(aa);
    mpz_clear(bb);
}

void LGLR::sample()
{
}