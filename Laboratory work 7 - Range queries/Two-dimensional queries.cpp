#include <bits/stdc++.h>
using namespace std;
typedef unsigned int uint;

const uint MAXN = (1 << 17);

uint A, B, CUR = 0, start[MAXN];

inline uint nextRand17() {
	CUR = CUR * A + B;
	return CUR >> 15;
}

inline uint nextRand24() {
	CUR = CUR * A + B;
	return CUR >> 8;
}

struct Node {
	Node* left;
	Node* right;
	uint lb, rb;
	vector <uint> arr;
};

Node* Empty = new Node{ NULL, NULL, MAXN, MAXN, vector<uint>() };

Node* build(uint l, uint r) {
	if (l == r)
		return new Node{ Empty, Empty, l, r, vector<uint>(1, start[l]) };
	uint mid = (l + r) / 2;
	Node* L = build(l, mid);
	Node* R = build(mid + 1, r);
	vector <uint> curarr(L->arr.size() + R->arr.size());
	merge(L->arr.begin(), L->arr.end(), R->arr.begin(), R->arr.end(), curarr.begin());
	return new Node{ L, R, l, r, curarr };
}

uint get(Node* v, uint l, uint r, uint x, uint y) {
	if (l > v->rb || r < v->lb)
		return 0;
	if (l <= v->lb && v->rb <= r) {
		uint pl = static_cast<uint>(lower_bound(v->arr.begin(), v->arr.end(), x) - v->arr.begin());
		uint pr = static_cast<uint>(upper_bound(v->arr.begin(), v->arr.end(), y) - v->arr.begin());
		return pr - pl;
	}
	return get(v->left, l, r, x, y) + get(v->right, l, r, x, y);
}

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	uint q, l, r, x, y, sum = 0, res;
	cin >> q >> A >> B;

	for (uint i = 0; i < MAXN; i++)
		start[i] = nextRand24();

	Node* root = build(0, MAXN - 1);

	while (q--) {
		l = nextRand17();
		r = nextRand17();
		if (l > r)
			swap(l, r);
		x = nextRand24();
		y = nextRand24();
		if (x > y)
			swap(x, y);
		res = get(root, l, r, x, y);
		B += res;
		sum += res;
	}

	cout << sum;

	return 0;
}
