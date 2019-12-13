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
    int n, sz, x;
	cin >> n;

	g.resize(n);

	for (int i = 0; i < n; i++) {
		cin >> sz;
		while (sz--) {
			cin >> x;
			g[i].insert(x - 1);
		}
	}

	vector <int> start;
	for (int i = 0; i < n; i++) {
		if ((int)g[i].size() % 2 == 1)
			start.push_back(i);
	}

	if ((int)start.size() > 2) {
		cout << -1;
		return 0;
	}
	if (start.empty())
		start.push_back(0);

	dfs(start[0]);
	cout << (int)ans.size() << '\n';
	for (int i = (int)ans.size() - 1; i >= 0; i--)
		cout << ans[i].first + 1 << " ";
	cout << ans[0].second + 1;
    return 0;
}
