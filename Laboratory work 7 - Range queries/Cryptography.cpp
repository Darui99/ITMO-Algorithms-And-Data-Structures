#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int mod;

struct mat {
	int c0, c1, c2, c3;
};

vector <mat> start;

const mat E = { 1, 0, 0, 1 };

inline mat mult(const mat &a, const mat &b) {
	mat res;
	res.c0 = (a.c0 * b.c0 + a.c1 * b.c2) % mod;
	res.c1 = (a.c0 * b.c1 + a.c1 * b.c3) % mod;
	res.c2 = (a.c2 * b.c0 + a.c3 * b.c2) % mod;
	res.c3 = (a.c2 * b.c1 + a.c3 * b.c3) % mod;
	return res;
}

struct Node {
	Node* left;
	Node* right;
	int lb, rb;
	mat arr;
};

Node* Empty = new Node{ NULL, NULL, 0, 0, E };

Node* build(int l, int r) {
	if (l == r)
		return new Node{ Empty, Empty, l, r, start[l - 1] };
	int mid = (l + r) / 2;
	Node* L = build(l, mid);
	Node* R = build(mid + 1, r);
	return new Node{ L, R, l, r, mult(L->arr, R->arr) };
}

mat get(Node* v, int l, int r) {
	if (l > v->rb || r < v->lb)
		return E;
	if (l <= v->lb && v->rb <= r)
		return v->arr;
	return mult(get(v->left, l, r), get(v->right, l, r));
}

int main() {
	scanf("%d", &mod);
	int n, q, l, r;

	scanf("%d%d", &n, &q);

	start.resize(n);
	for (int i = 0; i < n; i++) {
		scanf("%d%d%d%d", &start[i].c0, &start[i].c1, &start[i].c2, &start[i].c3);
	}

	Node* root = build(1, n);

	mat res;
	while (q--) {
		scanf("%d%d", &l, &r);
		res = get(root, l, r);
		printf("%d %d\n%d %d\n\n", res.c0, res.c1, res.c2, res.c3);
	}

	return 0;
}
