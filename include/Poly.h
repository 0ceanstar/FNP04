#pragma once
#include <iostream>
#include <gmp.h>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Poly
{
public:
    Poly(vector<mpz_t> &x, mpz_t p);

    /**
     * @brief 计算多项式的系数,注意：这里的需要提前声明vector a的大小为 kc+1 否则可能造成错误
     *
     *
     * @param a
     * @param mod p = 0 ---> recursion; p =1 ---> iteration
     */
    void get_co(vector<mpz_t> &a, int mod = 0);

    void get_co(vector<mpz_t> &a, const vector<mpz_t> &x);

    // set N to p
    void set_p(mpz_t &p);

    // get p number
    void get_p(mpz_t &n);

    //验证多项式生成的正确性
    static void sample();

private:
    int kc; // the size of set x
    vector<mpz_t> x;
    mpz_t p;
    void _get_co(vector<bool> &vis, int cur, int j, mpz_t &t);
};
