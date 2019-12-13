#include <bits/stdc++.h>
using namespace std;

vector < vector<int> > g, tr_g;
vector <int> color, topsort, comp;

void dfs(int v) {
    color[v] = 1;
    for (int i = 0; i < (int)g[v].size(); i++) {
        int to = g[v][i];
        if (color[to] == 0)
            dfs(to);
    }
    topsort.push_back(v);
    color[v] = 2;
}

int cur_comp = 0;

void tr_dfs(int v) {
    color[v] = 1;
    comp[v] = cur_comp;
    for (int i = 0; i < (int)tr_g[v].size(); i++) {
        int to = tr_g[v][i];
        if (color[to] == 0)
            tr_dfs(to);
    }
    color[v] = 2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, sz, x;
    cin >> n;

    g.resize(2 * n);
    tr_g.resize(2 * n);
    color.resize(2 * n);
    comp.resize(2 * n);

    vector < pair<int, int> > lst;

    for (int i = 0; i < n; i++) {
        cin >> sz;
        while (sz--) {
            cin >> x;
            x--;
            lst.push_back(make_pair(i, n + x));
        }
    }

    for (int i = 0; i < n; i++) {
        cin >> x;
        x--;
        g[n + x].push_back(i);
        tr_g[i].push_back(n + x);
    }

    for (int i = 0; i < (int)lst.size(); i++) {
        if (g[lst[i].second][0] != lst[i].first) {
            g[lst[i].first].push_back(lst[i].second);
            tr_g[lst[i].second].push_back(lst[i].first);
        }
    }

    for (int i = 0; i < 2 * n; i++) {
        if (color[i] == 0)
            dfs(i);
    }

    for (int i = 0; i < 2 * n; i++)
        color[i] = 0;

    for (int i = (int)topsort.size() - 1; i >= 0; i--) {
        if (color[topsort[i]] == 0) {
            tr_dfs(topsort[i]);
            cur_comp++;
        }
    }

    vector < vector <int> > ans(n);
    for (int i = 0; i < n; i++)
        ans[g[n + i][0]].push_back(n + i);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (int)g[i].size(); j++) {
            if (comp[i] == comp[g[i][j]])
                ans[i].push_back(g[i][j]);
        }
        cout << (int)ans[i].size() << " ";
        for (int j = 0; j < (int)ans[i].size(); j++)
            cout << ans[i][j] - n + 1 << " ";
        cout << '\n';
    }

    return 0;
}

