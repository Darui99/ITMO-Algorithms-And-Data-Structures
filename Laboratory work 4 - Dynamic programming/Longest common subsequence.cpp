#include <bits/stdc++.h>
using namespace std;

vector <int> lcs(const string &a, const string &b) {
	int n = (int)a.size(), m = (int)b.size();
	vector < vector<int> > dp(2, vector<int>(m + 1));
	for (int j = 1; j <= n; j++) {
		for (int i = 1; i <= m; i++) {
			if (a[j - 1] == b[i - 1])
				dp[1][i] = max(dp[1][i], dp[0][i - 1] + 1);
			dp[1][i] = max(dp[1][i], dp[0][i]);
			dp[1][i] = max(dp[1][i], dp[1][i - 1]);
		}
		dp[0].swap(dp[1]);
	}
	return dp[0];
}

string ans = "";

void getAns(const string &a, const string &b) {
	int n = (int)a.size(), m = (int)b.size();
	if (n == 1) {
		if ((int)b.find(a) != -1)
			ans += a;
		return;
	}
	vector <int> dpl = lcs(a.substr(0, n / 2), b);
	string aa = a.substr(n / 2, n - n / 2);
	vector <int> dpr = lcs(string(aa.rbegin(), aa.rend()), string(b.rbegin(), b.rend()));

	int maxu = -1, imaxu = -1;
	for (int i = 0; i <= m; i++) {
		if (maxu < dpl[i] + dpr[m - i]) {
			maxu = dpl[i] + dpr[m - i];
			imaxu = i;
		}
	}
	getAns(a.substr(0, n / 2), b.substr(0, imaxu));
	getAns(a.substr(n / 2, n - n / 2), b.substr(imaxu, m - imaxu));
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	string a, b;
	cin >> a >> b;
	getAns(a, b);
	cout << ans;
	return 0;
}
