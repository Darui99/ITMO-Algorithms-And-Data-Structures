#include <bits/stdc++.h>
using namespace std;

const int inf = (int)1e+6 + 3;
const int MAXN = 305;

int n;
int mat[MAXN][MAXN], match[MAXN];
bool used[MAXN];

bool dfs(int v, int lock) {
	if (used[v])
		return false;
	used[v] = true;
	for (int i = 0; i < n; i++) {
		if (mat[v][i] < lock)
			continue;
		if (match[i] == -1 || dfs(match[i], lock)) {
			match[i] = v;
			return true;
		}
	}
	return false;
}

inline int kuhn(int n, int lock) {
	for (int i = 0; i < n; i++)
		match[i] = -1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			used[j] = false;
		dfs(i, lock);
	}
	int res = 0;
	for (int i = 0; i < n; i++)
		res += (match[i] != -1);
	return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cin >> mat[i][j];
	}

	int l = 0, r = inf;
	while (r - l > 1) {
		int mid = (l + r) / 2;
		if (kuhn(n, mid) == n) {
			l = mid;
		} else {
			r = mid;
		}
	}
	cout << l;
    return 0;
}
