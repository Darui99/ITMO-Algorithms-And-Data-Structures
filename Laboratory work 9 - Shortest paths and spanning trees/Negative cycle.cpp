#include <bits/stdc++.h>
using namespace std;

const int inf = (int)1e+9;
const int MAXN = 255;

int g[MAXN][MAXN];
int par[MAXN][MAXN];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> g[i][j];
			if (g[i][j] != inf)
				par[i][j] = j;
		}
	}

	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (g[i][k] == inf || g[k][j] == inf) {
					continue;
				}
				if (g[i][j] > g[i][k] + g[k][j]) {
					g[i][j] = g[i][k] + g[k][j];
					par[i][j] = par[i][k];
				}
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				if (g[i][k] != inf && g[k][j] != inf && g[k][k] < 0) {
					cout << "YES\n";
					vector <int> num(n, -1), path;
					int cur = k;
					while (true) {
						num[cur] = (int)path.size();
						path.push_back(cur);
						cur = par[cur][k];
						if (num[cur] != -1) {
							cout << (int)path.size() - num[cur] + 1 << '\n';
							for (int t = num[cur]; t < (int)path.size(); t++)
								cout << path[t] + 1 << " ";
							cout << cur + 1;
							return 0;
						}
					}
				}
			}
		}
	}
	cout << "NO";

	return 0;
}
