#include <bits/stdc++.h>
using namespace std;

vector < vector<int> > g;
vector <int> color;
vector < pair<int, int> > ans;

void dfs(int v, int root, int son) {
	color[v] = 1;
	for (int i = 0; i < (int)g[v].size(); i++) {
		int to = g[v][i];
		if (color[to] == 0) {
			if (v != root && to > son)
				ans.push_back(make_pair(root, to));
			if (v == root) {
				dfs(to, root, to);
			} else {
				dfs(to, root, son);
			}
		}
	}
	color[v] = 2;
}

int main() {
    freopen("dfs.in", "r", stdin);
    freopen("dfs.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, m;
	cin >> n >> m;

	vector <int> arr(m), last(m);
	g.resize(n);
	color.resize(n);

	for (int i = 0; i < m; i++) {
		cin >> arr[i];
		arr[i]--;
		last[arr[i]] = i;
	}

	for (int i = 0; i < m; i++) {
		if (i == 0 || last[arr[i - 1]] == i - 1)
			continue;
		if (!g[arr[i - 1]].empty() && g[arr[i - 1]].back() == arr[i])
			continue;
		g[arr[i - 1]].push_back(arr[i]);
		ans.push_back(make_pair(arr[i - 1], arr[i]));
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			color[j] = 0;
		dfs(i, i, -1);
	}

	cout << (int)ans.size() << '\n';
	for (int i = 0; i < (int)ans.size(); i++)
		cout << ans[i].first + 1 << " " << ans[i].second + 1 << '\n';

	return 0;
}
