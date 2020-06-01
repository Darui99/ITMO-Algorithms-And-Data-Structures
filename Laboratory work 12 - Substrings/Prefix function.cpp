#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
	cin >> s;

	int n = (int)s.size(), j = 0;

	vector <int> p(n);
	for (int i = 1; i < n; i++) {
		for (; j && s[i] != s[j]; j = p[j - 1]) {}
		p[i] = (s[i] == s[j] ? ++j : j);
	}

	for (int i = 0; i < n; i++)
		cout << p[i] << ' ';
	return 0;
}
