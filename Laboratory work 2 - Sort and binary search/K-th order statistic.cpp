#include <bits/stdc++.h>
using namespace std;

int kth(int l, int r, int k, vector <int> &arr) {
	if (l == r)
		return arr[l];

	int x = arr[l + rand() % (r - l + 1)];
	int lb = l, rb = r;

	while (lb < rb) {
		while (lb < rb && arr[lb] < x)
			lb++;
		while (rb > lb && arr[rb] > x)
			rb--;
		if (lb < rb) {
			swap(arr[lb], arr[rb]);
			lb++;
			rb--;
		}
		else
			break;
	}

	if (lb == rb) {
		if (rb == 0) {
			lb++;
		} else {
			if (lb == r) {
				rb--;
			} else {
				if (arr[lb] <= x) {
					lb++;
				} else {
					rb--;
				}
			}
		}
	}

	if (rb - l + 1 >= k)
		return kth(l, rb, k, arr);
	else
		return kth(lb, r, k - (rb - l + 1), arr);
}

int main() {
    freopen("kth.in", "r", stdin);
    freopen("kth.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, k, A, B, C;
	cin >> n >> k >> A >> B >> C;

	vector <int> arr(n);
	cin >> arr[0] >> arr[1];
	for (int i = 2; i < n; i++)
		arr[i] = A * arr[i - 2] + B * arr[i - 1] + C;

	cout << kth(0, n - 1, k, arr);

	return 0;
}
