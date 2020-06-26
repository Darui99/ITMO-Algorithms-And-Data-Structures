#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = (int)2e+7 + 3;

bitset<MAXN> sieve;

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
    sieve.flip();

	for (ll i = 2ll; i < (ll)MAXN; i++) {
		if (sieve[(int)i]) {
			for (ll k = i * i; k < (ll)MAXN; k += i)
				sieve[(int)k] = false;
		}
	}

	int t, x;
	cin >> t;

	while (t--) {
		cin >> x;
		if (sieve[x]) {
			cout << "YES\n";
		} else {
			cout << "NO\n";
		}
	}
	return 0;
}
