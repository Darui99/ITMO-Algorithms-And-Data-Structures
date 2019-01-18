#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void mergeSort(int l, int r, vector <ll> &arr, vector<ll> &emp) {
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
		if (arr[ptra] > arr[ptrb]) {
			emp[pos] = arr[ptra++];
		} else {
			emp[pos] = arr[ptrb++];
		}
	}

	for (int i = l; i <= r; i++) {
		arr[i] = emp[i];
	}
}

struct trip {
	ll a, b, t;
};

ll n, m, p;
vector <trip> arr;

bool check(ll x) {
	vector <ll> can;
	ll cur, sum = 0ll;
	for (int i = 0; i < n; i++) {
		if (x - arr[i].b - arr[i].t < 0ll)
			continue;
		if (arr[i].a == 0ll)
			cur = p;
		else
			cur = (x - arr[i].b - arr[i].t) / arr[i].a;
		can.push_back(cur);
	}

	if ((int)can.size() == 0)
		return false;
	vector <ll> emp((int)can.size());
	mergeSort(0, (int)can.size() - 1, can, emp);

	for (int i = 0; i < min((ll)can.size(), m); i++)
		sum += can[i];

	if (sum >= p)
		return true;
	else
		return false;
}

int main() {
    freopen("supermarket.in", "r", stdin);
    freopen("supermarket.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n;
	arr.resize(n);
	for (int i = 0; i < n; i++)
		cin >> arr[i].a >> arr[i].b >> arr[i].t;
	cin >> m >> p;
	if (p == 0ll) {
		cout << 0;
		return 0;
	}

	ll l = 0ll, r = (ll)1e+15;
	while (l != r) {
		ll mid = (l + r) / 2ll;
		if (check(mid))
			r = mid;
		else
			l = mid + 1ll;
	}
	cout << l;

	return 0;
}
