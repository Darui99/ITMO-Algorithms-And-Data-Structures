#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("binsearch.in", "r", stdin);
    freopen("binsearch.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	vector <int> arr(n);
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	int q, x;
	cin >> q;

	while (q--) {
		cin >> x;

		int l = 0, r = n - 1;
		while (l != r) {
			int mid = (l + r) / 2;
			if (arr[mid] >= x) {
				r = mid;
			} else {
				l = mid + 1;
			}
		}

		if (arr[l] != x) {
			cout << "-1 -1\n";
			continue;
		}
		cout << l + 1 << " ";

		l = 0; r = n - 1;
		while (l != r) {
			int mid = (l + r) / 2;
			if (mid == l)
				mid++;
			if (arr[mid] <= x) {
				l = mid;
			} else {
				r = mid - 1;
			}
		}
		cout << r + 1 << '\n';
	}

	return 0;
}
