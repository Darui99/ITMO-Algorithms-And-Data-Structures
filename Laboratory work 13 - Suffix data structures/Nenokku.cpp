#include <bits/stdc++.h>
using namespace std;

const int alph = 26;

struct Node {
	vector<int> next;
	int p, suflink, l, h;

	Node(int np, int nh, int nl) {
		next.resize(alph, -1);
		p = np;
		suflink = -1;
		l = nl;
		h = nh;
	}
};
vector <Node> trie(1, Node(0, 0, -1));

string s;

inline bool is_go(int v, int f, int c) {
	if (trie[v].h == f) {
		return (trie[v].next[c] != -1);
	} else {
		int dif = f - trie[trie[v].p].h;
		return ((int)(s[trie[v].l + dif] - 'a') == c);
	}
}

inline void go(int &v, int &f, int c) {
	if (trie[v].h == f)
		v = trie[v].next[c];
	f++;
}

inline void ukkonen() {
	int v = 0, f = 0;
	for (int i = 0; i < (int)s.size(); i++) {
		int c = (int)(s[i] - 'a');
		int prev = -1;
		bool flag = true;
		while (!is_go(v, f, c)) {
			if (v == 0) {
				trie[v].next[c] = (int)trie.size();
				trie.push_back(Node(v, (int)s.size() - i, i));
				flag = false;
				break;
			}
			int dif = f - trie[trie[v].p].h;
			int pc = (int)(s[trie[v].l + dif] - 'a');
			if (trie[v].h != f) {
				trie.push_back(Node(trie[v].p, f, trie[v].l));
				trie[v].p = (int)trie.size() - 1;
				trie[v].l += dif;
				trie.back().next[pc] = v;
				v = trie[v].p;
				trie[trie[v].p].next[(int)(s[trie[v].l] - 'a')] = v;
			}
			trie[v].next[c] = (int)trie.size();
			trie.push_back(Node(v, trie[v].h + (int)s.size() - i, i));
			if (prev != -1)
				trie[prev].suflink = v;
			prev = v;

			int u, st;
			if (trie[v].p == 0) {
				u = 0;
				f = 0;
				st = 1;
			} else {
				u = trie[trie[v].p].suflink;
				f = trie[u].h;
				st = 0;
			}
			for (int j = st; j < dif; j++) {
				int cc = (int)(s[trie[v].l + j] - 'a');
				go(u, f, cc);
			}
			v = u;
		}
		if (prev != -1)
			trie[prev].suflink = v;
		if (flag)
			go(v, f, c);
	}
}

void to_lower_case(string &s) {
	for (int i = 0; i < (int)s.size(); i++) {
		if ('A' <= s[i] && s[i] <= 'Z')
			s[i] = (char)((int)s[i] - 'A' + 'a');
	}
}

string ans[2] = { "NO\n", "YES\n" };

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    char type;
	string ss;
	vector <pair<string, int>> arr;

	while (cin >> type >> ss) {
		to_lower_case(ss);
		if (type == 'A') {
			s += ss;
		} else {
			arr.push_back(make_pair(ss, (int)s.size()));
		}
	}

	ukkonen();
	for (int i = 0; i < (int)arr.size(); i++) {
		bool flag = true;
		int v = 0, f = 0;
		for (int j = 0; j < (int)arr[i].first.size(); j++) {
			int c = (int)(arr[i].first[j] - 'a');
			if (is_go(v, f, c)) {
				go(v, f, c);
			} else {
				flag = false;
				break;
			}
		}
		int pos = trie[v].l + f - trie[trie[v].p].h - 1;
		flag &= (pos < arr[i].second);
		cout << ans[flag];
	}
    return 0;
}
