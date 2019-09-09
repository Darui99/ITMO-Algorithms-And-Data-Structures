#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXX = (int)1e+6 + 5;
const int S = 450;

ll cnt[MAXX];

struct ask {
	int l, r, num;
};

bool cmp(const ask &a, const ask &b) {
	return make_pair(a.l / S, a.r) < make_pair(b.l / S, b.r);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, m;
	cin >> n >> m;

	vector <ll> arr(n);
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	vector <ask> q(m);
	for (int i = 0; i < m; i++) {
		cin >> q[i].l >> q[i].r;
		q[i].l--; q[i].r--;
		q[i].num = i;
	}
	sort(q.begin(), q.end(), cmp);

	vector <ll> ans(m);
	ll cur = 0ll;

	for (int i = q[0].l; i <= q[0].r; i++) {
		cur += 2ll * cnt[arr[i]] * arr[i] + arr[i];
		cnt[arr[i]]++;
	}
	ans[q[0].num] = cur;

	int L = q[0].l, R = q[0].r;
	for (int i = 1; i < m; i++) {
		if (q[i].l < L) {
			for (int j = L - 1; j >= q[i].l; j--) {
				cur += 2ll * cnt[arr[j]] * arr[j] + arr[j];
				cnt[arr[j]]++;
			}
		} else {
			for (int j = L; j < q[i].l; j++) {
				cur += -2ll * cnt[arr[j]] * arr[j] + arr[j];
				cnt[arr[j]]--;
			}
		}
		if (q[i].r < R) {
			for (int j = R; j > q[i].r; j--) {
				cur += -2ll * cnt[arr[j]] * arr[j] + arr[j];
				cnt[arr[j]]--;
			}
		} else {
			for (int j = R + 1; j <= q[i].r; j++) {
				cur += 2ll * cnt[arr[j]] * arr[j] + arr[j];
				cnt[arr[j]]++;
			}
		}
		ans[q[i].num] = cur;
		L = q[i].l; R = q[i].r;
	}

	for (int i = 0; i < m; i++)
		cout << ans[i] << '\n';

	return 0;
}
