#include "Client.h"
#include "Server.h"
using namespace std;
const int N = 3;    // the number of P2~PN
const int SIZE = 3; // every party has the same size of data

int main()
{
    // initialize Elgamal protocol
    Elgamal elgamal;
    elg_pk PK = elgamal.pk;
    elg_sk SK = elgamal.sk;

    // TODO: get the fragment of elgamal secret key
    gmp_randstate_t grt;
    gmp_randinit_default(grt);
    gmp_randseed_ui(grt, clock());
    vector<mpz_t> s(N);

    mpz_t cnt;
    mpz_init(cnt);
    for (int i = 1; i < N; i++)
    {
        mpz_init(s[i]);
        mpz_urandomb(s[i], grt, elgamal.MESSAGE_SPACE - 10);
        mpz_add(cnt, cnt, s[i]);
    }
    mpz_init(s[0]);
    mpz_sub(s[0], SK.s, cnt);

    // initialize P1
    int temp[SIZE] = {4, 2, 3};
    vector<mpz_t> m(SIZE);
    for (int i = 0; i < SIZE; i++)
    {
        mpz_init_set_si(m[i], temp[i]);
    }
    Server P1(m, PK.p);

    // TODO: initialize P2~PN
    vector<Client *> P2N;

    mpz_t MAX;
    mpz_init_set_si(MAX, 10);

    printf("P2N's data is :\n");
    for (int i = 0; i < N; i++)
    {
        vector<mpz_t> y(SIZE);
        for (int j = 0; j < SIZE; j++)
        {
            mpz_init(y[j]);
            mpz_urandomm(y[j], grt, MAX);
            gmp_printf("%Zd\t", y[j]);
        }
        printf("\n");
        P2N.push_back(new Client(y, PK.p));
    }

    for (int i = 0; i < N; i++)
    {
        // TODO: P2~PN generate the polynomials respectively
        Client &cur = *P2N[i];
        mpz_t enc_co_1;
        vector<mpz_t> enc_co_2(SIZE + 1);
        mpz_t k;
        mpz_init(k);
        mpz_urandomb(k, grt, elgamal.MESSAGE_SPACE);

        cur.get_enc_co(enc_co_1, enc_co_2, PK, k);

        mpz_clear(k);

        // TODO: P1 use polynomials to calculate data
    }

    // TODO: P1 get the result
    return 0;
}