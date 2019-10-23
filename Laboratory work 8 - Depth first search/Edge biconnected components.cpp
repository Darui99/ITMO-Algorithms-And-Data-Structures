#include <bits/stdc++.h>
using namespace std;

vector < vector< pair<int, int> > > g;
vector <int> color, tin, up, comp;

int timer = 0, cur_comp = 0;
stack <int> q;

void dfs(int v, int p) {
	color[v] = 1;
	tin[v] = timer++;
	up[v] = tin[v];
	q.push(v);
	for (int i = 0; i < (int)g[v].size(); i++) {
		int to = g[v][i].first, num = g[v][i].second;
		if (num == p)
			continue;
		if (color[to] == 1) {
			up[v] = min(up[v], tin[to]);
		}
		if (color[to] == 0) {
			dfs(to, num);
			up[v] = min(up[v], up[to]);
			if (up[to] > tin[v]) {
				while (q.top() != to) {
					comp[q.top()] = cur_comp;
					q.pop();
				}
				comp[q.top()] = cur_comp;
				q.pop();
				cur_comp++;
			}
		}
	}
	color[v] = 2;
}

int main() {
    freopen("bicone.in", "r", stdin);
    freopen("bicone.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, m, a, b;
	cin >> n >> m;

	g.resize(n);
	color.resize(n);
	tin.resize(n);
	up.resize(n);
	comp.resize(n);

	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		a--; b--;
		g[a].push_back(make_pair(b, i));
		g[b].push_back(make_pair(a, i));
	}

	for (int i = 0; i < n; i++) {
		if (color[i] == 0) {
			dfs(i, -1);
			while (!q.empty()) {
				comp[q.top()] = cur_comp;
				q.pop();
			}
			cur_comp++;
		}
	}

	cout << cur_comp << endl;
	for (int i = 0; i < n; i++)
		cout << comp[i] + 1 << " ";

	return 0;
}
