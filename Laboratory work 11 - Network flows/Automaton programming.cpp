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
		bool any = false;
		for (int i = 0; i < (int)g.size(); i++) {
			if (d[i] == inf)
				continue;
			for (int j = 0; j < (int)g[i].size(); j++) {
				int num = g[i][j];
				if (lst[num].f == lst[num].c)
					continue;
				if (d[lst[num].to] > d[i] + lst[num].cost) {
					any = true;
					d[lst[num].to] = d[i] + lst[num].cost;
					par[lst[num].to] = make_pair(i, num);
				}
			}
		}
		if (!any)
			break;
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

struct task {
	int l, t, cost, num;

	task() = default;

	task(int nl, int nt, int nc, int nn) {
		l = nl;
		t = nt;
		cost = nc;
		num = nn;
	}

	bool operator<(const task& b) {
		if (l != b.l)
			return l < b.l;
		else
			return num < b.num;
	}
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, k, a, b, numeric = 0;
	cin >> n >> k;

	s = 0; t = 2 * n + 1;

	vector <task> arr(n);
	for (int i = 0; i < n; i++) {
		cin >> arr[i].l >> arr[i].t >> arr[i].cost;
		arr[i].num = i;
	}

	g.resize(2 * n + 3);
	lst.resize(2 * (n * n + 2 * n + 1));

	for (int i = 0; i < n; i++) {
		lst[numeric] = edge(i + 1, 0, 1, 0);
		g[s].push_back(numeric++);
		lst[numeric] = edge(s, 0, 0, 0);
		g[i + 1].push_back(numeric++);
	}
	for (int i = 0; i < n; i++) {
		a = i + 1; b = i + 1 + n;
		lst[numeric] = edge(b, 0, 1, -arr[i].cost);
		g[a].push_back(numeric++);
		lst[numeric] = edge(a, 0, 0, arr[i].cost);
		g[b].push_back(numeric++);
	}
	sort(arr.begin(), arr.end());
	for (int i = 0; i < n; i++) {
		a = arr[i].num + 1;
		if (i < n - 1) {
			b = arr[i + 1].num + 1;
		} else {
			b = t;
		}
		lst[numeric] = edge(b, 0, k, 0);
		g[a].push_back(numeric++);
		lst[numeric] = edge(a, 0, 0, 0);
		g[b].push_back(numeric++);
	}
	for (int i = 0; i < n; i++) {
		a = arr[i].num + 1 + n;
		int ptr = lower_bound(arr.begin(), arr.end(), task(arr[i].l + arr[i].t, 0, 0, -1)) - arr.begin();
		if (ptr < (int)arr.size()) {
			b = arr[ptr].num + 1;
		} else {
			b = t;
		}
		lst[numeric] = edge(b, 0, 1, 0);
		g[a].push_back(numeric++);
		lst[numeric] = edge(a, 0, 0, 0);
		g[b].push_back(numeric++);
	}

	lst[numeric] = edge(t + 1, 0, k, 0);
	g[t].push_back(numeric++);
	lst[numeric] = edge(t, 0, 0, 0);
	g[t + 1].push_back(numeric++);
	t++;
	lst.resize(numeric);

	while (push_flow()) {}

	vector <int> ans(n);
	for (int i = n + 1; i <= 2 * n; i++) {
		for (int j = 0; j < (int)g[i].size(); j++) {
			int num = g[i][j];
			if (lst[num].f == 1) {
				ans[i - n - 1] = 1;
			}
		}
	}

	for (int i = 0; i < n; i++)
		cout << ans[i] << " ";
    return 0;
}
