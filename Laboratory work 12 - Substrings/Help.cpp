#include <bits/stdc++.h>
using namespace std;

inline int get(const string &s) {
	int n = (int)s.size();
	vector <int> z(n);
	for (int i = 1, l = 0, r = 0; i < n; i++) {
		if (i <= r)
			z[i] = min(r - i + 1, z[i - l]);
		while (i + z[i] < n && s[z[i]] == s[i + z[i]])
			z[i]++;
		if (i + z[i] - 1 > r) {
			l = i;
			r = i + z[i] - 1;
		}
	}
	return n - *max_element(z.begin(), z.end());
}

int main() {
    string s, cur = "";
	cin >> s;

	int res = 0;
	for (int i = 0; i < (int)s.size(); i++) {
		cur.push_back(s[i]);
		res += get(string(cur.rbegin(), cur.rend()));
		cout << res << '\n';
	}
	return 0;
}
