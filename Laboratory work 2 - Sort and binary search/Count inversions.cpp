#include <bits/stdc++.h>
using namespace std;

unsigned int cur = 0, A, B;
unsigned int nextRand24() {
	cur = cur * A + B;
	return cur >> 8;
}

long long ans = 0ll;

void mergeSort(int l, int r, vector <unsigned int> &arr, vector<unsigned int> &emp) {
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
			ans += (long long)(i - (ptra - l));
			emp[pos] = arr[ptra++];
			continue;
		}
		if (arr[ptra] <= arr[ptrb]) {
			ans += (long long)(i - (ptra - l));
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
    freopen("invcnt.in", "r", stdin);
    freopen("invcnt.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, m;
	cin >> n >> m >> A >> B;

	vector <unsigned int> arr(n);
	for (int i = 0; i < n; i++)
		arr[i] = nextRand24() % m;

	vector <unsigned int> emp(n);
	mergeSort(0, n - 1, arr, emp);
	cout << ans;

	return 0;
}
