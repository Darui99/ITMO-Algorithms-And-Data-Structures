#include <bits/stdc++.h>
using namespace std;

const int alph = 26;

int main() {
    freopen("radixsort.in", "r", stdin);
    freopen("radixsort.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, m, k;
	cin >> n >> m >> k;

	vector <string> arr(n);
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	vector <int> p(n), h(alph), pn(n), cnt(alph);

	for (int i = 0; i < n; i++) {
		cnt[arr[i].back() - 'a']++;
	}

	for (int i = 0; i < n; i++)
		p[i] = i;

	for (int i = 1; i < alph; i++)
		h[i] = h[i - 1] + cnt[i - 1];

	for (int i = m - 1, step = 0; step < k; i--, step++) {
		for (int j = 0; j < alph; j++)
			cnt[j] = 0;
		for (int j = 0; j < n; j++)
			cnt[arr[j][i] - 'a']++;
		h[0] = 0;
		for (int j = 1; j < alph; j++)
			h[j] = h[j - 1] + cnt[j - 1];

		for (int j = 0; j < n; j++) {
			int v = h[arr[p[j]][i] - 'a'];
			h[arr[p[j]][i] - 'a']++;
			pn[v] = p[j];
		}
		p.swap(pn);
	}

	for (int i = 0; i < n; i++)
		cout << arr[p[i]] << '\n';

	return 0;
}
