#include <bits/stdc++.h>
using namespace std;

int n, k;
vector <string> word;
unordered_map<string, int> num;
vector < vector<int> > g;

string cur;

void rec(int i) {
	if (i == k) {
		num[cur] = (int)word.size();
		word.push_back(cur);
		return;
	}
	for (int j = 0; j < n; j++) {
		cur.push_back((char)(j + '0'));
		rec(i + 1);
		cur.pop_back();
	}
}

vector < pair<int, int> > ans;

void dfs(int v) {
	while (!g[v].empty()) {
		int to = g[v].back();
		g[v].pop_back();
		dfs(to);
		ans.push_back(make_pair(v, to));
	}
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> k;

	if (k == 1) {
		for (int i = 0; i < n; i++)
			cout << i;
		return 0;
	}

	k--;
	rec(0);

	g.resize(word.size());

	for (int i = 0; i < (int)word.size(); i++) {
		for (int j = 0; j < n; j++) {
			cur = "";
			cur.push_back((char)(j + '0'));
			cur += word[i].substr(0, k - 1);
			g[num[cur]].push_back(i);
		}
	}

	for (int i = 0; i < (int)word.size(); i++) {
		if ((int)g[i].size() % 2 == 1) {
			dfs(i);
			break;
		}
	}
	dfs(0);

	for (int i = (int)ans.size() - 1; i >= 0; i--)
		cout << word[ans[i].first][0];
	cout << word[ans[0].second];
    return 0;
}
