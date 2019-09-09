#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int LOGN = 7;
const int MAXN = 130;
const ll mod = (ll)1e+9 + 7ll;

int pows[MAXN], arr[MAXN][MAXN][4], d[LOGN][LOGN][MAXN][MAXN][4];

function <int(int, int)> f[2];

int n, m, q;

inline void build() {
	for (int i = 2; i < MAXN; i++)
		pows[i] = pows[i / 2] + 1;

	f[0] = [](int a, int b) { return min(a, b); };
	f[1] = [](int a, int b) { return max(a, b); };

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int t = 0; t < 4; t++)
				d[0][0][i][j][t] = arr[i][j][t];
		}
	}

	for (int j = 1; j < LOGN; j++) {
		for (int x = 0; x < n; x++) {
			for (int y = 0; y + (1 << (j - 1)) < m; y++) {
				for (int t = 0; t < 4; t++) {
					d[0][j][x][y][t] = f[t < 2](d[0][j - 1][x][y][t], d[0][j - 1][x][y + (1 << (j - 1))][t]);
				}
			}
		}
	}

	for (int i = 1; i < LOGN; i++) {
		for (int j = 0; j < LOGN; j++) {
			for (int x = 0; x + (1 << (i - 1)) < n; x++) {
				for (int y = 0; y < m; y++) {
					for (int t = 0; t < 4; t++) {
						d[i][j][x][y][t] = f[t < 2](d[i - 1][j][x][y][t], d[i - 1][j][x + (1 << (i - 1))][y][t]);
					}
				}
			}
		}
	}
}

inline int get(int xl, int yl, int xr, int yr, int t) {
	int cpx = pows[xr - xl + 1], clx = (1 << cpx);
	int cpy = pows[yr - yl + 1], cly = (1 << cpy);
	int F = f[t < 2](d[cpx][cpy][xl][yl][t], d[cpx][cpy][xr - clx + 1][yl][t]);
	int S = f[t < 2](d[cpx][cpy][xl][yr - cly + 1][t], d[cpx][cpy][xr - clx + 1][yr - cly + 1][t]);
	return f[t < 2](F, S);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int t = 0; t < 4; t++)
				cin >> arr[i][j][t];
			if (arr[i][j][0] > arr[i][j][2])
				swap(arr[i][j][0], arr[i][j][2]);
			if (arr[i][j][1] > arr[i][j][3])
				swap(arr[i][j][1], arr[i][j][3]);
		}
	}

	build();

	ll A, B, sum = 0ll;
	cin >> q;
	vector <ll> v(q * 4 + 1);
	cin >> A >> B >> v[0];

	for (int i = 1; i < (int)v.size(); i++)
		v[i] = (A * v[i - 1] + B) % mod;

	for (int i = 0; i < q; i++) {
		int xl, yl, xr, yr;
		xl = (int)v[i * 4 + 1] % n; yl = (int)v[i * 4 + 2] % m;
		xr = (int)v[i * 4 + 3] % n; yr = (int)v[i * 4 + 4] % m;
		if (xl > xr)
			swap(xl, xr);
		if (yl > yr)
			swap(yl, yr);
		int ans[4];
		for (int t = 0; t < 4; t++)
			ans[t] = get(xl, yl, xr, yr, t);
		if (ans[0] > ans[2] || ans[1] > ans[3])
			continue;
		sum = (sum + (ll)(ans[2] - ans[0]) * (ll)(ans[3] - ans[1]) % mod) % mod;
	}
	cout << sum;

	return 0;
}
