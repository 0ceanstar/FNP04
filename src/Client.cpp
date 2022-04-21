#include "Client.h"

Client::Client(std::vector<mpz_t> &x, mpz_t &p) : kc(x.size()), x(kc), a(kc + 1)
{
    mpz_init_set(this->p, p);
    init(x);
}
Client::Client()
{
}

Client::~Client()
{
    for (int i = 0; i < kc; i++)
    {
        mpz_clear(x[i]);
        mpz_clear(a[i]);
    }
    mpz_clear(a[kc]);
}

void Client::init(vector<mpz_t> &x)
{
    for (int i = 0; i < kc; i++)
    {
        mpz_init_set(this->x[i], x[i]);
    }
}

void Client::get_co()
{
    Poly poly(this->x, p);
    if (kc < 30)
        poly.get_co(a);
    else
        poly.get_co(a, 1);
}

void Client::show_co()
{
    printf("The coefficient is:\n\n");
    for (int i = 0; i < kc + 1; i++)
    {
        gmp_printf("%Zd\n\n", a[i]);
    }
}

void Client::get_enc_co(mpz_t &enc_co_1,
                        std::vector<mpz_t> &enc_co_2,
                        elg_pk pk,
                        mpz_t k)
{
    for (int i = 0; i < a.size(); i++)
    {
        printf("i = %d\n", i);
        Elgamal::elg_enc(enc_co_1, enc_co_2[i], a[i], pk, k);
    }
}

void Client::set_data(vector<mpz_t> &x)
{
    kc = x.size();
    init(x);
}

void Client::set_p(mpz_t &p)
{
    mpz_init_set(this->p, p);
}

void Client::sample()
{
    ifstream infile("../data/num5/Client1.txt");
    assert(infile.is_open());
    string line = "";
    vector<mpz_t> data(16);
    int k = 0;
    while (k < 16 && getline(infile, line))
    {
        mpz_init_set_str(data[k++], line.c_str(), 10);
    }
    mpz_t p;
    Elgamal el;
    mpz_init_set(p, el.pk.p);
    Client client(data, p);

    client.get_co();

    client.show_co();

    infile.close();
}