#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef double ld;
typedef complex<ld> C;

const ld PI = (ld)acos((ld)-1.0);

vector <C> convert(const string &s) {
	vector <C> res((int)s.size() - (s[0] == '-'));
	for (int i = (int)s.size() - 1, j = 0; i >= (int)(s[0] == '-'); i--, j++)
		res[j] = (ld)(s[i] - '0');
	return res;
}

void fft(vector<C> &x) {
	int n = (int)x.size();
	if (n == 1)
		return;
	vector <C> x0(n / 2);
	vector <C> x1(n / 2);
	for (int i = 0; i < n / 2; i++) {
		x0[i] = x[2 * i];
		x1[i] = x[2 * i + 1];
	}
	fft(x0);
	fft(x1);
	ld a = (ld)2.0 * PI / (ld)n;
	C w(cos(a), sin(a)), cw = (ld)1.0;
	for (int i = 0; i < n; i++) {
		x[i] = x0[i % (n / 2)] + cw * x1[i % (n / 2)];
		cw *= w;
	}
}

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
    string as, bs;
	cin >> as >> bs;
	bool sign = (as[0] == '-') ^ (bs[0] == '-');

	vector <C> a = convert(as);
	vector <C> b = convert(bs);
	int logn = 0, n;
	while ((1 << logn) < (int)max(a.size(), b.size()))
		logn++;
	logn++;
	n = (1 << logn);
	a.resize(n);
	b.resize(n);

	fft(a);
	fft(b);
	for (int i = 0; i < n; i++)
		a[i] *= b[i];
	// inv-fft(a)
	b = a;
	fft(b);
	a[0] = b[0] / (ld)n;
	for (int i = 1; i < n; i++)
		a[i] = b[n - i] / (ld)n;


	vector <ll> res(n);
	for (int i = 0; i < n; i++) {
		res[i] += (ll)roundl(a[i].real());
		if (i + 1 < n) {
			res[i + 1] += res[i] / 10ll;
		} else {
			res.push_back(res[i] / 10ll);
		}
		res[i] %= 10ll;
	}
	while ((int)res.size() > 1 && res.back() == 0ll)
		res.pop_back();

	if (sign && res != vector<ll>(1))
		cout << "-";
	for (int i = (int)res.size() - 1; i >= 0; i--)
		cout << res[i];
	return 0;
}
