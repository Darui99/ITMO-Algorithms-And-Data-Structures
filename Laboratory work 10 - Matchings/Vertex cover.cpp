#include <bits/stdc++.h>
using namespace std;

vector < vector<int> > g;
vector <int> match, L, R, cover;
vector <bool> used;

void dfs0(int v) {
	L[v] = true;
	for (int i = 0; i < (int)g[v].size(); i++) {
		int to = g[v][i];
		R[to] = true;
		if (match[to] != -1 && !L[match[to]])
			dfs0(match[to]);
	}
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, k, a;
	cin >> n >> m;

	g.resize(n);
	used.resize(n);
	cover.resize(n);
	L.resize(n);
	R.resize(m);
	match.resize(m, -1);

	for (int i = 0; i < n; i++) {
		cin >> k;
		while (k--) {
			cin >> a;
			g[i].push_back(a - 1);
		}
	}

	for (int i = 0; i < n; i++) {
		cin >> a;
		if (a != 0)
			match[a - 1] = i;
	}

	for (int i = 0; i < m; i++) {
		if (match[i] != -1)
			cover[match[i]] = true;
	}

	for (int i = 0; i < n; i++) {
		if (!cover[i])
			dfs0(i);
	}

	vector <int> ansl, ansr;
	for (int i = 0; i < n; i++) {
		if (!L[i])
			ansl.push_back(i);
	}
	for (int i = 0; i < m; i++) {
		if (R[i])
			ansr.push_back(i);
	}

	cout << (int)ansl.size() + (int)ansr.size() << '\n';
	cout << (int)ansl.size() << " ";
	for (int i = 0; i < (int)ansl.size(); i++)
		cout << ansl[i] + 1 << " ";
	cout << '\n';
	cout << (int)ansr.size() << " ";
	for (int i = 0; i < (int)ansr.size(); i++)
		cout << ansr[i] + 1 << " ";
    return 0;
}
