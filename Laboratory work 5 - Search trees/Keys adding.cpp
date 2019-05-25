#include <bits/stdc++.h>
using namespace std;

struct Node {
	Node* left;
	Node* right;
	int key, pr, size;
};
Node* Empty = new Node{ NULL, NULL, 0, 0, 0 };

void update(Node* v) {
	if (v == Empty)
		return;
	v->size = v->left->size + v->right->size + 1;
}

pair <Node*, Node*> split_key(Node* v, int k) {
	if (v == Empty)
		return make_pair(Empty, Empty);

	if (v->key > k) {
		auto gets = split_key(v->left, k);
		Node* l = gets.first;
		Node* r = gets.second;
		v->left = r;
		update(l);
		update(v);
		return make_pair(l, v);
	} else {
		auto gets = split_key(v->right, k);
		Node* l = gets.first;
		Node* r = gets.second;
		v->right = l;
		update(v);
		update(r);
		return make_pair(v, r);
	}
}

pair <Node*, Node*> split_size(Node* v, int k) {
	if (v == Empty)
		return make_pair(Empty, Empty);

	if (v->left->size >= k) {
		auto gets = split_size(v->left, k);
		Node* l = gets.first;
		Node* r = gets.second;
		v->left = r;
		update(l);
		update(v);
		return make_pair(l, v);
	} else {
		auto gets = split_size(v->right, k - v->left->size - 1);
		Node* l = gets.first;
		Node* r = gets.second;
		v->right = l;
		update(v);
		update(r);
		return make_pair(v, r);
	}
}

Node* merge(Node* l, Node* r) {
	if (l == Empty) {
		update(r);
		return r;
	}
	if (r == Empty) {
		update(l);
		return l;
	}

	if (l->pr > r->pr) {
		l->right = merge(l->right, r);
		update(l);
		return l;
	} else {
		r->left = merge(l, r->left);
		update(r);
		return r;
	}
}

void insert(Node* &v, int k) {
	auto gets = split_key(v, k);
	Node* p = new Node{ Empty, Empty, k, rand(), k };
	v = merge(merge(gets.first, p), gets.second);
}

void erase(Node* &v, int k) {
	auto gets = split_key(v, k - 1);
	auto gets1 = split_key(gets.second, k);
	v = merge(gets.first, gets1.second);
}

int findNext(Node* v, int k) {
	auto gets = split_key(v, k - 1);
	auto gets1 = split_size(gets.second, 1);
	int res = gets1.first->key;
	v = merge(gets.first, merge(gets1.first, gets1.second));
	return res;
}

vector <int> ans;

void gen(Node* v) {
	if (v == Empty)
		return;
	gen(v->left);
	ans.push_back(v->key);
	gen(v->right);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, m, x;
	cin >> n >> m;

	Node* zero = Empty;
	Node* root = Empty;

	for (int i = 1; i <= 3 * max(n, m); i++) {
		insert(zero, i);
		Node* p = new Node{ Empty, Empty, 0, rand(), 1 };
		root = merge(root, p);
	}

	for (int i = 1; i <= n; i++) {
		cin >> x;

		int pos = findNext(zero, x);
		erase(zero, pos);

		auto gets = split_size(root, pos);
		auto gets1 = split_size(gets.first, x - 1);
		auto gets2 = split_size(gets1.second, pos - x);
		gets2.second->key = i;
		root = merge(gets1.first, merge(gets2.second, merge(gets2.first, gets.second)));
	}

	gen(root);
	while (ans.back() == 0)
		ans.pop_back();

	cout << (int)ans.size() << endl;
	for (int i = 0; i < (int)ans.size(); i++)
		cout << ans[i] << " ";
	return 0;
}
