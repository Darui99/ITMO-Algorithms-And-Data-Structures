#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, m, k, x, l, r;
	cin >> n >> m >> k;

	vector < pair<int, int> > arr;
	for (int i = 0; i < k; i++) {
		cin >> x;
		while (x--) {
			cin >> l >> r;
			if (l > r)
				swap(l, r);
			arr.push_back(make_pair(l - 1, r - 1));
		}
	}

	for (int mask = 0; mask < (1 << n); mask++) {
		vector <int> cur(n), sorted;
		for (int i = 0; i < n; i++) {
			if ((1 << i) & mask)
				cur[i] = 1;
			else
				cur[i] = 0;
		}
		sorted = cur;
		for (int i = 0; i < n; i++) {
			for (int j = n - 1; j > i; j--) {
				if (sorted[j] < sorted[j - 1])
					swap(sorted[j], sorted[j - 1]);
			}
		}

		for (int i = 0; i < m; i++) {
			if (cur[arr[i].first] > cur[arr[i].second])
				swap(cur[arr[i].first], cur[arr[i].second]);
		}

		if (cur != sorted) {
			cout << "No";
			return 0;
		}
	}
	cout << "Yes";

	return 0;
}
