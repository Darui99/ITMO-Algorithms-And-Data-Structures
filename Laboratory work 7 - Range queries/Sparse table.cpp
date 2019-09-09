#include <bits/stdc++.h>
using namespace std;

const int LOGN = 17;
const int MAXN = (int)1e+5 + 5;

int pows[MAXN], arr[MAXN], d[LOGN][MAXN];

inline int get(int l, int r) {
	int cur_pow = pows[r - l + 1], cur_len = (1 << cur_pow);
	return min(d[cur_pow][l], d[cur_pow][r - cur_len + 1]);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	pows[1] = 0;
	for (int i = 2; i < MAXN; i++)
		pows[i] = pows[i / 2] + 1;

	int n, m;
	cin >> n >> m >> arr[0];

	for (int i = 1; i < n; i++)
		arr[i] = (arr[i - 1] * 23 + 21563) % 16714589;

	for (int i = 0; i < n; i++)
		d[0][i] = arr[i];

	int p = 1;
	for (int i = 1; i < LOGN; i++) {
		for (int j = 0; j + p < n; j++)
			d[i][j] = min(d[i - 1][j], d[i - 1][j + p]);
		p *= 2;
	}

	int l = 0, r = 0, ans = 0;
	for (int i = 0; i < m; i++) {
		if (i == 0) {
			cin >> l >> r;
		} else {
			l = (17 * l + 751 + ans + 2 * i) % n + 1;
			r = (13 * r + 593 + ans + 5 * i) % n + 1;
		}
		ans = get(min(l, r) - 1, max(l, r) - 1);
	}

	cout << l << " " << r << " " << ans;

	return 0;
}
