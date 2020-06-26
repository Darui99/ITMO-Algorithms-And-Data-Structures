#include <bits/stdc++.h>
using namespace std;

typedef unsigned int uint;

const int MAXN = 31700;

bitset<MAXN> sieve;
uint prime[MAXN];
uint sqrp[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
    uint n, x, g, res = 0;
	cin >> n >> x;

	g = (uint)sqrt(n) + 1;
	uint cnt = 0;
	sieve.flip();
	for (uint i = 2; i < g; i++) {
		if (sieve[i]) {
			res = res * x + i;
			prime[cnt++] = i;
			sqrp[cnt - 1] = i * i;
			for (uint j = i * i; j < g; j += i)
				sieve[j] = false;
		}
	}

	uint s = 0, f = g;
	for (uint i = 1; i <= g; i++) {
		sieve.reset();
		s += g; f += g;
		for (uint t = 0; t < cnt; t++) {
			uint j = prime[t];
			if (sqrp[t] >= f)
				break;
			uint b;
			if (sqrp[t] < s) {
				uint k = s % j;
				if (k == 0) {
					b = 0;
				} else {
					b = j - k;
				}
			} else {
				b = sqrp[t] - s;
			}
			for (uint z = b; z < g; z += j)
				sieve[z] = true;
		}
		for (uint t = 0; t < g; t++) {
			if (!sieve[t]) {
				uint j = s + t;
				if (j > n) {
					cout << res;
					return 0;
				}
				res = res * x + j;
			}
		}
	}
	cout << res;
	return 0;
}
