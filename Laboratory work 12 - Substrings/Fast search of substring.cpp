#include <bits/stdc++.h>
using namespace std;

int main() {
    string a, b, s;
	cin >> a >> b;

	s = a + "$" + b;

	int n = (int)s.size(), j;

	vector <int> p(n), ans;

	for (int i = 1; i < n; i++) {
		for (j = p[i - 1]; j && s[i] != s[j]; j = p[j - 1]) {}
		p[i] = (s[i] == s[j] ? ++j : j);
		if (p[i] == (int)a.size())
			ans.push_back(i - 2 * (int)a.size());
	}

	cout << (int)ans.size() << '\n';
	for (int i = 0; i < (int)ans.size(); i++)
		cout << ans[i] + 1 << ' ';
	return 0;
}
