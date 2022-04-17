#include "Poly.h"
void Poly::_get_co(vector<bool> &vis, int cur, int j, mpz_t &t)
{
    //该函数采用递归进行，cur为当前的层数
    // t用于存放结果
    static int cnt = 0; //统计当前的1的数量，如果已经达到j则返回
    if (cnt == j)
    {
        mpz_t pro;
        mpz_init_set_ui(pro, 1);
        //只有在0-cur这个区间vis才有可能被赋值为1
        for (int i = 0; i < cur; i++)
        {
            if (!vis[i])
            {
                mpz_mul(pro, pro, x[i]);
                mpz_mod(pro, pro, p);
            }
        }
        //将剩下的直接相乘
        for (int i = cur; i < kc; i++)
        {
            mpz_mul(pro, pro, x[i]);
            mpz_mod(pro, pro, p);
        }
        mpz_add(t, t, pro);
        mpz_mod(t, t, p);
        return;
    }
    if (cur == kc)
        return;

    //尝试写入1
    vis[cur] = 1;
    cnt++;
    _get_co(vis, cur + 1, j, t);
    //回溯
    vis[cur] = 0;
    cnt--;
    _get_co(vis, cur + 1, j, t);
}

Poly::Poly(vector<mpz_t> &x, mpz_t mod) : kc(x.size()), x(kc)
{
    mpz_init_set(p, mod); //默认的模数，这里是随便设置的
    for (int i = 0; i < kc; i++)
    {
        mpz_init_set(this->x[i], x[i]);
    }
}

void Poly::get_co(vector<mpz_t> &a, int mod)
{
    if (mod == 0) // recursion
    {
        //遍历计算每个系数，a0需要单独计算
        // a0等于所有x的累积
        mpz_init_set_ui(a[0], 1);
        for (int i = 0; i < kc; i++)
        {
            mpz_mul(a[0], a[0], x[i]);
        }
        //对于每一项系数aj，从kc个数里面选出j个，然后累乘剩余所有的项，得到Cjkc个数字，累加它们得到aj的绝对值，
        // aj的符号，从a0开始，a0为正，a1为负，a2为正......
        bool flag = 1;        // flag=1为负，第一项是a1，所以为负
        vector<bool> vis(kc); // vis为1则该项不参与此轮计算
        for (int j = 1; j <= kc; j++)
        {
            mpz_t &cur = a[j];
            mpz_init_set_ui(cur, 0);
            fill(vis.begin(), vis.end(), false);
            _get_co(vis, 0, j, cur);
            if (flag)
            {
                mpz_neg(cur, cur);
            }
            flag = !flag;
        }
        return;
    }

    // TODO: implement the iteration method
    mpz_init_set_ui(a[0], 1);
    for (int i = 0; i < kc; i++)
    {
        mpz_mul(a[0], a[0], x[i]);
    }
}

void Poly::get_co(vector<mpz_t> &a, const vector<mpz_t> &x)
{
    //遍历计算每个系数，a0需要单独计算
    // a0等于所有x的累积
    mpz_init_set_ui(a[0], 1);
    for (int i = 0; i < kc; i++)
    {
        mpz_mul(a[0], a[0], x[i]);
    }
    //对于每一项系数aj，从kc个数里面选出j个，然后累乘剩余所有的项，得到Cjkc个数字，累加它们得到aj的绝对值，
    // aj的符号，从a0开始，a0为正，a1为负，a2为正......
    bool flag = 1;        // flag=1为负，第一项是a1，所以为负
    vector<bool> vis(kc); // vis为1则该项不参与此轮计算
    for (int j = 1; j <= kc; j++)
    {
        mpz_t &cur = a[j];
        mpz_init_set_ui(cur, 0);
        fill(vis.begin(), vis.end(), false);
        _get_co(vis, 0, j, cur);
        if (flag)
        {
            mpz_neg(cur, cur);
        }
        flag = !flag;
    }
}

void Poly::sample()
{
    vector<int> x = {4, 2, 3};
    int kc = x.size();
    printf("x为：");
    for (int i = 0; i < kc; i++)
    {
        printf("%d  ", x[i]);
    }
    printf("\n\n");
    vector<mpz_t> xx(kc);
    for (int i = 0; i < kc; i++)
    {
        mpz_t &cur = xx[i];
        mpz_init_set_si(cur, x[i]);
    }

    mpz_t mod;
    mpz_init_set_ui(mod, 51215902124);

    Poly P(xx, mod);
    vector<bool> vis(kc);
    vector<mpz_t> co(kc + 1);
    P.get_co(co);
    for (int i = 0; i < kc + 1; i++)
    {
        gmp_printf("co[%d] = %Zd\n\n", i, co[i]);
    }
}

void Poly::set_p(mpz_t &mod)
{
    mpz_init_set(p, mod);
}

void Poly::get_p(mpz_t &mod)
{
    mpz_init_set(mod, this->p);
}