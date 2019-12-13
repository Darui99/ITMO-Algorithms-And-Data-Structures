#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, m, a, b;
	cin >> n >> m;

	vector < vector<int> > g(n);
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		a--; b--;
		g[a].push_back(b);
		g[b].push_back(a);
	}

	vector <int> d(n, (int)1e+9 + 7);
	d[0] = 0;
	queue <int> q;
	q.push(0);

	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (int i = 0; i < (int)g[v].size(); i++) {
			int to = g[v][i];
			if (d[to] > d[v] + 1) {
				d[to] = d[v] + 1;
				q.push(to);
			}
		}
	}

	for (int i = 0; i < n; i++)
		cout << d[i] << " ";

	return 0;
}
