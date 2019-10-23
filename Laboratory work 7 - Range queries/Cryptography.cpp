#include <stdio.h>
using namespace std;
 
int mod, n;
 
struct mat {
    int c0, c1, c2, c3;
};
 
const mat E = { 1, 0, 0, 1 };
 
inline mat mult(const mat &a, const mat &b) {
    mat res;
    res.c0 = (a.c0 * b.c0 + a.c1 * b.c2) % mod;
    res.c1 = (a.c0 * b.c1 + a.c1 * b.c3) % mod;
    res.c2 = (a.c2 * b.c0 + a.c3 * b.c2) % mod;
    res.c3 = (a.c2 * b.c1 + a.c3 * b.c3) % mod;
    return res;
}
 
const int MAXN = 262150;
 
mat st[2 * MAXN];
 
inline mat get(int l, int r) {
    mat resl = E, resr = E;
    int nl = n + l - 1, nr = n + r - 1;
    while (nl < nr) {
        if (nl % 2 == 1) {
            resl = mult(resl, st[nl]);
            nl++;
        }
        nl /= 2;
        if (nr % 2 == 0) {
            resr = mult(st[nr], resr);
            nr--;
        }
        nr /= 2;
    }
    if (nl == nr)
        resl = mult(resl, st[nl]);
    return mult(resl, resr);
}
 
int main() {
    scanf("%d", &mod);
    int q, l, r;
 
    scanf("%d%d", &n, &q);
 
    int cc = 1;
    while (cc < n)
        cc <<= 1;
 
    for (int i = 0; i < MAXN; i++)
        st[i] = E;
 
    for (int i = cc; i < cc + n; i++)
        scanf("%d%d%d%d", &st[i].c0, &st[i].c1, &st[i].c2, &st[i].c3);
 
    for (int i = cc - 1; i >= 1; i--)
        st[i] = mult(st[(i << 1)], st[(i << 1) + 1]);
    n = cc;
 
    mat res;
    while (q--) {
        scanf("%d%d", &l, &r);
        res = get(l, r);
        printf("%d %d\n%d %d\n\n", res.c0, res.c1, res.c2, res.c3);
    }
 
    return 0;
}
