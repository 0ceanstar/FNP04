#include "Client.h"
#include "Server.h"
using namespace std;

int main()
{
    int x[] = {4, 2, 3};

    vector<mpz_t> xx(3);

    printf("the data is :\n");
    for (int i = 0; i < 3; i++)
    {
        mpz_init_set_si(xx[i], x[i]);
        gmp_printf("%Zd\t", xx[i]);
    }
    printf("\n");

    Client client(xx);

    return 0;
}