#include <bits/stdc++.h>
using namespace std;

int main() {
    string a, b, s;
	cin >> a >> b;

	s = a + "$" + b;

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

	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());

	s = a + "$" + b;
	vector <int> g(n);

	for (int i = 1, l = 0, r = 0; i < n; i++) {
		if (i <= r)
			g[i] = min(r - i + 1, g[i - l]);
		while (i + g[i] < n && s[g[i]] == s[i + g[i]])
			g[i]++;
		if (i + g[i] - 1 > r) {
			l = i;
			r = i + g[i] - 1;
		}
	}

	vector <int> ans;
	for (int i = 0; i < (int)b.size(); i++) {
		int j = (int)b.size() - i - (int)a.size();
		if (j < 0)
			break;
		if (z[(int)a.size() + 1 + i] + g[(int)a.size() + 1 + j] >= (int)a.size() - 1)
			ans.push_back(i);
	}

	cout << (int)ans.size() << '\n';
	for (int i = 0; i < (int)ans.size(); i++)
		cout << ans[i] + 1 << ' ';
	return 0;
}
