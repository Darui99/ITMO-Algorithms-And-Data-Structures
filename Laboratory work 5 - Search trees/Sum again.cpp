#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = (ll)1e+9;

struct Node {
	Node* left;
	Node* right;
	ll key, pr, sum;
};
Node* Empty = new Node{ NULL, NULL, 0ll, 0ll, 0ll };
Node* root = Empty;

void update(Node* v) {
	if (v == Empty)
		return;
	v->sum = v->left->sum + v->right->sum + v->key;
}

pair <Node*, Node*> split(Node* v, ll k) {
	if (v == Empty)
		return make_pair(Empty, Empty);

	if (v->key > k) {
		auto gets = split(v->left, k);
		Node* l = gets.first;
		Node* r = gets.second;
		v->left = r;
		update(l);
		update(v);
		return make_pair(l, v);
	} else {
		auto gets = split(v->right, k);
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

bool contains(Node* v, ll k) {
	if (v == Empty)
		return false;
	if (v->key == k)
		return true;
	if (v->key < k) {
		return contains(v->right, k);
	} else {
		return contains(v->left, k);
	}
}

void insert(ll k) {
	auto gets = split(root, k);
	Node* p = new Node{ Empty, Empty, k, rand(), k };
	root = merge(merge(gets.first, p), gets.second);
}

ll get(ll l, ll r) {
	auto gets = split(root, l - 1ll);
	auto gets1 = split(gets.second, r);
	ll res = gets1.first->sum;
	root = merge(gets.first, merge(gets1.first, gets1.second));
	return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	ll q, x, prev = 0ll, l, r;
	char c;
	cin >> q;

	while (q--) {
		cin >> c;
		if (c == '+') {
			cin >> x;
			x = (x + prev) % mod;
			if (!contains(root, x))
				insert(x);
			prev = 0ll;
		} else {
			cin >> l >> r;
			x = get(l, r);
			cout << x << endl;
			prev = x;
		}
	}
	return 0;
}
