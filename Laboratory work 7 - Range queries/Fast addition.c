#include <stdio.h>
typedef unsigned int uint;

#define MAXN (1 << 24) + 5

uint arr[MAXN], A, B, m, q, CUR = 0, l, r, add, t;

int main() {
    scanf("%u%u%u%u", &m, &q, &A, &B);

    while(m--) {
        CUR = CUR * A + B;
        add = CUR >> 8;
        CUR = CUR * A + B;
        l = CUR >> 8;
        CUR = CUR * A + B;
        r = CUR >> 8;
        if (l > r) {
            t = r;
            r = l;
            l = t;
        }
        arr[l] += add;
        arr[r + 1] -= add;
    }

    uint sum = arr[0];
    for (int i = 1; i < MAXN; i++) {
        sum += arr[i];
        arr[i] = arr[i - 1] + sum;
    }

    sum = 0;
    while(q--) {
        CUR = CUR * A + B;
        l = CUR >> 8;
        CUR = CUR * A + B;
        r = CUR >> 8;
        if (l > r) {
            t = r;
            r = l;
            l = t;
        }
        sum += arr[r] - (l > 0 ? arr[l - 1] : 0);
    }

    printf("%u", sum);

    return 0;
}
