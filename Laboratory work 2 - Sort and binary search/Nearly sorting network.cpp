#include <bits/stdc++.h>
using namespace std;

const int MAXN = 12;

int n;
vector <int> sorted[MAXN][MAXN], substr[MAXN][MAXN], arr;
vector < pair<int, int> >  ans;

void build(int l, int r) {
	if (r - l + 1 <= 2)
		return;

	if (substr[l][r - 1] != sorted[l][r - 1]) {
		build(l, r - 1);
		if (arr[r] == 0) {
			for (int i = r; i > l; i--)
				ans.push_back(make_pair(i - 1, i));
		} else {
			for (int i = l; i < r; i++)
				ans.push_back(make_pair(i, r));
		}
	} else {
		build(l + 1, r);
		if (arr[l] == 0) {
			for (int i = r; i > l; i--)
				ans.push_back(make_pair(l, i));
		} else {
			for (int i = l; i < r; i++)
				ans.push_back(make_pair(i, i + 1));
		}
	}
}

void solve() {
	arr.resize(n);
	ans.clear();
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	for (int i = 0; i < n; i++) {
		vector <int> scur, cur;
		for (int j = i; j < n; j++) {
			cur.push_back(arr[j]);
			scur.push_back(arr[j]);
			for (int k = (int)scur.size() - 1; k > 0; k--) {
				if (scur[k] < scur[k - 1])
					swap(scur[k], scur[k - 1]);
			}
			sorted[i][j] = scur;
			substr[i][j] = cur;
		}
	}

	if (arr == sorted[0][n - 1]) {
		cout << -1 << '\n';
	} else {
		build(0, n - 1);
		cout << (int)ans.size() << '\n';
		for (int i = 0; i < (int)ans.size(); i++)
			cout << ans[i].first + 1 << ' ' << ans[i].second + 1 << '\n';
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	while (cin >> n) {
		if (n == 0)
			break;
		solve();
	}

	return 0;
}
