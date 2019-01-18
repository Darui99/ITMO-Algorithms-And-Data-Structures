#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("garland.in", "r", stdin);
    freopen("garland.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;
	vector <double> h(n);

	double A;
	cin >> A;

	double l = 0.0, r = A;
	for (int step = 0; step < 50; step++) {
		double mid = (l + r) / 2.0;
		h[0] = A; h[1] = mid;

		bool flag = true;
		for (int i = 2; i < n; i++) {
			h[i] = 2.0 * h[i - 1] + 2.0 - h[i - 2];
			if (h[i] <= 0.0) {
				flag = false;
				break;
			}
		}
		if (flag)
			r = mid;
		else
			l = mid;
	}

	h[0] = A; h[1] = l;
	for (int i = 2; i < n; i++)
		h[i] = 2.0 * h[i - 1] + 2.0 - h[i - 2];

	cout.precision(2);
	cout << fixed << h.back();

	return 0;
}
