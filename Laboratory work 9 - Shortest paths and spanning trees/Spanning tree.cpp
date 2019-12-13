#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll inf = (ll)4e+18;

inline ll dist(const pair <ll, ll> &a, const pair<ll, ll> &b) {
	return (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n;
	cin >> n;
	vector < pair<ll, ll> > arr(n);
	for (int i = 0; i < n; i++)
		cin >> arr[i].first >> arr[i].second;

	vector <ll> d(n, inf);
	vector <bool> used(n);
	d[0] = 0ll;
	double ans = 0.0;
	for (int i = 0; i < n; i++) {
		ll minu = inf;
		int iminu = -1;
		for (int j = 0; j < n; j++) {
			if (!used[j] && d[j] < minu) {
				minu = d[j];
				iminu = j;
			}
		}
		if (iminu == -1)
			break;
		ans += (double)sqrt(minu);
		used[iminu] = true;
		for (int j = 0; j < n; j++) {
				d[j] = min(d[j], dist(arr[iminu], arr[j]));
		}
	}

	cout.precision(20);
	cout << fixed << ans;

	return 0;
}
