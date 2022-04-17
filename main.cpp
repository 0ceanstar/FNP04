#include "Client.h"
#include "Server.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int N = 4;    // the number of P2~PN
const int SIZE = 3; // every party has the same size of data

void execute()
{
    // initialize Elgamal protocol
    Elgamal elgamal;
    elg_pk PK = elgamal.pk;
    elg_sk SK = elgamal.sk;

    // get the fragment of elgamal secret key
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

    // initialize P2~PN
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

    // P1's ecrypted value
    vector<mpz_t> c(SIZE);
    for (int i = 0; i < SIZE; i++)
    {
        mpz_init_set_si(c[i], 0);
    }
    mpz_t deno;
    mpz_init_set_si(deno, 1);

    for (int i = 0; i < N; i++)
    {
        // P2~PN generate the polynomials respectively
        Client &cur = *P2N[i];
        mpz_t enc_co_1;
        vector<mpz_t> enc_co_2(SIZE + 1);
        mpz_t k;
        mpz_init(k);
        mpz_urandomb(k, grt, elgamal.MESSAGE_SPACE);

        // k must be constant value
        mpz_set_si(k, 10086);

        cur.get_enc_co(enc_co_1, enc_co_2, PK, k);

        mpz_t temp;
        mpz_init(temp);
        mpz_powm(temp, enc_co_1, s[i], PK.p);
        mpz_mul(deno, deno, temp);
        mpz_mod(deno, deno, PK.p);

        mpz_clear(temp);
        mpz_clear(k);

        // P1 use polynomials to calculate data
        vector<mpz_t> enc_data(SIZE);
        P1.get_enc_data(enc_data, enc_co_2);
        printf("enc_data is :");
        for (int j = 0; j < SIZE; j++)
        {
            gmp_printf("%Zd\t", enc_data[j]);
            mpz_add(c[j], c[j], enc_data[j]);
            mpz_mod(c[j], c[j], PK.p);
        }
        printf("\n");
    }
    printf("c is :");
    for (int i = 0; i < SIZE; i++)
    {
        gmp_printf("%Zd\t", c[i]);
    }
    printf("\n");

    // P1 get the result
    mpz_invert(deno, deno, PK.p);
    for (int i = 0; i < SIZE; i++)
    {
        mpz_mul(c[i], c[i], deno);
        mpz_mod(c[i], c[i], PK.p);
    }
    printf("the result is :");
    for (int i = 0; i < SIZE; i++)
    {
        gmp_printf("%Zd\t", c[i]);
    }
    printf("\n\n");
}

void write_file(string data, string file_path)
{
    ofstream outfile(file_path);
    if (!outfile.is_open())
    {
        cerr << "error" << endl;
    }
    outfile << data;
    outfile.close();
}

void gen_data()
{
    gmp_randstate_t grt;
    gmp_randinit_default(grt);
    gmp_randseed_ui(grt, clock());
    srand((unsigned)time(NULL));

    int num = 1 << 10;

    vector<int> idx;
    for (int i = 0; i < 64; i++)
    {
        idx.push_back(rand() % num);
    }
    sort(idx.begin(), idx.end());

    string data = "";

    int it = 0;
    for (int i = 0; i < num; i++)
    {
        if (idx[it] == i)
        {
            data += "123456\n";
            it++;
            continue;
        }
        mpz_t temp;
        mpz_init(temp);
        mpz_urandomb(temp, grt, 30);
        data += string(mpz_get_str(NULL, 10, temp));
        data += "\n";

        mpz_clear(temp);
    }

    write_file(data, "../data/Server.txt");
}

int main()
{
    gen_data();
    return 0;
}