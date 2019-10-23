#include <bits/stdc++.h>
using namespace std;

int n, m, cur_comp;
vector < vector<int> > g, tr_g;
vector <int> color, comp, topsort;
vector < pair< pair<int, int>, char> > arr;

inline void roadroller() {
	g.clear();
	g.resize(2 * n);
	tr_g.clear();
	tr_g.resize(2 * n);
	color.clear();
	color.resize(2 * n);
	comp.clear();
	comp.resize(2 * n);
	topsort.clear();
	cur_comp = 0;
}

void dfs(int v) {
	color[v] = 1;
	for (int i = 0; i < (int)g[v].size(); i++) {
		int to = g[v][i];
		if (color[to] == 0)
			dfs(to);
	}
	color[v] = 2;
	topsort.push_back(v);
}

void tr_dfs(int v) {
	comp[v] = cur_comp;
	color[v] = 1;
	for (int i = 0; i < (int)tr_g[v].size(); i++) {
		int to = tr_g[v][i];
		if (color[to] == 0)
			tr_dfs(to);
	}
	color[v] = 2;
}

bool check(int x) {
	roadroller();

	for (int i = 0; i < x; i++) {
		int add = (arr[i].second == 'L');
		g[arr[i].first.first * 2].push_back(arr[i].first.second * 2 + add);
		tr_g[arr[i].first.second * 2 + add].push_back(arr[i].first.first * 2);
		g[arr[i].first.second * 2 + add].push_back(arr[i].first.first * 2);
		tr_g[arr[i].first.first * 2].push_back(arr[i].first.second * 2 + add);
		g[arr[i].first.first * 2 + 1].push_back(arr[i].first.second * 2 + !add);
		tr_g[arr[i].first.second * 2 + !add].push_back(arr[i].first.first * 2 + 1);
		g[arr[i].first.second * 2 + !add].push_back(arr[i].first.first * 2 + 1);
		tr_g[arr[i].first.first * 2 + 1].push_back(arr[i].first.second * 2 + !add);
	}

	for (int i = 0; i < 2 * n; i++) {
		if (color[i] == 0)
			dfs(i);
	}

	for (int i = 0; i < 2 * n; i++)
		color[i] = 0;

	for (int i = 2 * n - 1; i >= 0; i--) {
		if (color[topsort[i]] == 0) {
			tr_dfs(topsort[i]);
			cur_comp++;
		}
	}

	for (int i = 0; i < n; i++) {
		if (comp[2 * i] == comp[2 * i + 1]) {
			return false;
		}
	}
	return true;
}

int main() {
    freopen("truth.in", "r", stdin);
    freopen("truth.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> n >> m;

	arr.resize(m);
	for (int i = 0; i < m; i++) {
		cin >> arr[i].first.first >> arr[i].first.second >> arr[i].second;
		arr[i].first.first--; arr[i].first.second--;
	}

	int l = 0, r = m + 1;
	while (r - l > 1) {
		int mid = (l + r) / 2;
		if (check(mid)) {
			l = mid;
		} else {
			r = mid;
		}
	}
	cout << l;

	return 0;
}
