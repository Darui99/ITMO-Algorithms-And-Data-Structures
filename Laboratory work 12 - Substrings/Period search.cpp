#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
	cin >> s;

	int n = (int)s.size(), j;

	vector <int> p(n);
	for (int i = 1; i < n; i++) {
		for (j = p[i - 1]; j && s[i] != s[j]; j = p[j - 1]) {}
		p[i] = (s[i] == s[j] ? ++j : j);
	}

	if (n % (n - p.back()) == 0) {
		cout << n - p.back();
	} else {
		cout << n;
	}
	return 0;
}
