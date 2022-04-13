#include "thres_Elgamal.h"
using namespace std;

void thres_Elgamal::sample()
{
    int num = 3;
    vector<mpz_t> ti(num);
    Elgamal el;
    elg_pk pk = el.get_elg_pk();
    elg_sk sk = el.get_elg_sk();

    mpz_t t;
    mpz_init_set(t, sk.t);

    // initialize the random seed
    gmp_randstate_t grt;
    gmp_randinit_default(grt);
    gmp_randseed_ui(grt, clock_t());

    // get the fragments of t
    int frag_len = el.get_MESSAGE_SPACE() - 10;
    mpz_t last;
    mpz_init(last);
    for (int i = 0; i < num - 1; i++)
    {
        mpz_t temp;
        mpz_init(temp);
        mpz_urandomb(temp, grt, frag_len);
        mpz_init_set(ti[i], temp);
        mpz_add(last, last, temp);
    }
    mpz_sub(last, t, last);
    mpz_init_set(ti[num - 1], last);

    // define the message m, get the ciphertext c1 and c2
    mpz_t m, c1, c2, p;
    mpz_inits(m, c1, c2, p, NULL);

    mpz_set_si(m, 10086);
    mpz_set(p, pk.p);

    el.elg_enc(c1, c2, m, pk);

    // get everyone's fragment
    vector<mpz_t> frag(num);
    for (int i = 0; i < num; i++)
    {
        mpz_init(frag[i]);
        mpz_powm(frag[i], c1, ti[i], p);
    }

    // get the product of all fragment
    mpz_t prod;
    mpz_init_set_si(prod, 1);
    for (int i = 0; i < num; i++)
    {
        mpz_mul(prod, prod, frag[i]);
        mpz_mod(prod, prod, p);
    }

    // decrypt the ciphertext
    mpz_t temp;
    mpz_init(temp);
    mpz_invert(temp, prod, p);
    mpz_mul(temp, temp, c2);
    mpz_mod(temp, temp, p);
    gmp_printf("the message is %Zd\n\n", temp);
}