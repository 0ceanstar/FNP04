#include "Client.h"
#include "Server.h"
using namespace std;
const int N = 3;
const int SIZE = 10;

// int main()
// {
//     // initialize Elgamal protocol
//     Elgamal elgamal;
//     elg_pk PK = elgamal.pk;
//     elg_sk SK = elgamal.sk;
//     // TODO:get the fragment of elgamal secret key

//     // initialize P1
//     int temp[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//     vector<mpz_t> m(SIZE);
//     for (int i = 0; i < SIZE; i++)
//     {
//         mpz_init_set_si(m[i], temp[i]);
//     }
//     Client P1(m, PK.p);

//     // TODO: initialize P2~PN

//     // TODO: P1 generate the polynomial

//     // TODO: use Elgamal public key to encrypt coefficient

//     // TODO: P2~PN
//     return 0;
// }

int main()
{
    Elgamal elgamal;
    elg_pk PK = elgamal.pk;
    elg_sk SK = elgamal.sk;

    int temp[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<mpz_t> m(SIZE);
    for (int i = 0; i < SIZE; i++)
    {
        mpz_init_set_si(m[i], temp[i]);
    }
    Client P1(m, PK.p);

    mpz_t enc_co_1;
    vector<mpz_t> enc_co_2(SIZE + 1);
    P1.get_enc_co(enc_co_1, enc_co_2, PK, m[0]);

    return 0;
}