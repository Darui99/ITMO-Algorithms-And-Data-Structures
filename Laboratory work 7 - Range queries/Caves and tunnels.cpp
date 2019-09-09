#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll inf = (ll)4e+18;

struct Node {
	Node* left;
	Node* right;
	ll lb, rb, maxu;
};

Node* Empty = new Node{ NULL, NULL, 0ll, 0ll, -inf };

Node* build(ll l, ll r) {
	if (l == r)
		return new Node{ Empty, Empty, l, r, 0ll };
	ll mid = (l + r) / 2ll;
	Node* L = build(l, mid);
	Node* R = build(mid + 1, r);
	return new Node{ L, R, l, r, 0ll };
}

Node* root;

ll get(Node* v, ll l, ll r) {
	if (r < v->lb || l > v->rb)
		return -inf;
	if (l <= v->lb && v->rb <= r)
		return v->maxu;
	return max(get(v->left, l, r), get(v->right, l, r));
}

void update(Node* v, ll x, ll k) {
	if (v->lb == v->rb) {
		v->maxu += k;
		return;
	}
	if (v->left->lb <= x && x <= v->left->rb) {
		update(v->left, x, k);
	} else {
		update(v->right, x, k);
	}
	v->maxu = max(v->left->maxu, v->right->maxu);
}

const int LOGN = 17;
const int MAXN = (int)1e+5 + 5;

int par[LOGN][MAXN];

vector < vector<int> > g;
vector <int> tin, tout, w, nextw, leader, pos;
vector <bool> arrow, calced;

int timer = 1;
void dfs(int v, int p) {
	par[0][v] = p;
	tin[v] = timer++;
	w[v] = 1;

	int maxu = -1, imaxu = v;
	for (int i = 0; i < (int)g[v].size(); i++) {
		int to = g[v][i];
		if (to == p)
			continue;
		dfs(to, v);
		w[v] += w[to];
		if (w[to] > maxu) {
			maxu = w[to];
			imaxu = to;
		}
	}
	nextw[v] = imaxu;
	if (imaxu != v)
		arrow[imaxu] = true;
	tout[v] = timer++;
}

inline bool check_par(int v, int u) {
	return (tin[v] <= tin[u] && tout[u] <= tout[v]);
}

inline int lca(int a, int b) {
	if (check_par(a, b))
		return a;
	if (check_par(b, a))
		return b;

	int now = a;
	for (int i = LOGN - 1; i >= 0; i--) {
		int to = par[i][now];
		if (!check_par(to, a) || !check_par(to, b))
			now = to;
	}
	return par[0][now];
}

inline ll get_vert(int v, int p) {
	ll res = -inf;
	while (true) {
		if (check_par(p, leader[v]) && p != leader[v]) {
			res = max(res, get(root, pos[leader[v]], pos[v]));
			v = par[0][leader[v]];
		} else {
			res = max(res, get(root, pos[p], pos[v]));
			break;
		}
	}
	return res;
}

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, a, b;
	cin >> n;

	root = build(1ll, (ll)n);

	g.resize(n);
	tin.resize(n);
	tout.resize(n);
	w.resize(n);
	nextw.resize(n);
	arrow.resize(n);
	calced.resize(n);
	leader.resize(n);
	pos.resize(n);

	for (int i = 0; i < n - 1; i++) {
		cin >> a >> b;
		a--; b--;
		g[a].push_back(b);
		g[b].push_back(a);
	}

	dfs(0, 0);
	for (int i = 1; i < LOGN; i++) {
		for (int j = 0; j < n; j++)
			par[i][j] = par[i - 1][par[i - 1][j]];
	}

	int curpos = 1;
	for (int i = 0; i < n; i++) {
		if (arrow[i] || calced[i])
			continue;
		int curver = i;
		while (!calced[curver]) {
			leader[curver] = i;
			pos[curver] = curpos++;
			calced[curver] = true;
			curver = nextw[curver];
		}
	}

	int q, p;
	cin >> q;

	char type;
	ll x;

	while (q--) {
		cin >> type;
		if (type == 'I') {
			cin >> a >> x;
			update(root, pos[a - 1], x);
		} else {
			cin >> a >> b;
			a--; b--;
			p = lca(a, b);
			cout << max(get_vert(a, p), get_vert(b, p)) << '\n';
		}
	}

	return 0;
}
