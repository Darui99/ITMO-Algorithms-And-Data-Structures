#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <stdio.h>

#define S 65536
#define MAXN 100005

int n, t, v;
unsigned long long ans;
unsigned int arr[MAXN], cnt[S], h[S], p[MAXN], pn[MAXN], F[2][MAXN], a, b;

unsigned int cur = 0, A, B, now;

int main() {
	freopen("buckets.in", "r", stdin);
	freopen("buckets.out", "w", stdout);

	scanf("%d%d%lu%lu", &t, &n, &A, &B);

	while (t--) {
		for (int i = 0; i < n; i++) {
			cur = cur * A + B;
			a = cur >> 8;
			cur = cur * A + B;
			b = cur >> 8;
			arr[i] = (a << 8) ^ b;

			F[0][i] = arr[i] << 16 >> 16;
			F[1][i] = arr[i] >> 16;
		}

		ans = 0ll;

		for (int step = 0; step < 2; step++) {
			for (int i = 0; i < n; i++) {
				if (step == 0)
					p[i] = i;
				else
					p[i] = pn[i];
				now = F[step][p[i]];
				cnt[now]++;
			}

			h[0] = 0;
			for (int i = 1; i < S; i++) {
				h[i] = h[i - 1] + cnt[i - 1];
				cnt[i - 1] = 0;
			}
			cnt[S - 1] = 0;

			for (int i = 0; i < n; i++) {
				now = F[step][p[i]];
				v = h[now];
				h[now]++;
				if (step == 0)
					pn[v] = p[i];
				else
					ans += (v + 1ll) * arr[p[i]];
			}
		}
		printf("%llu\n", ans);
	}

	return 0;
}
