#include <bits/stdc++.h>
using namespace std;

const int MAXN = (int)1e+6 + 3;

int first[MAXN];
bool sieve[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
    for (int i = 2; i < MAXN; i++) {
		sieve[i] = true;
		first[i] = MAXN;
	}

	for (int i = 2; i < MAXN; i++) {
		if (sieve[i]) {
			first[i] = i;
			for (int k = i + i; k < MAXN; k += i) {
				sieve[k] = false;
				first[k] = min(first[k], i);
			}
		}
	}

	int t, x;
	cin >> t;

	while (t--) {
		cin >> x;
		while (x > 1) {
			cout << first[x] << ' ';
			x /= first[x];
		}
		cout << '\n';
	}
	return 0;
}
