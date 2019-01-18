#include <bits/stdc++.h>
using namespace std;

const int MAXN = 16;
const int LOGN = 4;

vector < vector< pair<int, int> > > network, ans;

void add(int l, int r, int layer) {
	if ((int)network.size() - 1 < layer)
		network.push_back(vector< pair<int, int> >());
	network[layer].push_back(make_pair(l, r));
}

void buildBitonicSorter(int l, int r, int layer) {
	if (l == r)
		return;
	int n = r - l + 1, mid = (l + r) / 2;
	for (int i = 0; i < n / 2; i++)
		add(l + i, l + i + n / 2, layer);
	buildBitonicSorter(l, mid, layer + 1);
	buildBitonicSorter(mid + 1, r, layer + 1);
}

void buildMerger(int l, int r, int layer) {
	int n = r - l + 1, mid = (l + r) / 2;
	for (int i = 0; i < n / 2; i++)
		add(l + i, r - i, layer);
	buildBitonicSorter(l, mid, layer + 1);
	buildBitonicSorter(mid + 1, r, layer + 1);
}

int main() {
    // freopen("garland.in", "r", stdin);
    // freopen("garland.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	for (int i = 1; i <= LOGN; i++) {
		int curLayer = (int)network.size();
		for (int j = 1; j + (1 << i) - 1 <= MAXN; j += (1 << i))
			buildMerger(j, j + (1 << i) - 1, curLayer);
	}

	int cntCmp = 0;
	for (int i = 0; i < (int)network.size(); i++) {
		vector< pair<int, int> > cur;
		for (int j = 0; j < (int)network[i].size(); j++) {
			if (network[i][j].first <= n && network[i][j].second <= n) {
				cur.push_back(network[i][j]);
				cntCmp++;
			}
		}
		if (!cur.empty())
			ans.push_back(cur);
	}

	cout << n << " " << cntCmp << " " << (int)ans.size() << endl;
	for (int i = 0; i < (int)ans.size(); i++) {
		cout << (int)ans[i].size() << " ";
		for (int j = 0; j < (int)ans[i].size(); j++) {
			cout << ans[i][j].first << " " << ans[i][j].second << " ";
		}
		cout << endl;
	}

	return 0;
}
