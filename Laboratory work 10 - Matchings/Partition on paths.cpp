#include <bits/stdc++.h>
using namespace std;

vector < unordered_multiset<int> > g;
vector < pair<int, int> > ans;

void dfs(int v) {
	while (!g[v].empty()) {
		int to = *g[v].begin();
		g[v].erase(g[v].begin());
		g[to].erase(g[to].find(v));
		dfs(to);
		ans.push_back(make_pair(v, to));
	}
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, a, b;
	cin >> n >> m;

	g.resize(n);

	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		a--; b--;
		g[a].insert(b);
		g[b].insert(a);
	}

	vector <int> start;
	for (int i = 0; i < n; i++) {
		if ((int)g[i].size() % 2 == 1)
			start.push_back(i);
	}

	set < pair<int, int> > add;
	for (int i = 1; i < (int)start.size() - 2; i += 2) {
		add.insert(make_pair(start[i - 1], start[i]));
		g[start[i - 1]].insert(start[i]);
		g[start[i]].insert(start[i - 1]);
	}

	if (start.empty())
		start.push_back(0);

	dfs(start.back());
	reverse(ans.begin(), ans.end());

	vector < vector< pair<int, int> > > path(1);
	for (int i = 0; i < (int)ans.size(); i++) {
		if (add.count(make_pair(ans[i].first, ans[i].second)) ||
		    add.count(make_pair(ans[i].second, ans[i].first))) {
			add.erase(make_pair(ans[i].first, ans[i].second));
			add.erase(make_pair(ans[i].second, ans[i].first));
			path.emplace_back();
			continue;
		}
		path.back().push_back(ans[i]);
	}

	while (path.back().empty())
		path.pop_back();

	cout << (int)path.size() << '\n';
	for (int i = 0; i < (int)path.size(); i++) {
		for (int j = 0; j < (int)path[i].size(); j++)
			cout << path[i][j].first + 1 << " ";
		cout << path[i].back().second + 1 << '\n';
	}
    return 0;
}
