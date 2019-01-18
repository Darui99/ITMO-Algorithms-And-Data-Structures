#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("antiqs.in", "r", stdin);
    freopen("antiqs.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	if (n == 1) {
		cout << 1;
		return 0;
	}

	vector <int> arr = { 1, 2 };
	for (int i = 3; i <= n; i++) {
		arr.push_back(i);
		swap(arr[(i - 1) / 2], arr.back());
	}

	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";

	return 0;
}
