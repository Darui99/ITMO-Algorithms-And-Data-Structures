#include <bits/stdc++.h>
using namespace std;

const int alph = 26;
const int mod = 10000;

typedef vector < vector<int> > vvi;

inline vvi mul(const vvi &a, const vvi &b) {
	vvi res(a.size(), vector<int>(b[0].size()));
	for (int i = 0; i < (int)a.size(); i++)
		for (int j = 0; j < (int)b[0].size(); j++)
			for (int k = 0; k < (int)b.size(); k++)
				res[i][j] = (res[i][j] + a[i][k] * b[k][j]) % mod;
	return res;
}

vvi bin_pow_mat(vvi a, int n) {
	if (n == 0) {
		vvi res(a.size(), vector<int>(a.size()));
		for (int i = 0; i < (int)a.size(); i++)
			res[i][i] = 1;
		return res;
	}
	if (n % 2 == 1) {
		vvi res = bin_pow_mat(a, n - 1);
		return mul(a, res);
	} else {
		vvi res = bin_pow_mat(a, n / 2);
		return mul(res, res);
	}
}

int bin_pow(int a, int n) {
	int u = a, res = 1;
	while (n) {
		if (n % 2 == 1)
			res = (res * u) % mod;
		u = (u * u) % mod;
		n /= 2;
	}
	return res;
}

struct Node {
	int next[alph];
	int p, ls, suflink;
	bool term;

	Node() = default;

	Node(int np, int nls) {
		for (int i = 0; i < alph; i++)
			next[i] = -1;
		p = np;
		ls = nls;
		suflink = -1;
		term = false;
	}
};

vector <Node> trie(1, Node(0, -1));

inline void add(const string &s) {
	int v = 0, c;
	for (int i = 0; i < (int)s.size(); i++) {
		c = (int)(s[i] - 'a');
		if (trie[v].next[c] == -1) {
			trie.push_back(Node(v, c));
			trie[v].next[c] = (int)trie.size() - 1;
		}
		v = trie[v].next[c];
	}
	trie[v].term = true;
}

int get_suflink(int v) {
	if (trie[v].suflink != -1)
		return trie[v].suflink;
	if (trie[v].p == 0)
		return 0;

	int cur = get_suflink(trie[v].p);
	while (cur > 0 && trie[cur].next[trie[v].ls] == -1)
		cur = get_suflink(cur);
	return (trie[cur].next[trie[v].ls] == -1 ? 0 : trie[cur].next[trie[v].ls]);
}

vector <bool> calced;

bool calc(int v) {
	if (calced[v])
		return trie[v].term;
	calced[v] = true;
	trie[v].term |= calc(trie[v].suflink);
	return trie[v].term;
}

inline int go(int v, int c) {
	while (v > 0 && trie[v].next[c] == -1)
		v = trie[v].suflink;
	return (trie[v].next[c] == -1 ? 0 : trie[v].next[c]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
	cin >> n;

	string s;
	for (int i = 0; i < n; i++) {
		cin >> s;
		add(s);
	}

	n = (int)trie.size();
	calced.resize(n);

	for (int i = 0; i < n; i++)
		trie[i].suflink = get_suflink(i);
	for (int i = 0; i < n; i++)
		trie[i].term = calc(i);

	vvi g(n, vector<int>(n));
	for (int i = 0; i < n; i++) {
		if (trie[i].term)
			continue;
		for (int c = 0; c < alph; c++) {
			int to = go(i, c);
			if (trie[to].term)
				continue;
			g[i][to]++;
		}
	}

	vvi one(1, vector<int>(n));
	one[0][0] = 1;

	int l;
	cin >> l;

	vvi dp = bin_pow_mat(g, l);
	vvi sumv = mul(one, dp);

	int sum = 0;
	for (int i = 0; i < n; i++)
		sum = (sum + sumv[0][i]) % mod;

	int ans = (bin_pow(alph, l) + mod - sum) % mod;
	cout << ans;
	return 0;
}
