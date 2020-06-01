#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector <int> kasai(const string &s, const vector <int> &p) {
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

const int LOGN = 18;
const int MAXN = (int)2e+5 + 5;

int pows[MAXN], d[LOGN][MAXN];

inline void build_ST(const vector<int> &arr) {
	for (int i = 2; i < MAXN; i++)
		pows[i] = pows[i / 2] + 1;

	int n = (int)arr.size();
	for (int i = 0; i < n; i++)
		d[0][i] = arr[i];

	int p = 1;
	for (int i = 1; i < LOGN; i++) {
		for (int j = 0; j + p < n; j++)
			d[i][j] = min(d[i - 1][j], d[i - 1][j + p]);
		p *= 2;
	}
}

inline int get(int l, int r) {
	int cur_pow = pows[r - l + 1], cur_len = (1 << cur_pow);
	return min(d[cur_pow][l], d[cur_pow][r - cur_len + 1]);
}

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
    string s;
	cin >> s;

	reverse(s.begin(), s.end());
	s += "$";

	vector <int> p = build_suf_arr(s);
	vector <int> lcp = kasai(s, p);
	vector <int> num(p.size());
	for (int i = 0; i < (int)num.size(); i++)
		num[p[i]] = i;

	build_ST(lcp);
	ll ans = 0ll;

	set <int> q;
	for (int i = (int)s.size() - 2; i >= 0; i--) {
		ans += (ll)((int)s.size() - i - 1);
		int maxu = 0;
		auto it = q.lower_bound(num[i]);
		if (it != q.end()) {
			maxu = max(maxu, get(num[i], *it - 1));
		}
		if (it != q.begin()) {
			it--;
			maxu = max(maxu, get(*it, num[i] - 1));
		}
		ans -= (ll)maxu;
		q.insert(num[i]);
		cout << ans << '\n';
	}
	return 0;
}
