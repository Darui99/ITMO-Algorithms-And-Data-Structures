#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll inf = (ll)4e+18;

struct Node {
	Node* left;
	Node* right;
	ll lb, rb, minu, add;
	bool last, need;
};

Node* Empty = new Node{ NULL, NULL, 0, 0, inf, 0ll, false, false };

Node* build(ll l, ll r) {
	if (l == r)
		return new Node{ Empty, Empty, l, r, inf, 0ll, false, false };
	ll mid = (l + r) / 2ll;
	Node* L = build(l, mid);
	Node* R = build(mid + 1ll, r);
	return new Node{ L, R, l, r, inf, 0ll, false, false };
}

void push(Node* v) {
	if (v == Empty || !v->need)
		return;

	v->need = false;
	if (v->last == false) {
		v->minu = v->add;

		if (!v->left->need)
			v->left->need = true;
		v->left->last = false;
		v->left->add = v->add;

		if (!v->right->need)
			v->right->need = true;
		v->right->last = false;
		v->right->add = v->add;
	} else {
		v->minu += v->add;

		if (!v->left->need) {
			v->left->need = true;
			v->left->last = true;
			v->left->add = v->add;
		} else {
			v->left->add += v->add;
		}

		if (!v->right->need) {
			v->right->need = true;
			v->right->last = true;
			v->right->add = v->add;
		} else {
			v->right->add += v->add;
		}
	}
}

ll get(Node* v, ll l, ll r) {
	push(v);
	if (l > v->rb || r < v->lb)
		return inf;
	if (l <= v->lb && v->rb <= r)
		return v->minu;
	return min(get(v->left, l, r), get(v->right, l, r));
}

void update(Node* v, ll l, ll r, ll k, bool t) {
	push(v);
	if (l > v->rb || r < v->lb)
		return;
	if (l <= v->lb && v->rb <= r) {
		v->need = true;
		v->last = t;
		v->add = k;
		push(v);
		return;
	}
	update(v->left, l, r, k, t);
	update(v->right, l, r, k, t);
	v->minu = min(v->left->minu, v->right->minu);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	ll n, x, l, r;
	cin >> n;

	Node* root = build(1ll, n);

	for (ll i = 1ll; i <= n; i++) {
		cin >> x;
		update(root, i, i, x, false);
	}

	string s;
	while (cin >> s >> l >> r) {
		if (s == "min") {
			cout << get(root, l, r) << '\n';
			continue;
		}
		cin >> x;
		update(root, l, r, x, (s == "add"));
	}

	return 0;
}
