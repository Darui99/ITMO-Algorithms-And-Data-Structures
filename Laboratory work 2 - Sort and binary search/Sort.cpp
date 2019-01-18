#include <bits/stdc++.h>
using namespace std;

void mergeSort(int l, int r, vector <int> &arr, vector<int> &emp) {
	if (l == r)
		return;

	int mid = (l + r) / 2;
	mergeSort(l, mid, arr, emp);
	mergeSort(mid + 1, r, arr, emp);

	int n = mid - l + 1, m = r - mid;
	int ptra = l, ptrb = mid + 1;
	for (int i = 0, pos = l; i < n + m; i++, pos++) {
		if (ptra == mid + 1) {
			emp[pos] = arr[ptrb++];
			continue;
		}
		if (ptrb == r + 1) {
			emp[pos] = arr[ptra++];
			continue;
		}
		if (arr[ptra] < arr[ptrb]) {
			emp[pos] = arr[ptra++];
		} else {
			emp[pos] = arr[ptrb++];
		}
	}

	for (int i = l; i <= r; i++) {
		arr[i] = emp[i];
	}
}

int main() {
    freopen("sort.in", "r", stdin);
    freopen("sort.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	vector <int> arr(n);
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	vector <int> emp(n);
	mergeSort(0, n - 1, arr, emp);

	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";

	return 0;
}
