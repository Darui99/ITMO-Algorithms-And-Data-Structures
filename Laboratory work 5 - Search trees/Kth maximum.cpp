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
	auto gets1 = split_size(gets.second, 1);
	v = merge(gets.first, gets1.second);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int q, x, n = 0;
	char c;

	cin >> q;
	Node* root = Empty;

	while (q--) {
		cin >> c;

		if (c == '+' || c == '1') {
			if (c == '+')
				cin >> c;
			cin >> x;
			insert(root, x);
			n++;
		}
		if (c == '-') {
			cin >> c >> x;
			erase(root, x);
			n--;
		}
		if (c == '0') {
			cin >> x;
			auto gets = split_size(root, n - x);
			auto gets1 = split_size(gets.second, 1);
			cout << gets1.first->key << endl;
			root = merge(gets.first, merge(gets1.first, gets1.second));
		}
	}
	return 0;
}
