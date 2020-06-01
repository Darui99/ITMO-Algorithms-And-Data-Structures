#include <bits/stdc++.h>
using namespace std;

inline vector <int> build_p(const string &s) {
	int n = (int)s.size(), j = 0;
	vector <int> p(n);
	for (int i = 1; i < n; i++) {
		for (; j && s[i] != s[j]; j = p[j - 1]) {}
		p[i] = (s[i] == s[j] ? ++j : j);
	}
	return p;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string s;
	cin >> s;

	int n = (int)s.size();

	vector < vector<int> > p(n);
	for (int i = 0; i < n; i++)
		p[i] = build_p(s.substr(i, n - i));

	vector < vector<int> > mss(n);
	for (int i = 0; i < n; i++) {
		mss[i].resize(p[i].size());
		for (int j = 1; j < (int)p[i].size(); j++)
			mss[i][j] = max(mss[i][j - 1], p[i][j]);
	}

	vector < vector<int> > c(n);
	for (int i = 0; i < n; i++)
		c[i].resize(p[i].size());

	for (int i = n - 1; i >= 0; i--) {
		c[i][0] = 1;
		for (int j = i - 1; j >= 0; j--)
			c[j][i - j] = c[j + 1][i - j - 1] + i - j + 1 - mss[j][i - j];
	}

	int q, l, r;
	cin >> q;

	while (q--) {
		cin >> l >> r;
		l--; r--;
		cout << c[l][r - l] << '\n';
	}
	return 0;
}
