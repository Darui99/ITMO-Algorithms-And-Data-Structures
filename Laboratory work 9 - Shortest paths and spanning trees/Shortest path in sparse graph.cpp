#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, m, a, b, c;
	cin >> n >> m;

	vector < vector < pair<int, int> > > g(n);
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		a--; b--;
		g[a].push_back(make_pair(b, c));
		g[b].push_back(make_pair(a, c));
	}

	vector <int> d(n, (int)1e+9 + 7);
	d[0] = 0;

	set < pair<int, int> > q;
	q.insert(make_pair(0, 0));

	while (!q.empty()) {
		int v = q.begin()->second;
		q.erase(q.begin());

		for (int i = 0; i < (int)g[v].size(); i++) {
			int to = g[v][i].first, cost = g[v][i].second;
			if (d[to] > d[v] + cost) {
				q.erase(make_pair(d[to], to));
				d[to] = d[v] + cost;
				q.insert(make_pair(d[to], to));
			}
		}
	}

	for (int i = 0; i < n; i++)
		cout << d[i] << " ";

	return 0;
}
