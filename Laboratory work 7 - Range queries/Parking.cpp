#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int inf = (int)1e+9 + 7;

struct Node {
	Node* left;
	Node* right;
	int lb, rb, minu;
};

Node* Empty = new Node{ NULL, NULL, 0, 0, 1 };

Node* build(int l, int r) {
	if (l == r)
		return new Node{ Empty, Empty, l, r, 0 };
	int mid = (l + r) / 2;
	Node* L = build(l, mid);
	Node* R = build(mid + 1, r);
	return new Node{ L, R, l, r, 0 };
}

int descent(Node* v) {
	if (v->lb == v->rb)
		return v->lb;
	if (v->left->minu == 0) {
		return descent(v->left);
	} else {
		return descent(v->right);
	}
}

int get(Node* v, int l, int r) {
	if (l > v->rb || r < v->lb)
		return inf;
	if (l <= v->lb && v->rb <= r) {
		if (v->minu == 0)
			return descent(v);
		return inf;
	}
	int res = get(v->left, l, r);
	return (res != inf ? res : get(v->right, l, r));
}

void update(Node* v, int pos, int k) {
	if (v->lb == v->rb) {
		v->minu = k;
		return;
	}
	if (v->left->lb <= pos && pos <= v->left->rb) {
		update(v->left, pos, k);
	} else {
		update(v->right, pos, k);
	}
	v->minu = min(v->left->minu, v->right->minu);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, m;
	cin >> n >> m;

	Node* root = build(1, n);

	string s;
	while (cin >> s >> m) {
		if (s == "exit") {
			update(root, m, 0);
		} else {
			int pos = get(root, m, n);
			pos = (pos != inf ? pos : get(root, 1, m - 1));
			update(root, pos, 1);
			cout << pos << '\n';
		}
	}

	return 0;
}
