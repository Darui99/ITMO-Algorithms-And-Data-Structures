#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll inf = (ll)4e+18;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, s, f;
	cin >> n >> s >> f;
	s--; f--;

	vector < vector<ll> > g(n);
	for (int i = 0; i < n; i++) {
		g[i].resize(n);
		for (int j = 0; j < n; j++) {
			cin >> g[i][j];
		}
	}

	vector <ll> d(n, inf);
	vector <bool> used(n);
	d[s] = 0;
	for (int i = 0; i < n; i++) {
		ll minu = inf;
		int iminu = -1;
		for (int j = 0; j < n; j++) {
			if (!used[j] && d[j] < minu) {
				minu = d[j];
				iminu = j;
			}
		}
		if (iminu == -1)
			break;
		used[iminu] = true;
		for (int j = 0; j < n; j++) {
			if (g[iminu][j] != -1)
				d[j] = min(d[j], d[iminu] + g[iminu][j]);
		}
	}
	if (d[f] == inf) {
	    cout << -1;
	} else {
	    cout << d[f];
	}

	return 0;
}
