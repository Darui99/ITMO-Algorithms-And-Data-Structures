#include <bits/stdc++.h>
using namespace std;

struct Node {
	Node* left;
	Node* right;
	Node* par;
	Node* link;
	int size, pr, ver;
	bool rev;
};

Node* Empty = new Node{ NULL, NULL, NULL, NULL, 0, 0, 0, false };

void push(Node* v) {
	if (v == Empty || !v->rev)
		return;
	swap(v->left, v->right);
	v->left->rev ^= true;
	v->right->rev ^= true;
	v->rev = false;
}

void update(Node* v) {
	if (v == Empty)
		return;
	v->size = v->left->size + v->right->size + 1;
}

pair<Node*, Node*> split(Node* v, int k) {
	push(v);
	if (v == Empty)
		return make_pair(Empty, Empty);
	if (v->left->size >= k) {
		auto gets = split(v->left, k);
		Node* l = gets.first;
		Node* r = gets.second;
		v->left = r;
		if (l != Empty)
			l->par = nullptr;
		if (r != Empty)
			r->par = v;
		update(v);
		return make_pair(l, v);
	} else {
		auto gets = split(v->right, k - v->left->size - 1);
		Node* l = gets.first;
		Node* r = gets.second;
		v->right = l;
		if (r != Empty)
			r->par = nullptr;
		if (l != Empty)
			l->par = v;
		update(v);
		return make_pair(v, r);
	}
}

Node* merge(Node* l, Node* r) {
	push(l);
	push(r);
	if (l == Empty) {
		update(r);
		return r;
	}
	if (r == Empty) {
		update(l);
		return l;
	}
	if (l->pr > r->pr) {
		Node* gets = merge(l->right, r);
		l->right = gets;
		if (gets != Empty)
			gets->par = l;
		update(l);
		return l;
	} else {
		Node* gets = merge(l, r->left);
		r->left = gets;
		if (gets != Empty)
			gets->par = r;
		update(r);
		return r;
	}
}

inline void relax(Node* v) {
	stack <Node*> q;
	Node* cur = v;
	while (true) {
		q.push(cur);
		if (cur->par == nullptr)
			break;
		cur = cur->par;
	}
	while (!q.empty()) {
		push(q.top());
		q.pop();
	}
}

inline int get_pos(Node* v) {
	relax(v);
	int pos = 0;
	Node* cur = v;
	if (cur->par == nullptr) {
		pos = cur->left->size + 1;
	} else {
		Node* prev;
		pos = cur->left->size;
		while (cur->par != nullptr) {
			prev = cur;
			cur = cur->par;
			if (cur->left != prev) {
				pos += cur->left->size;
				pos++;
			}
		}
		pos++;
	}
	return pos;
}

inline Node* get_root(Node* v) {
	Node* cur = v;
	while (cur->par != nullptr)
		cur = cur->par;
	return cur;
}

void expose(Node* v) {
	Node* nlink = get_root(v)->link;
	int pos = get_pos(v);
	auto gets = split(get_root(v), pos);
	if (gets.second != Empty)
		gets.second->link = v;
	Node* cur = gets.first;
	cur->link = nlink;

	while (true) {
		Node* up = cur->link;
		if (up == nullptr)
			break;
		nlink = get_root(up)->link;
		pos = get_pos(up);
		gets = split(get_root(up), pos);
		if (gets.second != Empty)
			gets.second->link = up;
		cur->link = nullptr;
		gets.first->link = nullptr;
		cur = merge(gets.first, cur);
		cur->link = nlink;
	}
}

void change_root(Node* v) {
	expose(v);
	get_root(v)->rev = true;
	swap(v->link, get_root(v)->link);
}

int lca(Node* v, Node* u) {
	expose(v);
	expose(u);
	Node* res = get_root(v)->link;
	if (res == nullptr) {
		return v->ver;
	} else {
		return res->ver;
	}
}

vector < vector<int> > g;
vector <int> w, next_ver;
vector <Node*> ptr;

inline void refresh(int n) {
	g.clear();
	w.clear();
	next_ver.clear();
	ptr.clear();

	g.resize(n);
	w.resize(n);
	next_ver.resize(n, -1);
	ptr.resize(n);
}

void dfs(int v, int p) {
	w[v] = 1;
	for (int i = 0; i < (int)g[v].size(); i++) {
		int to = g[v][i];
		if (to == p)
			continue;
		dfs(to, v);
		w[v] += w[to];
	}

	int maxu = -1, imaxu = -1;
	for (int i = 0; i < (int)g[v].size(); i++) {
		int to = g[v][i];
		if (to == p)
			continue;
		if (w[to] > maxu) {
			maxu = w[to];
			imaxu = to;
		}
	}
	if (imaxu != -1)
		next_ver[v] = imaxu;
}

void build(int v, int p, Node* path) {
	ptr[v] = new Node{ Empty, Empty, NULL, NULL, 1, rand(), v + 1, false };
	path = merge(path, ptr[v]);
	for (int i = 0; i < (int)g[v].size(); i++) {
		int to = g[v][i];
		if (to == p)
			continue;
		if (to == next_ver[v]) {
			build(to, v, path);
		} else {
			build(to, v, Empty);
			get_root(ptr[to])->link = ptr[v];
		}
	}
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    while (true) {
		int n, a, b, q;
		cin >> n;
		if (n == 0)
			break;
		refresh(n);

		for (int i = 0; i < n - 1; i++) {
			cin >> a >> b;
			a--; b--;
			g[a].push_back(b);
			g[b].push_back(a);
		}

		dfs(0, 0);
		build(0, 0, Empty);

		cin >> q;
		char type;
		while (q--) {
			cin >> type;
			if (type == '?') {
				cin >> a >> b;
				cout << lca(ptr[a - 1], ptr[b - 1]) << '\n';
			} else {
				cin >> a;
				change_root(ptr[a - 1]);
			}
		}
	}
    return 0;
}
