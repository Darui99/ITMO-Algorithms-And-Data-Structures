#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = (ll)1e+9 + 7ll;

ll sum = 0ll;
vector < vector< pair<int, int> > > g;
vector <ll> w, arr;
vector < pair<int, int> > bounds;

void dfs(int v, int p) {
	w[v] = 1ll;
	for (int i = 0; i < (int)g[v].size(); i++) {
		int to = g[v][i].first;
		if (to == p)
			continue;
		dfs(to, v);
		w[v] += w[to];
	}
}

void calc(int v, int p) {
	for (int i = 0; i < (int)g[v].size(); i++) {
		int to = g[v][i].first, num = g[v][i].second;
		if (to == p)
			continue;
		calc(to, v);
		arr[num] = w[to] * (w[0] - w[to]) * 2ll;
		sum += arr[num];
		if (sum > (ll)5e+5) {
			cout << 0;
			exit(0);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, m, s, a, b, l, r, lb, rb;
	cin >> n >> s;
	m = n - 1;

	g.resize(n);
	bounds.resize(m);
	w.resize(n);
	arr.resize(m);

	for (int i = 0; i < m; i++) {
		cin >> a >> b >> l >> r;
		a--; b--;
		g[a].push_back(make_pair(b, i));
		g[b].push_back(make_pair(a, i));
		bounds[i] = make_pair(l, r);
	}

	dfs(0, 0);
	calc(0, 0);
	vector <ll> pref(s + 1), dp(s + 1);
	dp[0] = 1ll;

	ll cur;
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j <= s; j++) {
            if (j - arr[i - 1] >= 0)
                pref[j] = (pref[j - (int)arr[i - 1]] + dp[j]) % mod;
            else
                pref[j] = dp[j];
        }
        for (int j = 0; j <= s; j++) {
            rb = j - bounds[i - 1].first * (int)arr[i - 1];
            lb = j - (bounds[i - 1].second + 1) * (int)arr[i - 1];
            if (rb >= 0) {
                cur = pref[rb];
                if (lb >= 0)
                    cur = (cur + mod - pref[lb]) % mod;
                dp[j] = cur;
            } else {
                dp[j] = 0ll;
            }
        }
    }
    cout << dp[s];
	return 0;
}
