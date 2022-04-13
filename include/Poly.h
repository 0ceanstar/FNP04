#pragma once
#include <iostream>
#include <gmp.h>
#include <vector>
#include <algorithm>

using namespace std;

class Poly
{
public:
    Poly(vector<mpz_t> &x);

    //计算多项式的系数
    //注意：这里的需要提前声明vector a的大小为 kc+1 否则可能造成错误
    void get_co(vector<mpz_t> &a);

    void get_co(vector<mpz_t> &a, const vector<mpz_t> &x);

    // set N to mod
    void set_mod(mpz_t &mod);

    // get mod number
    void get_mod(mpz_t &n);

    //验证多项式生成的正确性
    static void sample();

private:
    int kc; // the size of set x
    vector<mpz_t> x;
    mpz_t N; // the mod number
    void _get_co(vector<bool> &vis, int cur, int j, mpz_t &t);
};
