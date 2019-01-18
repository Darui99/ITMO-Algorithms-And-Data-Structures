#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

unsigned int cur = 0, A, B;
inline unsigned int nextRand24() {
	cur = cur * A + B;
	return cur >> 8;
}

inline unsigned int nextRand32() {
	unsigned int a = nextRand24(), b = nextRand24();
	return (a << 8) ^ b;
}

ll ans = 0ll, k;

void mergeSort(int l, int r, vector <ll> &arr, vector<ll> &emp) {
	if (l == r) {
		ans += (arr[l] >= k);
		return;
	}

	int mid = (l + r) / 2, ptr = l;
	mergeSort(l, mid, arr, emp);
	mergeSort(mid + 1, r, arr, emp);


	for (int i = mid + 1; i <= r; i++) {
		while (ptr <= mid && arr[i] - arr[ptr] >= k) {
			ptr++;
		}
		ans += (ll)(ptr - l);
	}

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
    freopen("bigseg.in", "r", stdin);
    freopen("bigseg.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n >> k >> A >> B;

	vector <ll> arr(n);
	for (int i = 0; i < n; i++) {
		if (i == 0)
			arr[i] = (ll)(int)nextRand32();
		else
			arr[i] = arr[i - 1] + (ll)(int)nextRand32();
	}

	vector <ll> emp(n);
	mergeSort(0, n - 1, arr, emp);

	cout << ans;

	return 0;
}
