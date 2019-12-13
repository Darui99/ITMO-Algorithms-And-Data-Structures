#include <bits/stdc++.h>
using namespace std;

vector <int> p, sz;

int get(int v) {
	if (p[v] != v)
		p[v] = get(p[v]);
	return p[v];
}

void join(int v, int u) {
	if (sz[v] < sz[u])
		swap(v, u);
	p[u] = v;
	sz[v] += sz[u];
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, m;
	cin >> n >> m;

	p.resize(n);
	sz.resize(n);

	for (int i = 0; i < n; i++) {
		p[i] = i;
		sz[i] = 1;
	}

	vector < vector<int> > edge(m);
	for (int i = 0; i < m; i++) {
		edge[i].resize(3);
		cin >> edge[i][1] >> edge[i][2] >> edge[i][0];
		edge[i][1]--; edge[i][2]--;
	}

	int ans = 0;
	sort(edge.begin(), edge.end());

	for (int i = 0; i < m; i++) {
		edge[i][1] = get(edge[i][1]);
		edge[i][2] = get(edge[i][2]);
		if (edge[i][1] != edge[i][2]) {
			ans += edge[i][0];
			join(edge[i][1], edge[i][2]);
		}
	}
	cout << ans;

	return 0;
}
