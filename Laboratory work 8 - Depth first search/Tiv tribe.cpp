#include <bits/stdc++.h>
using namespace std;

const int alpha = 26;

vector < vector<int> > g;

inline int diff(const string &a, const string &b) {
	for (int i = 0; i < (int)min(a.size(), b.size()); i++) {
		if (a[i] != b[i])
			return i;
	}
	return -1;
}

vector <int> topsort, color;

void dfs(int v) {
	color[v] = 1;
	for (int i = 0; i < (int)g[v].size(); i++) {
		int to = g[v][i];
		if (color[to] == 1) {
			cout << "No";
			exit(0);
		}
		if (color[to] == 0)
			dfs(to);
	}
	color[v] = 2;
	topsort.push_back(v);
}

int main() {
    freopen("tiv.in", "r", stdin);
    freopen("tiv.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n;
	cin >> n;

	g.resize(alpha);
	color.resize(alpha);

	vector <bool> zero(alpha, true);
	vector <string> arr(n);

	for (int i = 0; i < n; i++)
		cin >> arr[i];

	for (int i = 1; i < n; i++) {
		if ((int)arr[i].size() < (int)arr[i - 1].size()) {
			cout << "No";
			return 0;
		}
		if ((int)arr[i].size() > (int)arr[i - 1].size())
			continue;
		int cur = diff(arr[i - 1], arr[i]);
		if (cur == -1) {
			cout << "No";
			return 0;
		}
		g[arr[i][cur] - 'a'].push_back(arr[i - 1][cur] - 'a');
		zero[arr[i][cur] - 'a'] = false;
	}

	for (int i = 0; i < n; i++) {
		if ((int)arr[i].size() > 1)
			zero[arr[i][0] - 'a'] = false;
	}

	bool flag = true;
	for (int i = 0; i < alpha; i++) {
		if (zero[i]) {
			flag = false;
			for (int j = 0; j < alpha; j++) {
				if (i == j)
					continue;
				g[j].push_back(i);
			}
			break;
		}
	}

	if (flag) {
		cout << "No";
		return 0;
	}

	for (int i = 0; i < alpha; i++) {
		if (color[i] == 0)
			dfs(i);
	}

	cout << "Yes\n";

	vector <int> ans(topsort.size());
	for (int i = 0; i < (int)topsort.size(); i++)
		ans[topsort[i]] = i;

	for (int i = 0; i < (int)ans.size(); i++)
		cout << ans[i] << " ";

	return 0;
}
