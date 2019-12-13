#include <bits/stdc++.h>
using namespace std;

vector <string> arr;
char types[2] = { 'B', 'W' };
vector < vector<int> > g;
vector < vector< pair <int, int> > > cells;
vector <int> match, L, R, cover;
vector <bool> used;

struct kek {
	int t, x, y;
	char c;
	kek(int nt, int nx, int ny) {
	    t = nt;
	    x = nx;
	    y = ny;
	}
	kek() = default;
};

vector <kek> ans((int)1e+6 + 3);

bool dfs(int v) {
	if (used[v])
		return false;
	used[v] = true;
	for (int i = 0; i < (int)g[v].size(); i++) {
		int to = g[v][i];
		if (match[to] == -1 || dfs(match[to])) {
			match[to] = v;
			return true;
		}
	}
	return false;
}

void dfs0(int v) {
	L[v] = true;
	for (int i = 0; i < (int)g[v].size(); i++) {
		int to = g[v][i];
		R[to] = true;
		if (match[to] != -1 && !L[match[to]])
			dfs0(match[to]);
	}
}

inline void kuhn(int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			used[j] = false;
		dfs(i);
	}
}

void roadroller(int n) {
	g.clear();
	g.resize(n);
	cells.clear();
	cells.resize(2 * n);
	used.clear();
	used.resize(n);
	cover.clear();
	cover.resize(n);
	L.clear();
	L.resize(n);
	R.clear();
	R.resize(n);
	match.clear();
	match.resize(n, -1);
}

inline int diag(int x, int y, int t) {
	if (t == 0) {
		return (int)arr.size() - x + y - 1;
	} else {
		return diag(x, (int)arr[0].size() - y - 1, 0);
	}
}

void solve(int step) {
	int n = (int)arr.size() + (int)arr[0].size() - 1;
	roadroller(n);

	for (int i = 0; i < (int)arr.size(); i++) {
		for (int j = 0; j < (int)arr[i].size(); j++) {
			if (arr[i][j] != types[(i + j + step) % 2]) {
				g[diag(i, j, 0)].push_back(diag(i, j, 1));
				cells[diag(i, j, 0)].push_back(make_pair(i, j));
				cells[diag(i, j, 1) + n].push_back(make_pair(i, j));
			}
		}
	}

	kuhn(n);

	for (int i = 0; i < n; i++) {
		if (match[i] != -1)
			cover[match[i]] = true;
	}

	for (int i = 0; i < n; i++) {
		if (!cover[i])
			dfs0(i);
	}

	vector <kek> cur_ans;
	for (int i = 0; i < n; i++) {
		if (!L[i] && (int)g[i].size() > 0) {
			cur_ans.push_back(kek(2, cells[i][0].first + 1, cells[i][0].second + 1));
			if (arr[cells[i][0].first][cells[i][0].second] == 'B') {
				cur_ans.back().c = 'W';
			} else {
				cur_ans.back().c = 'B';
			}
		}
	}
	for (int i = 0; i < n; i++) {
		if (R[i]) {
			cur_ans.push_back(kek(1, cells[i + n][0].first + 1, cells[i + n][0].second + 1));
			if (arr[cells[i + n][0].first][cells[i + n][0].second] == 'B') {
				cur_ans.back().c = 'W';
			} else {
				cur_ans.back().c = 'B';
			}
		}
	}
	if ((int)cur_ans.size() < (int)ans.size())
		ans = cur_ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
	cin >> n >> m;

	arr.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	for (int t = 0; t < 2; t++)
		solve(t);

	cout << (int)ans.size() << '\n';
	for (int i = 0; i < (int)ans.size(); i++)
		cout << ans[i].t << " " << ans[i].x << " " << ans[i].y << " " << ans[i].c << '\n';
    return 0;
}
