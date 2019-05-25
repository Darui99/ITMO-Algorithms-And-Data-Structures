#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	string have[2] = { "aa", "bB" };
	vector <string> arr;

	for (int mask = 0; mask < (1 << 10); mask++) {
		string cur = "";
		for (int i = 0; i < 10; i++) {
			cur += have[((1 << i) & mask) > 0];
		}
		arr.push_back(cur);
	}

	int n;
	cin >> n;

	for (int i = 0; i < n; i++)
		cout << arr[i] << '\n';
	return 0;
}
