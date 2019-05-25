#include <bits/stdc++.h>
using namespace std;

struct Node {
	Node* left;
	Node* right;
	Node* par;
	int key, h;
};
Node* Empty = new Node{ NULL, NULL, NULL, 0, 0 };
Node* root = Empty;

void update(Node* v) {
	if (v == Empty)
		return;
	v->h = max(v->left->h, v->right->h) + 1;
}

void smallLeftRotate(Node* v) {
	Node* par = v->par;
	Node* a = v;
	Node* b = v->right;
	a->right = b->left;
	b->left->par = a;
	b->left = a;
	a->par = b;
	b->par = par;
	if (par->key < b->key) {
		par->right = b;
	} else {
		par->left = b;
	}
	update(a);
	update(b);
	v = b;
}

void smallRightRotate(Node* v) {
	Node* par = v->par;
	Node* a = v;
	Node* b = v->left;
	a->left = b->right;
	b->right->par = a;
	b->right = a;
	a->par = b;
	b->par = par;
	if (par->key < b->key) {
		par->right = b;
	} else {
		par->left = b;
	}
	update(a);
	update(b);
	v = b;
}

void bigLeftRotate(Node* v) {
	Node* par = v->par;
	Node* a = v;
	Node* b = v->right;
	Node* c = v->right->left;
	b->left = c->right;
	c->right->par = b;
	a->right = c->left;
	c->left->par = a;
	c->left = a;
	a->par = c;
	c->right = b;
	b->par = c;
	c->par = par;
	if (par->key < c->key) {
		par->right = c;
	} else {
		par->left = c;
	}
	update(a);
	update(b);
	update(c);
	v = c;
}

void bigRightRotate(Node* v) {
	Node* par = v->par;
	Node* a = v;
	Node* b = v->left;
	Node* c = v->left->right;
	b->right = c->left;
	c->left->par = b;
	a->left = c->right;
	c->right->par = a;
	c->left = b;
	b->par = c;
	c->right = a;
	a->par = c;
	c->par = par;
	if (par->key < c->key) {
		par->right = c;
	} else {
		par->left = c;
	}
	update(a);
	update(b);
	update(c);
	v = c;
}

void rotate(Node* v) {
	if (v->left->h > v->right->h) {
		if (v->left->right->h > v->left->left->h) {
			bigRightRotate(v);
		} else {
			smallRightRotate(v);
		}
	} else {
		if (v->right->left->h > v->right->right->h) {
			bigLeftRotate(v);
		} else {
			smallLeftRotate(v);
		}
	}
}

void balancing(Node* v) {
	update(v);

	if (abs(v->left->h - v->right->h) >= 2) {
		rotate(v);
	}
	if (abs(v->left->h - v->right->h) == 0 || v == root) {
		while (root->par != Empty)
			root = root->par;
		return;
	}
	balancing(v->par);
}

pair <Node*, Node*> get(Node* v, Node* par, int k) {
	if (v->key == k || v == Empty)
		return make_pair(v, par);
	if (v->key < k) {
		return get(v->right, v, k);
	} else {
		return get(v->left, v, k);
	}
}

void insert(int k) {
	Node* place = get(root, Empty, k).first;
	place->par = get(root, Empty, k).second;
	if (place != Empty)
		return;
	Node* p = new Node{ Empty, Empty, Empty, k, 1 };
	if (root == Empty) {
		root = p;
		return;
	}
	if (place->par->key < k) {
		place->par->right = p;
		p->par = place->par;
	} else {
		place->par->left = p;
		p->par = place->par;
	}
	balancing(p->par);
}

Node* next(Node* v) {
	Node* cur;
	if (v->right != Empty) {
		cur = v->right;
		while (cur->left != Empty)
			cur = cur->left;
		return cur;
	}
	cur = v;
	while (cur->par != Empty) {
		if (cur->par->right == cur) {
			cur = cur->par;
		} else {
			return cur->par;
		}
	}
	return Empty;
}

Node* prev(Node* v) {
	Node* cur;
	if (v->left != Empty) {
		cur = v->left;
		while (cur->right != Empty)
			cur = cur->right;
		return cur;
	}
	cur = v;
	while (cur->par != Empty) {
		if (cur->par->left == cur) {
			cur = cur->par;
		} else {
			return cur->par;
		}
	}
	return Empty;
}

void eraseWithoutChildren(Node* p) {
	if (p->par == Empty) {
		if (p->left == Empty && p->right == Empty) {
			root = Empty;
		} else {
			if (p->left != Empty) {
				root = p->left;
			} else {
				root = p->right;
			}
			root->par = Empty;
			balancing(root);
		}
		delete p;
		return;
	}
	if (p->par->key < p->key) {
		if (p->left != Empty) {
			p->par->right = p->left;
			p->left->par = p->par;
		} else {
			p->par->right = p->right;
			p->right->par = p->par;
		}
	} else {
		if (p->left != Empty) {
			p->par->left = p->left;
			p->left->par = p->par;
		} else {
			p->par->left = p->right;
			p->right->par = p->par;
		}
	}
	balancing(p->par);
	delete p;
}

void erase(int k) {
	Node* p = get(root, Empty, k).first;
	if (p == Empty)
		return;
	if (p->left == Empty || p->right == Empty) {
		eraseWithoutChildren(p);
		return;
	}
	Node* g = next(p);
	int key = g->key;
	eraseWithoutChildren(g);
	p->key = key;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    string s;
	int x;
	while (cin >> s >> x) {
		if (s == "insert")
			insert(x);
		if (s == "delete")
			erase(x);
		if (s == "exists") {
			if (get(root, Empty, x).first != Empty) {
				cout << "true\n";
			} else {
				cout << "false\n";
			}
		}
		if (s == "next") {
			if (root == Empty) {
				cout << "none\n";
				continue;
			}
			auto gets = get(root, Empty, x);
			Node* cur = gets.first;
			cur->par = gets.second;
			if (cur == Empty) {
				if (cur->par->key > x) {
					cout << cur->par->key << endl;
					continue;
				}
				cur = cur->par;
			}
			cur = next(cur);
			if (cur == Empty) {
				cout << "none\n";
			} else {
				cout << cur->key << endl;
			}
		}
		if (s == "prev") {
			if (root == Empty) {
				cout << "none\n";
				continue;
			}
			auto gets = get(root, Empty, x);
			Node* cur = gets.first;
			cur->par = gets.second;
			if (cur == Empty) {
				if (cur->par->key < x) {
					cout << cur->par->key << endl;
					continue;
				}
				cur = cur->par;
			}
			cur = prev(cur);
			if (cur == Empty) {
				cout << "none\n";
			} else {
				cout << cur->key << endl;
			}
		}
	}
	return 0;
}
