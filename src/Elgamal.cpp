#include "Elgamal.h"
using namespace std;

Elgamal::Elgamal()
{

    gmp_randinit_default(grt);
    gmp_randseed_ui(grt, clock());

    mpz_init(_k);
    mpz_urandomb(_k, grt, MESSAGE_SPACE / 2);

    mpz_t q, p, g, g1, g2, x_a, y_a; // define the variables

    mpz_init(q);
    mpz_urandomb(q, grt, MESSAGE_SPACE);
    mpz_inits(p, g, g1, g2, x_a, y_a, NULL);

    mpz_add(p, q, q); // calculate p=2*q+1
    mpz_add_ui(p, p, 1);
    while (mpz_probab_prime_p(p, 30) ==
           0) // loop to find q which is not a non-prime
    {
        mpz_nextprime(q, q);
        mpz_add(p, q, q); // calculate p=2*q+1 again
        mpz_add_ui(p, p, 1);
    }
    mpz_urandomm(g, grt, p);
    mpz_powm_ui(g1, g, 2, p); // calculate g^2modp
    mpz_powm(g2, g, q, p);    // calculate g^pmodp
    while (g == 0 || mpz_cmp_ui(g1, 1) == 0 ||
           mpz_cmp_ui(g2, 1) == 0) // Lagrange 定理,
    {
        mpz_urandomm(g, grt, p);
        mpz_powm_ui(g1, g, 2, p); // calculate g^2 mod p
        mpz_powm(g2, g, q, p);    // calculate g^p mod p
    }
    mpz_urandomm(x_a, grt, p); // generate the x_a
    mpz_powm(y_a, g, x_a, p);  // generate the y_a

    mpz_init_set(pk.p, p);
    mpz_init_set(pk.a, g);
    mpz_init_set(pk.b, y_a);

    mpz_init_set(sk.t, x_a);
    mpz_init_set(sk.p, p);
    mpz_init_set(sk.a, g);
    mpz_init_set(sk.b, y_a);
}

void Elgamal::elg_enc(mpz_t &c1,
                      mpz_t &c2,
                      mpz_t m,
                      elg_pk pk,
                      bool is_random)
{

    mpz_t k;
    mpz_init(k);
    mpz_urandomm(k, grt, pk.p);

    if (!is_random)
    {
        mpz_set(k, _k);
    }

    mpz_inits(c1, c2, NULL);

    mpz_t temp;
    mpz_init(temp);
    mpz_powm(temp, pk.b, k, pk.p);
    mpz_powm(c1, pk.a, k, pk.p); // c1=a^k mod p
    mpz_mul(c2, temp, m);        // c2=m*(b^k) mod p
    mpz_mod(c2, c2, pk.p);

    mpz_clear(k);
}

void Elgamal::elg_dec(mpz_t &m,
                      mpz_t c1,
                      mpz_t c2,
                      elg_sk sk)
{
    mpz_t temp;
    mpz_init(temp);
    mpz_powm(temp, c1, sk.t, sk.p);
    mpz_invert(temp, temp, sk.p);

    mpz_mul(temp, temp, c2);
    mpz_mod(temp, temp, sk.p);

    mpz_init_set(m, temp);
}

void Elgamal::sample()
{
    Elgamal E;

    elg_pk pk = E.get_elg_pk();
    elg_sk sk = E.get_elg_sk();

    char *m_ch = "3";
    mpz_t m;
    mpz_init_set_str(m, m_ch, 10);
    gmp_printf("m = %Zd\n\n", m);

    mpz_t c1, c2;
    mpz_inits(c1, c2, NULL);

    E.elg_enc(c1, c2, m, pk, true);

    gmp_printf("c1 = %Zd\n\n", c1);
    gmp_printf("c2 = %Zd\n\n", c2);

    E.elg_dec(m, c1, c2, sk);
    gmp_printf("recover m = %Zd\n\n", m);
}

void Elgamal::sample_1()
{
    const char *start = "10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";

    mpz_t q, p, g, g1, g2, x_a, y_a, k, k_c, c1, c2, m; // define the variables
    gmp_randstate_t state;
    mpz_init_set_str(q, start, 10); // init the variables
    mpz_inits(p, g, g1, g2, x_a, y_a, k, k_c, c1, c2, m, NULL);
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, (unsigned int)(time(NULL)));
    mpz_add(p, q, q); // calculate p=2*q+1
    mpz_add_ui(p, p, 1);
    while (mpz_probab_prime_p(p, 30) == 0) // loop to find q which is not a non-prime
    {
        mpz_nextprime(q, q);
        mpz_add(p, q, q); // calculate p=2*q+1 again
        mpz_add_ui(p, p, 1);
    }
    mpz_urandomm(g, state, p);
    mpz_powm_ui(g1, g, 2, p);                                          // calculate g^2modp
    mpz_powm(g2, g, q, p);                                             // calculate g^pmodp
    while (g == 0 || mpz_cmp_ui(g1, 1) == 0 || mpz_cmp_ui(g2, 1) == 0) // Lagrange 定理,
    {
        mpz_urandomm(g, state, p);
        mpz_powm_ui(g1, g, 2, p); // calculate g^2modp
        mpz_powm(g2, g, q, p);    // calculate g^pmodpf
    }

    mpz_urandomm(x_a, state, p); // generate the x_a
    mpz_powm(y_a, g, x_a, p);    // generate the y_a
    // encryption
    mpz_urandomm(m, state, p); // generate the plaintext
    mpz_init_set_si(m, 3);

    gmp_printf("The plaintext is:%Zd\n", m);
    mpz_urandomm(k, state, p);
    mpz_powm(k_c, y_a, k, p); // K=(Y_A)^k%p
    mpz_powm(c1, g, k, p);    // c1=g^k%p
    mpz_mul(c2, k_c, m);      // c2=k*m%p
    mpz_mod(c2, c2, p);
    gmp_printf("The pair of ciphertext is:\n(%Zd\n,%Zd)\n", c1, c2);
    // decrytion
    mpz_powm(k_c, c1, x_a, p); // K=(c1)^x_a%p
    mpz_invert(k_c, k_c, p);   // find the inverse of the K
    mpz_mul(c2, c2, k_c);      // m=c2*k^-1%p
    mpz_mod(c2, c2, p);
    gmp_printf("The plaintext after decrption is:%Zd\n", c2);
    mpz_clears(q, p, g, g1, g2, x_a, y_a, k, k_c, c1, c2, m, NULL); // free the memories
}