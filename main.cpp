#include "Client.h"
#include "Server.h"
using namespace std;

int main()
{
    // initialize the Client and get Client's encrypted coefficient
    int kc = 3;

    int x[] = {4, 2, 3};

    vector<mpz_t> xx(3);
    for (int i = 0; i < kc; i++)
    {
        mpz_init_set_si(xx[i], x[i]);
    }

    Client client(xx);

    // the module
    mpz_t p;
    mpz_init_set(p, client.elgamal.pk.p);

    vector<mpz_t> enc_co_1(kc + 1);
    vector<mpz_t> enc_co_2(kc + 1);

    client.get_enc_co(enc_co_1, enc_co_2);

    // initialize the Server
    int ks = 5;

    int y[] = {1, 2, 4, 7, 9};

    vector<mpz_t> yy(ks);
    for (int i = 0; i < ks; i++)
    {
        mpz_init_set_si(yy[i], y[i]);
    }

    Server server(yy, client.elgamal.sk.t, p);

    vector<mpz_t> res(ks);
    server.get_enc_data(res, enc_co_2);

    for (int i = 0; i < ks; i++)
    {
        gmp_printf("%Zd\n\n", res[i]);
    }

    return 0;
}
