#include <bits/stdc++.h>
using namespace std;

const int inf = (int)1e+9 + 7;

struct edge {
	int to, f, c, cost;

	edge() = default;

	edge(int nt, int fn, int cn, int ccn) {
		to = nt;
		f = fn;
		c = cn;
		cost = ccn;
	}
};

int s, t;
vector < vector<int> > g;
vector <edge> lst;

bool push_flow() {
	vector <int> d(g.size(), inf);
	vector < pair<int, int> > par(g.size(), make_pair(-1, -1));
	d[s] = 0;

	for (int t = 0; t < (int)g.size(); t++) {
		for (int i = 0; i < (int)g.size(); i++) {
			if (d[i] == inf)
				continue;
			for (int j = 0; j < (int)g[i].size(); j++) {
				int num = g[i][j];
				if (lst[num].f == lst[num].c)
					continue;
				if (d[lst[num].to] > d[i] + lst[num].cost) {
					d[lst[num].to] = d[i] + lst[num].cost;
					par[lst[num].to] = make_pair(i, num);
				}
			}
		}
	}

	int add = inf;
	pair <int, int> cur = make_pair(t, -1);
	vector <int> path;
	while (true) {
		if (cur.second != -1) {
			path.push_back(cur.second);
			add = min(add, lst[cur.second].c - lst[cur.second].f);
		}
		if (par[cur.first].first == -1)
			break;
		cur = par[cur.first];
	}
	for (int i = 0; i < (int)path.size(); i++) {
		lst[path[i]].f += add;
		lst[path[i] ^ 1].f -= add;
	}
	return (!path.empty());
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, a, b, c, cost, numeric = 0;
	cin >> n >> m;

	s = 0; t = n - 1;

	g.resize(n);
	lst.resize(2 * m);

	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c >> cost;
		a--; b--;
		lst[numeric] = edge(b, 0, c, cost);
		g[a].push_back(numeric++);
		lst[numeric] = edge(a, 0, 0, -cost);
		g[b].push_back(numeric++);
	}

	while (push_flow()) {}

	long long ans = 0ll;
	for (int i = 0; i < (int)lst.size(); i += 2)
		ans += (long long)lst[i].f * (long long)lst[i].cost;
	cout << ans;
    return 0;
}