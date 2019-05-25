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

void print(Node* v) {
	if (v == Empty)
		return;
	print(v->left);
	cout << v->key << " ";
	print(v->right);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, q, l, r;
	cin >> n >> q;

	Node* root = Empty;
	for (int i = 1; i <= n; i++) {
		Node* p = new Node{ Empty, Empty, i, rand(), 1 };
		root = merge(root, p);
	}

	while (q--) {
		cin >> l >> r;
		auto gets = split_size(root, l - 1);
		auto gets1 = split_size(gets.second, r - l + 1);
		root = merge(gets1.first, merge(gets.first, gets1.second));
	}

	print(root);
	return 0;
}
