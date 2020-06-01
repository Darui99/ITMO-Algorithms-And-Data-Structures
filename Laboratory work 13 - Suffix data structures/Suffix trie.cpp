#include <bits/stdc++.h>
using namespace std;

const int alph = 26;

struct Node {
	int next[alph];

	Node() {
		for (int i = 0; i < alph; i++)
			next[i] = -1;
	}
};
vector <Node> trie(1, Node());

inline void add(const string &s) {
	int v = 0;
	for (int i = 0; i < (int)s.size(); i++) {
		int c = (int)(s[i] - 'a');
		if (trie[v].next[c] == -1) {
			trie[v].next[c] = (int)trie.size();
			trie.emplace_back();
		}
		v = trie[v].next[c];
	}
}

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
    string s;
	cin >> s;

	for (int i = 0; i < (int)s.size(); i++)
		add(s.substr(i, (int)s.size() - i));

	cout << (int)trie.size() << ' ' << (int)trie.size() - 1 << '\n';
	for (int i = 0; i < (int)trie.size(); i++) {
		for (int j = 0; j < alph; j++) {
			if (trie[i].next[j] != -1) {
				cout << i + 1 << ' ' << trie[i].next[j] + 1 << ' ' << (char)(j + 'a') << '\n';
			}
		}
	}
	return 0;
}
