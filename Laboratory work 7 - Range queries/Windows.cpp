#include <bits/stdc++.h>
using namespace std;

struct ev {
	int l, r, t, type;
};

bool cmp(const ev &a, const ev &b) {
	return make_pair(a.t, a.type) < make_pair(b.t, b.type);
}

struct Node {
	Node* left;
	Node* right;
	int lb, rb, add;
	pair <int, int> maxu;
};

Node* Empty = new Node{ NULL, NULL, -1, -1, 0, make_pair(-1, -1) };

Node* build(int l, int r) {
	if (l == r)
		return new Node{ Empty, Empty, l, r, 0, make_pair(0, l) };
	int mid = (l + r) / 2;
	Node* L = build(l, mid);
	Node* R = build(mid + 1, r);
	return new Node{ L, R, l, r, 0, max(L->maxu, R->maxu) };
}

void push(Node* v) {
	if (v == Empty)
		return;
	v->maxu.first += v->add;
	v->left->add += v->add;
	v->right->add += v->add;
	v->add = 0;
}

pair <int, int> get(Node* v, int l, int r) {
	push(v);
	if (l > v->rb || r < v->lb)
		return make_pair(-1, -1);
	if (l <= v->lb && v->rb <= r)
		return v->maxu;
	return max(get(v->left, l, r), get(v->right, l, r));
}

void update(Node* v, int l, int r, int k) {
	push(v);
	if (l > v->rb || r < v->lb)
		return;
	if (l <= v->lb && v->rb <= r) {
		v->add += k;
		push(v);
		return;
	}
	update(v->left, l, r, k);
	update(v->right, l, r, k);
	v->maxu = max(v->left->maxu, v->right->maxu);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n;
	cin >> n;

	vector <int> numbers(2 * n);
	vector <ev> arr(2 * n);
	int x1, y1, x2, y2;

	for (int i = 0; i < n; i++) {
		cin >> x1 >> y1 >> x2 >> y2;
		arr[2 * i].l = y1;
		arr[2 * i].r = y2;
		arr[2 * i].t = x1;
		arr[2 * i].type = 0;
		arr[2 * i + 1].l = y1;
		arr[2 * i + 1].r = y2;
		arr[2 * i + 1].t = x2;
		arr[2 * i + 1].type = 1;
		numbers[2 * i] = y1;
		numbers[2 * i + 1] = y2;
	}

	sort(numbers.begin(), numbers.end());
	numbers.resize(unique(numbers.begin(), numbers.end()) - numbers.begin());

	for (int i = 0; i < (int)arr.size(); i++) {
		arr[i].l = (int)(lower_bound(numbers.begin(), numbers.end(), arr[i].l) - numbers.begin());
		arr[i].r = (int)(lower_bound(numbers.begin(), numbers.end(), arr[i].r) - numbers.begin());
	}

	sort(arr.begin(), arr.end(), cmp);

	int maxu = -1;
	pair <int, int> imaxu = make_pair(-1, -1), cur;

	Node* root = build(0, (int)numbers.size() - 1);

	for (int i = 0; i < (int)arr.size(); i++) {
		if (arr[i].type == 0) {
			update(root, arr[i].l, arr[i].r, 1);
		} else {
			update(root, arr[i].l, arr[i].r, -1);
		}
		cur = get(root, 0, (int)numbers.size() - 1);
		if (cur.first > maxu) {
			maxu = cur.first;
			imaxu = make_pair(arr[i].t, numbers[cur.second]);
		}
	}

	cout << maxu << '\n' << imaxu.first << " " << imaxu.second;

	return 0;
}
