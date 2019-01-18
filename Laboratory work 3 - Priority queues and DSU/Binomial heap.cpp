#include <bits/stdc++.h>
using namespace std;

const int LOGN = 22;
const int MAXN = (int)1e+6 + 5;
const int inf = 2147483647;

struct Node {
	Node* par;
	Node* son[LOGN];
	pair <int, int> val;
	int rank;

	Node(Node* np, pair<int, int> nv, int nr) {
		this->par = np;
		this->val = nv;
		this->rank = nr;
		for (int i = 0; i < LOGN; i++)
			this->son[i] = nullptr;
	}
};

Node* heap[MAXN];
Node* arr[MAXN];

int getMin(int k) {
	pair <int, int> res = make_pair(inf, inf);

	for (int i = 0; i < heap[k]->rank; i++) {
		if (heap[k]->son[i] == nullptr)
			continue;
		res = min(res, heap[k]->son[i]->val);
	}

	return res.first;
}

void decreaseKey(int v, int k) {
	arr[v]->val.first = k;
	Node* cur = arr[v];
	while (cur->par != nullptr) {
		if (cur->val < cur->par->val) {
			swap(cur->val, cur->par->val);
			swap(arr[cur->val.second], arr[cur->par->val.second]);
			cur = cur->par;
		} else {
			break;
		}
	}
}

Node* add(Node* a, Node* b) {
	if (a->val < b->val) {
		a->son[a->rank] = b;
		b->par = a;
		a->rank++;
		return a;
	} else {
		b->son[b->rank] = a;
		a->par = b;
		b->rank++;
		return b;
	}
}

void merge(int ka, int kb) {
	Node* a = heap[ka];
	Node* b = heap[kb];
	Node* c = nullptr;

	for (int i = 0; i <= max(a->rank, b->rank) + 1; i++) {
		// 000
		if (a->son[i] == nullptr && b->son[i] == nullptr && c == nullptr) {
			continue;
		}
		// 001
		if (a->son[i] == nullptr && b->son[i] == nullptr && c != nullptr) {
			b->son[i] = c;
			c->par = b;
			b->rank = max(b->rank, i + 1);
			c = nullptr;
			continue;
		}
		// 010
		if (a->son[i] == nullptr && b->son[i] != nullptr && c == nullptr) {
			b->rank = max(b->rank, i + 1);
			continue;
		}
		// 011
		if (a->son[i] == nullptr && b->son[i] != nullptr && c != nullptr) {
			c = add(b->son[i], c);
			b->son[i] = nullptr;
			continue;
		}
		// 100
		if (a->son[i] != nullptr && b->son[i] == nullptr && c == nullptr) {
			b->son[i] = a->son[i];
			a->son[i]->par = b;
			b->rank = max(b->rank, i + 1);
			continue;
		}
		// 101
		if (a->son[i] != nullptr && b->son[i] == nullptr && c != nullptr) {
			c = add(a->son[i], c);
			continue;
		}
		// 110
		if (a->son[i] != nullptr && b->son[i] != nullptr && c == nullptr) {
			c = add(a->son[i], b->son[i]);
			b->son[i] = nullptr;
			continue;
		}
		// 111
		if (a->son[i] != nullptr && b->son[i] != nullptr && c != nullptr) {
			c = add(a->son[i], c);
			continue;
		}
	}

	for (int i = 0; i < a->rank; i++)
		a->son[i] = nullptr;
}

void insert(int v, int a, int num) {
	Node* h = new Node(nullptr, make_pair(-inf, -MAXN + 1), 1);
	Node* p = new Node(h, make_pair(v, num), 0);
	h->son[0] = p;

	arr[num] = p;
	heap[MAXN - 1] = h;
	merge(MAXN - 1, a);
}

void extractMin(int k) {
	Node* h = heap[k];

	pair<int, int> minu = make_pair(inf, inf);
	int iminu = -1;

	for (int i = 0; i < h->rank; i++) {
		if (h->son[i] == nullptr)
			continue;
		if (h->son[i]->val < minu) {
			minu = h->son[i]->val;
			iminu = i;
		}
	}

	Node* del = h->son[iminu];
	h->son[iminu] = nullptr;
	heap[MAXN - 1] = del;
	merge(MAXN - 1, k);
}

int getNum(int v) {
	Node* cur = arr[v];
	while (cur->par != nullptr)
		cur = cur->par;
	return -cur->val.second;
}

void erase(int k) {
	int num = getNum(k);
	decreaseKey(k, -inf);
	extractMin(num);
}

void change(int v, int k) {
	Node* cur = arr[v];
	if (k <= cur->val.first) {
		decreaseKey(v, k);
	} else {
		int numh = getNum(v);
		erase(v);
		insert(k, numh, v);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, q, numeric = 1;
	cin >> n >> q;

	for (int i = 1; i <= n; i++) {
		heap[i] = new Node(nullptr, make_pair(-inf, -i), 0);
	}

	int type, x, y, h;
	while (q--) {
		cin >> type;
		if (type == 0) {
			cin >> h >> x;
			insert(x, h, numeric);
			numeric++;
		}
		if (type == 1) {
			cin >> x >> y;
			merge(x, y);
		}
		if (type == 2) {
			cin >> x;
			erase(x);
		}
		if (type == 3) {
			cin >> x >> y;
			change(x, y);
		}
		if (type == 4) {
			cin >> h;
			cout << getMin(h) << '\n';
		}
		if (type == 5) {
			cin >> h;
			extractMin(h);
		}
	}
	return 0;
}
