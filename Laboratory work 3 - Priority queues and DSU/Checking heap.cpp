#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("isheap.in", "r", stdin);
    freopen("isheap.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	vector <long long> arr(n + 1);
	for (int i = 1; i <= n; i++)
		cin >> arr[i];

	bool flag = true;
	for (int i = 1; i <= n; i++) {
		if (2 * i <= n)
			flag &= (arr[i] <= arr[2 * i]);
		if (2 * i + 1 <= n)
			flag &= (arr[i] <= arr[2 * i + 1]);
	}

	if (flag)
		cout << "YES";
	else
		cout << "NO";

	return 0;
}
