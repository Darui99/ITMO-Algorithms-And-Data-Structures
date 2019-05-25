#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

mt19937 rng_58;
ll ps[5] = { 999917ll, 999953ll, 2000029ll, 2000039ll, 2000081ll };
ll mods[5] = { 961748941ll, 961748947ll, 961748969ll, 961748987ll, 961748993ll };

inline pair<ll, ll> operator+(const pair<ll, ll> &a, const pair<ll, ll> &b) {
	return make_pair(a.first + b.first, a.second + b.second);
}

inline pair<ll, ll> operator*(const pair<ll, ll> &a, const pair<ll, ll> &b) {
	return make_pair(a.first * b.first, a.second * b.second);
}

inline pair<ll, ll> operator%(const pair<ll, ll> &a, const pair<ll, ll> &b) {
	return make_pair(a.first % b.first, a.second % b.second);
}

pair <ll, ll> p, mod;

pair<ll, ll> getHash(const vector < pair<ll, ll> > &s) {
	pair<ll, ll> res = make_pair(0ll, 0ll);
	for (int i = 0; i < (int)s.size(); i++) {
		res = (res * p + s[i]) % mod;
	}
	return res;
}

vector < vector<int> > g;
vector <int> w;

void set_w(int v, int par) {
	w[v] = 1;
	for (int i = 0; i < (int)g[v].size(); i++) {
		int to = g[v][i];
		if (to == par)
			continue;
		set_w(to, v);
		w[v] += w[to];
	}
}

vector <int> intrver;

void findIntrVer(int v, int par) {
	for (int i = 0; i < (int)g[v].size(); i++) {
		int to = g[v][i];
		if (to != par)
			findIntrVer(to, v);
	}

	if ((int)g[v].size() == 2) {
		int curw[2];
		for (int i = 0; i < (int)g[v].size(); i++) {
			int to = g[v][i];
			if (to == par) {
				curw[i] = w[0] - w[v];
			} else {
				curw[i] = w[to];
			}
		}
		if (curw[0] == curw[1] && curw[0] + curw[1] + 1 == (int)g.size())
			intrver.push_back(v);
	}
}

vector < pair<ll, ll> > h;

void dfs(int v, int par, int root) {
	vector < pair<ll, ll> > sons;
	for (int i = 0; i < (int)g[v].size(); i++) {
		int to = g[v][i];
		if (to == par)
			continue;
		dfs(to, v, root);
		sons.push_back(h[to]);
	}

	if ((int)sons.size() == 0) {
		h[v] = p;
		return;
	}

	if (v == root) {
		if (h[g[v][0]] == h[g[v][1]]) {
			cout << "YES";
			exit(0);
		}
	} else {
		sort(sons.begin(), sons.end());
		h[v] = getHash(sons);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	p = make_pair(ps[rng_58() % 5], ps[rng_58() % 5]);
	mod = make_pair(mods[rng_58() % 5], mods[rng_58() % 5]);

	int n, a, b;
	cin >> n;

	g.resize(n);
	w.resize(n);
	h.resize(n);

	for (int i = 0; i < n - 1; i++) {
		cin >> a >> b;
		a--; b--;
		g[a].push_back(b);
		g[b].push_back(a);
	}

	set_w(0, 0);
	findIntrVer(0, 0);
	for (int i = 0; i < (int)intrver.size(); i++) {
		dfs(intrver[i], intrver[i], intrver[i]);
	}
	cout << "NO";
	return 0;
}
