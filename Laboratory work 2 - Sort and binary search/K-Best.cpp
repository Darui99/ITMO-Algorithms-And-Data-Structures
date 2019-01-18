#include <bits/stdc++.h>
using namespace std;

typedef double ld;

const ld eps = (ld)1e-8;

void mergeSort(int l, int r, vector <ld> &arr, vector<ld> &emp) {
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

void mergeSortPair(int l, int r, vector < pair<ld, int> > &arr, vector< pair<ld, int> > &emp) {
	if (l == r)
		return;

	int mid = (l + r) / 2;
	mergeSortPair(l, mid, arr, emp);
	mergeSortPair(mid + 1, r, arr, emp);

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

int n, k, cur;
vector <ld> a, b, arr, emp;
ld sum;

bool check(ld x) {
	for (int i = 0; i < n; i++)
		arr[i] = a[i] - x * b[i];
	mergeSort(0, n - 1, arr, emp);
	sum = (ld)0.0;
	for (int i = n - 1, step = 0; step < k; i--, step++)
		sum += arr[i];
	return (sum > eps);
}

int main() {
    freopen("kbest.in", "r", stdin);
    freopen("kbest.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> k;
	a.resize(n);
	b.resize(n);
	arr.resize(n);
	emp.resize(n);

	for (int i = 0; i < n; i++)
		cin >> a[i] >> b[i];

	ld l = 0.0, r = (ld)1e+7 + 3.0, mid;
	for (int step = 0; step < 50; step++) {
		mid = (l + r) / (ld)2.0;
		if (check(mid))
			l = mid;
		else
			r = mid;
	}

	vector < pair<ld, int> > ans(n), ansemp(n);
	for (int i = 0; i < n; i++)
		ans[i] = make_pair(a[i] - l * b[i], i);
	mergeSortPair(0, n - 1, ans, ansemp);
	for (int i = n - 1, step = 0; step < k; i--, step++)
		cout << ans[i].second + 1 << " ";

	return 0;
}
