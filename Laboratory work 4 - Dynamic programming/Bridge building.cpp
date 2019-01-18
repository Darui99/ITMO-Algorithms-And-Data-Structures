#include <bits/stdc++.h>
using namespace std;

const int MAXN = 155;

int x, a, y, b, l;
int dp[MAXN][MAXN];

void clean() {
	for (int i = 0; i <= x; i++) {
		for (int j = 0; j <= y; j++) {
			dp[i][j] = -1;
		}
	}
	dp[x][y] = 0;
}

int divup(int a, int b) {
	return a / b + (a % b != 0);
}

int main() {
    freopen("bridge.in", "r", stdin);
    freopen("bridge.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> x >> a >> y >> b >> l;

	int lb = 0, rb = (int)1e+5;
	while (lb != rb) {
		clean();
		int mid = (lb + rb) / 2;
		if (mid == lb)
			mid++;
		int maxu = 0;
		for (int i = x; i >= 0; i--) {
			for (int j = y; j >= 0; j--) {
				if (dp[i][j] == -1)
					continue;
				if (i < j) {
					for (int g = i; g >= 0; g--) {
						int c = max(0, divup(mid - a * g, b));
						if (c > j)
							break;
						if (dp[i - g][j - c] < dp[i][j] + 1) {
							dp[i - g][j - c] = dp[i][j] + 1;
							maxu = max(maxu, dp[i - g][j - c]);
						}
					}
				} else {
					for (int g = j; g >= 0; g--) {
						int c = max(0, divup(mid - b * g, a));
						if (c > i)
							break;
						if (dp[i - c][j - g] < dp[i][j] + 1) {
							dp[i - c][j - g] = dp[i][j] + 1;
							maxu = max(maxu, dp[i - c][j - g]);
						}
					}
				}
			}
		}
		if (maxu >= l) {
			lb = mid;
		} else {
			rb = mid - 1;
		}
	}
	cout << lb;
	return 0;
}
