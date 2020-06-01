#include <bits/stdc++.h>
using namespace std;

const int alph = 26;

struct Node {
	int next[alph];
	int p, ls, suflink;
	bool term;
	vector <int> nums;

	Node() = default;

	Node(int np, int nls) {
		for (int i = 0; i < alph; i++)
			next[i] = -1;
		p = np;
		ls = nls;
		suflink = -1;
		term = false;
	}
};

vector <Node> trie(1, Node(0, -1));

inline void add(const string &s, int num) {
	int v = 0, c;
	for (int i = 0; i < (int)s.size(); i++) {
		c = (int)(s[i] - 'a');
		if (trie[v].next[c] == -1) {
			trie.push_back(Node(v, c));
			trie[v].next[c] = (int)trie.size() - 1;
		}
		v = trie[v].next[c];
	}
	trie[v].term = true;
	trie[v].nums.push_back(num);
}

int get_suflink(int v) {
	if (trie[v].suflink != -1)
		return trie[v].suflink;
	if (trie[v].p == 0)
		return 0;

	int cur = get_suflink(trie[v].p);
	while (cur > 0 && trie[cur].next[trie[v].ls] == -1)
		cur = get_suflink(cur);
	return (trie[cur].next[trie[v].ls] == -1 ? 0 : trie[cur].next[trie[v].ls]);
}

inline int go(int v, int c) {
	while (v > 0 && trie[v].next[c] == -1)
		v = trie[v].suflink;
	return (trie[v].next[c] == -1 ? 0 : trie[v].next[c]);
}

vector <bool> ans, calced;
string anss[2] = { "NO", "YES" };

void calc(int v) {
	if (calced[v])
		return;
	calced[v] = true;
	if (trie[v].term) {
	    for (int i = 0; i < (int)trie[v].nums.size(); i++)
		ans[trie[v].nums[i]] = true;
	}
	calc(trie[v].suflink);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
	cin >> n;

	string s;
	for (int i = 0; i < n; i++) {
		cin >> s;
		add(s, i);
	}
	ans.resize(n);

	n = (int)trie.size();
	calced.resize(n);
	cin >> s;

	for (int i = 0; i < n; i++)
		trie[i].suflink = get_suflink(i);

	int v = 0;
	for (int i = 0; i < (int)s.size(); i++) {
		v = go(v, (int)(s[i] - 'a'));
		calc(v);
	}

	for (int i = 0; i < (int)ans.size(); i++)
		cout << anss[ans[i]] << '\n';
	return 0;
}
