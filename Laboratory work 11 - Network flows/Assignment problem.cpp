#include <bits/stdc++.h>
using namespace std;

const int inf = (int)1e+9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, ans = 0;
	cin >> n;

	vector < vector<int> > arr(n, vector<int>(n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cin >> arr[i][j];
	}

	vector <int> match(n, -1);
	for (int i = 0; i < n; i++) {
		int cur = *min_element(arr[i].begin(), arr[i].end());
		ans += cur;
		for (int j = 0; j < n; j++)
			arr[i][j] -= cur;

		vector <int> minu(n, inf), par(n, -1), a, b, used(n), num(n, -1), add;
		a.push_back(i);
		add.push_back(0);
		num[i] = 0;
		while (true) {
			for (int j = 0; j < n; j++) {
				if (!used[j] && arr[a.back()][j] < minu[j]) {
					minu[j] = arr[a.back()][j];
					par[j] = a.back();
				}
			}
			int cmin = inf, icmin = -1;
			for (int j = 0; j < n; j++) {
				if (!used[j] && cmin > minu[j]) {
					cmin = minu[j];
					icmin = j;
				}
			}
			add[(int)a.size() - 1] += cmin;
			for (int j = 0; j < n; j++) {
				if (!used[j])
					minu[j] -= cmin;
			}
			ans += cmin;
			if (match[icmin] == -1) {
				cur = icmin;
				while (true) {
					match[cur] = par[cur];
					if (num[par[cur]] == 0)
						break;
					cur = b[num[par[cur]] - 1];
				}
				cur = 0;
				for (int j = (int)a.size() - 1; j >= 0; j--) {
					cur += add[j];
					for (int k = 0; k < n; k++)
						arr[a[j]][k] -= cur;
				}
				cur = 0;
				for (int j = (int)b.size() - 1; j >= 0; j--) {
					cur += add[j + 1];
					for (int k = 0; k < n; k++)
						arr[k][b[j]] += cur;
				}
				break;
			} else {
				used[icmin] = true;
				b.push_back(icmin);
				a.push_back(match[icmin]);
				add.push_back(0);
				num[a.back()] = (int)a.size() - 1;
			}
		}
	}

	cout << ans << '\n';
	for (int i = 0; i < n; i++)
		cout << match[i] + 1 << " " << i + 1 << '\n';
    return 0;
}
