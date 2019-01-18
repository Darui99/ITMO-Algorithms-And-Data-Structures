#include <bits/stdc++.h>
using namespace std;

struct trip {
	int mod, sum, digit;

	trip() {
		this->mod = -1;
		this->sum = -1;
		this->digit = -1;
	}

	trip(int nm, int ns, int nd) {
		this->mod = nm;
		this->sum = ns;
		this->digit = nd;
	}
};

const int MAXN = 1005;
const int MAXL = (int)1e+5 + 5;
int pows[MAXL];

bool dp[MAXN][MAXN];
trip par[MAXN][MAXN];

int main() {
    freopen("number.in", "r", stdin);
    freopen("number.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, cur, mod, sum;
	cin >> n;

	if (n < 10) {
		cout << n;
		return 0;
	}

	pows[0] = 1;
	for (int i = 1; i < MAXL; i++)
		pows[i] = (pows[i - 1] * 10) % n;

	queue < pair<int, int> > q;

	for (int i = 1; i < 10; i++) {
		dp[i % n][i] = true;
		q.push(make_pair(i % n, i));
		par[i % n][i] = trip(-1, -1, i);
	}

	while (!q.empty()) {
		mod = q.front().first;
		sum = q.front().second;
		q.pop();

		for (int c = 0; c < 10; c++) {
			cur = (10 * mod + c) % n;
			if (sum + c <= n && !dp[cur][sum + c]) {
				dp[cur][sum + c] = true;
				par[cur][sum + c] = trip(mod, sum, c);
				q.push(make_pair(cur, sum + c));
			}
		}

		if (dp[0][n])
			break;
	}

	string ans = "";
	mod = 0; sum = n;
	int nm, ns;

	while (mod != -1) {
		ans.push_back((char)(par[mod][sum].digit + '0'));
		nm = par[mod][sum].mod;
		ns = par[mod][sum].sum;
		mod = nm;
		sum = ns;
	}
	reverse(ans.begin(), ans.end());
	cout << ans;
	return 0;
}
