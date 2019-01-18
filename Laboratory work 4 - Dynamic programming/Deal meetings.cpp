#include <bits/stdc++.h>
using namespace std;

struct trip {
	int l, r, d;
};

int popcnt(int x) {
	int res = 0;
	while (x) {
		res++;
		x &= (x - 1);
	}
	return res;
}

int main() {
    freopen("meetings.in", "r", stdin);
    freopen("meetings.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, s;
	cin >> n >> s;

	vector <trip> arr(n);
	for (int i = 0; i < n; i++)
		cin >> arr[i].l >> arr[i].r >> arr[i].d;

	vector < set< pair<int, int> > > dp((1 << n));
	dp[0].insert(make_pair(s, 0));

	for (int mask = 0; mask < (1 << n); mask++) {
		for (int i = 0; i < n; i++) {
			if ((1 << i) & mask)
				continue;
			for (auto it = dp[mask].begin(); it != dp[mask].end(); it++) {
				if (arr[i].l <= it->first && it->first <= arr[i].r) {
					dp[mask ^ (1 << i)].insert(make_pair(it->first + arr[i].d, mask));
				}
			}
		}
	}

	int ans = -1, cur = -1;
	pair <int, int> ansp = make_pair(-1, -1);
	for (int mask = 0; mask < (1 << n); mask++) {
		if (!dp[mask].empty() && popcnt(mask) > ans) {
			ans = popcnt(mask);
			ansp = *dp[mask].begin();
			cur = mask;
		}
	}

	vector <int> path;
	int prev;
	while (true) {
		prev = ansp.second;
		if (cur == 0)
			break;
		int dif = cur ^ prev;
		for (int i = 0; i < n; i++) {
			if ((1 << i) & dif) {
				path.push_back(i);
				break;
			}
		}
		ansp = *dp[prev].begin();
		cur = prev;
	}

	cout << ans << endl;
	for (int i = ans - 1; i >= 0; i--)
		cout << path[i] + 1 << " ";
	return 0;
}
