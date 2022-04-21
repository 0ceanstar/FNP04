#include "LGLR.h"
using namespace std;

LGLR::LGLR(vector<mpz_t> &x, mpz_t p)
    : n(x.size() + 1), a(n + 1), x(n + 1), b(n + 1), temp(n + 1), c(n + 1)
{
    mpz_init_set(this->p, p);
    for (int i = 0; i < n - 1; i++)
    {
        mpz_init_set(this->x[i + 2], x[i]);
    }

    mpz_t x1;
    mpz_init(x1);
    mpz_init(y1);

    gmp_randinit_default(grt);
    gmp_randseed_ui(grt, clock());

    mpz_t t;
    mpz_init(t);
    do
    {
        mpz_urandomm(x1, grt, p);
        mpz_init_set_si(y1, 1);

        for (int i = 2; i <= n; i++)
        {
            mpz_sub(t, x1, this->x[i]);
            mpz_mul(y1, y1, t);
            mpz_mod(y1, y1, p);
        }

    } while (0 == mpz_sgn(y1));

    mpz_init_set(this->x[1], x1);
    mpz_clear(t);
    mpz_clear(x1);

    // printf("x = ");
    // for (int i = 1; i <= n; i++)
    // {
    //     gmp_printf("%Zd\t", this->x[i]);
    // }
    // printf("\n\n");

    // gmp_printf("y1 = %Zd\n\n", y1);

    init();
}

LGLR::~LGLR()
{
    for (int i = 0; i < n + 1; i++)
    {
        mpz_clears(a[i], x[i], temp[i], b[i], c[i], NULL);
    }
    mpz_clear(y1);
    mpz_clear(p);
}

void LGLR::mul(vector<mpz_t> &f, int len, mpz_t& t)
{
    for (int i = len; i > 0; i--)
    {
        mpz_init_set(temp[i], f[i]);
        mpz_init_set(f[i], f[i - 1]);
    }
    mpz_init_set(temp[0], f[0]);
    mpz_init_set_si(f[0], 0);

    mpz_t q;
    mpz_init(q);
    for (int i = 0; i <= len; i++)
    {
        mpz_mul(q, temp[i], t);
        mpz_add(f[i], f[i], q);
        mpz_mod(f[i], f[i], p);
    }
    mpz_clear(q);
}

void LGLR::dev(std::vector<mpz_t> &f, std::vector<mpz_t> &r, mpz_t t)
{
    for (int i = 0; i <= n; i++)
    {
        mpz_init_set(temp[i], f[i]);
    }
    mpz_t q;
    mpz_init(q);
    for (int i = n; i > 0; i--)
    {
        mpz_init_set(r[i - 1], temp[i]);
        mpz_mul(q, t, temp[i]);
        mpz_sub(temp[i - 1], temp[i - 1], q);
        mpz_mod(temp[i - 1], temp[i - 1], p);
    }
    mpz_clear(q);
}

void LGLR::init()
{
    mpz_init_set_si(b[1], 1);
    mpz_init_set(b[0], x[1]);
    mpz_neg(b[0], b[0]);

    mpz_t t;
    mpz_init(t);
    for (int i = 2; i <= n; i++)
    {
        try
        {
            mpz_set(t, x[i]);
            mpz_neg(t, t);
            mul(b, i, t);
        }
        catch (const std::exception &e)
        {
            std::cout << "Caught exception \"" << e.what() << "\"\n";
        }
    }
    mpz_clear(t);

    mpz_t q;
    mpz_init(q);
    for (int i = 1; i <= n; i++)
    {
        mpz_t fz;
        mpz_init_set_si(fz, 1);
        for (int j = 1; j <= n; j++)
        {
            if (i == j)
            {
                continue;
            }
            mpz_sub(q, x[i], x[j]);
            mpz_mul(fz, fz, q);
            mpz_mod(fz, fz, p);
        }
        if (i == 1)
        {
            mpz_sub_ui(q, p, 2);
            mpz_powm(fz, fz, q, p);
            mpz_mul(fz, fz, y1);
        }
        else
        {
            mpz_set_si(fz, 0);
        }
        mpz_mod(fz, fz, p);
        mpz_init_set(q, x[i]);
        mpz_neg(q, q);
        dev(b, c, q);
        for (int j = 0; j < n; j++)
        {
            mpz_mul(q, fz, c[j]);
            mpz_add(a[j], a[j], q);
            mpz_mod(a[j], a[j], p);
        }
        mpz_clear(fz);
    }
    mpz_clear(q);
}
void LGLR::get_co(std::vector<mpz_t> &a)
{
    for (int i = 0; i < n; i++)
    {
        mpz_init_set(a[i], this->a[i]);
    }
}

void LGLR::sample()
{
    Elgamal el;
    mpz_t p;
    mpz_init_set(p, el.pk.p);

    int n = 3;
    vector<mpz_t> x(n);
    mpz_init_set_ui(x[0], 4);
    mpz_init_set_ui(x[1], 2);
    mpz_init_set_ui(x[2], 3);

    LGLR lglr(x, p);

    vector<mpz_t> a(4);

    lglr.get_co(a);

    printf("a = ");
    for (int i = 0; i < n; i++)
    {
        if (mpz_cmp_si(a[i], 1000) > 0)
        {
            mpz_sub(a[i], a[i], p);
        }

        gmp_printf("%Zd\t", a[i]);
    }
    printf("\n\n");
}