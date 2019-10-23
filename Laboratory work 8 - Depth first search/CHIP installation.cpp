#include <bits/stdc++.h>
using namespace std;

vector <int> arr, owner, tp, color, topsort, comp;
vector <bool> used;
vector < vector<int> > g, tr_g, can;

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

int cur_comp = 0;

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

int main() {
    freopen("chip.in", "r", stdin);
    freopen("chip.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n;
    cin >> n;

    arr.resize(n);
    used.resize(n);
    can.resize(n);
    comp.resize(2 * n);
    color.resize(2 * n);
    tp.resize(2 * n);
    owner.resize(2 * n);
    g.resize(2 * n);
    tr_g.resize(2 * n);

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    for (int i = 0; i < 2 * n; i++) {
        cin >> owner[i];
        owner[i]--;
        can[owner[i]].push_back(i);
    }

    for (int i = 0; i < 2 * n; i++) {
        if (!used[owner[i]]) {
            used[owner[i]] = true;
        } else {
            tp[i]++;
        }
    }

    for (int i = 0; i < (int)owner.size(); i++) {
        int prev = (i - 1 + 2 * n) % (2 * n);
        int next = (i + 1) % (2 * n);
        if (arr[owner[prev]] == arr[owner[i]]) {
            g[owner[i] * 2 + tp[i]].push_back(owner[prev] * 2 + !tp[prev]);
            tr_g[owner[prev] * 2 + !tp[prev]].push_back(owner[i] * 2 + tp[i]);
        }
        if (arr[owner[next]] == arr[owner[i]]) {
            g[owner[i] * 2 + tp[i]].push_back(owner[next] * 2 + !tp[next]);
            tr_g[owner[next] * 2 + !tp[next]].push_back(owner[i] * 2 + tp[i]);
        }
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
            cout << "NO";
            return 0;
        }
    }

    cout << "YES\n";
    for (int i = 0; i < n; i++) {
        if (comp[2 * i] > comp[2 * i + 1]) {
            cout << can[i][0] + 1 << " ";
        } else {
            cout << can[i][1] + 1 << " ";
        }
    }

	return 0;
}

