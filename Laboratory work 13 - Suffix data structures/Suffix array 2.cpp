#include <bits/stdc++.h>
using namespace std;

vector <int> kasai(string s, vector <int> p) {
	int n = s.size();

	vector <int> num(n), lcp(n);
	for (int i = 0; i < n; i++)
		num[p[i]] = i;

	int k = 0;
	for (int i = 0; i < n; i++) {
		int now = num[i];
		if (now == n - 1) {
			k = 0;
			continue;
		}
		lcp[now] = k;
		for (int j = k; j < n; j++) {
			if (s[(i + j) % n] == s[(p[now + 1] + j) % n]) {
				lcp[now]++;
			} else {
				break;
			}
		}
		k = max(0, lcp[now] - 1);
	}
	return lcp;
}

vector <int> build_suf_arr(const string &s) {
	int n = s.size();

	vector < pair<int, int> > start(n);
	for (int i = 0; i < n; i++)
		start[i] = make_pair(s[i], i);
	sort(start.begin(), start.end());

	vector <int> c(n), cn(n), p(n), pn(n), h(n);
	int ptr = 0, num = 0;
	for (int i = 0; i < n; i++) {
		p[i] = start[i].second;
		if (start[ptr].first < start[i].first) {
			ptr = i;
			num++;
			h[num] = i;
		}
		c[p[i]] = num;
	}

	int LOGN = 1;
	while ((1 << LOGN) < n)
		LOGN++;
	for (int k = 0; k < LOGN; k++) {
		for (int i = 0; i < n; i++) {
			int v = (p[i] - (1 << k) + n) % n;
			pn[h[c[v]]] = v;
			h[c[v]]++;
		}
		ptr = 0; num = 0; h[0] = 0;
		for (int i = 0; i < n; i++) {
			auto f = make_pair(c[pn[ptr]], c[(pn[ptr] + (1 << k)) % n]);
			auto s = make_pair(c[pn[i]], c[(pn[i] + (1 << k)) % n]);
			if (f < s) {
				ptr = i;
				num++;
				h[num] = i;
			}
			cn[pn[i]] = num;
		}
		p.swap(pn);
		c.swap(cn);
	}
	return p;
}

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
    string s;
	cin >> s;
	s += "$";

	auto ans = build_suf_arr(s);
	for (int i = 1; i < (int)ans.size(); i++)
		cout << ans[i] + 1 << ' ';
	cout << '\n';

	auto lcp = kasai(s, ans);
	for (int i = 1; i < (int)lcp.size() - 1; i++)
		cout << lcp[i] << ' ';
	return 0;
}
