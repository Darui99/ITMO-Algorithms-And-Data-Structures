#include <bits/stdc++.h>
using namespace std;

const int alph = 26;

struct Node {
	int next[alph];
	int p, ls, suflink;

	Node() = default;

	Node(int np, int nls) {
		for (int i = 0; i < alph; i++)
			next[i] = -1;
		p = np;
		ls = nls;
		suflink = -1;
	}
};

vector <Node> trie(1, Node(0, -1));

inline int add(const string &s) {
	int v = 0, c;
	for (int i = 0; i < (int)s.size(); i++) {
		c = (int)(s[i] - 'a');
		if (trie[v].next[c] == -1) {
			trie.push_back(Node(v, c));
			trie[v].next[c] = (int)trie.size() - 1;
		}
		v = trie[v].next[c];
	}
	return v;
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
	cin >> n;

	vector <int> num(n);

	string s;
	for (int i = 0; i < n; i++) {
		cin >> s;
		num[i] = add(s);
	}

	n = (int)trie.size();
	vector <int> ans(n);
	vector <bool> used(n);

	for (int i = 0; i < n; i++) {
		trie[i].suflink = get_suflink(i);
	}

	int q;
	cin >> q;

	while (q--) {
		int type;
		cin >> type;
		if (type == 1) {
			int v = 0;
			cin >> s;
			stack <int> h;
			for (int i = 0; i < (int)s.size(); i++) {
				v = go(v, (int)(s[i] - 'a'));
				int u = v;
				while (u > 0 && !used[u]) {
					used[u] = true;
					ans[u]++;
					h.push(u);
					u = trie[u].suflink;
				}
			}
			while (!h.empty()) {
				used[h.top()] = false;
				h.pop();
			}
		} else {
			int v;
			cin >> v;
			v--;
			cout << ans[num[v]] << '\n';
		}
	}
	return 0;
}
