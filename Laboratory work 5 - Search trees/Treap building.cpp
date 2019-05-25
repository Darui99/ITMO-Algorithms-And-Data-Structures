#include <bits/stdc++.h>
using namespace std;

struct Node {
	Node* left;
	Node* right;
	Node* par;
	int key, pr, num;
};

struct trip {
	int first, second, num;
};

bool cmp(trip a, trip b) {
	return make_pair(a.first, a.second) < make_pair(b.first, b.second);
}

vector < vector<int> > ans;

void getAns(Node* v) {
	if (v == NULL)
		return;

	ans[v->num - 1].resize(3);

	if (v->par == NULL)
		ans[v->num - 1][0] = 0;
	else
		ans[v->num - 1][0] = v->par->num;

	if (v->left == NULL)
		ans[v->num - 1][1] = 0;
	else
		ans[v->num - 1][1] = v->left->num;

	if (v->right == NULL)
		ans[v->num - 1][2] = 0;
	else
		ans[v->num - 1][2] = v->right->num;

	getAns(v->left);
	getAns(v->right);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n;
	cin >> n;

	ans.resize(n);
	vector <trip> arr(n);
	for (int i = 0; i < n; i++) {
		cin >> arr[i].first >> arr[i].second;
		arr[i].num = i + 1;
	}
	sort(arr.begin(), arr.end(), cmp);

	stack <Node*> q;
	Node* past;

	for (int i = 0; i < n; i++) {
		Node* p = new Node{ NULL, NULL, NULL, arr[i].first, arr[i].second, arr[i].num };
		past = NULL;
		while (!q.empty()) {
			if (q.top()->pr < p->pr) {
				q.top()->right = p;
				p->par = q.top();
				break;
			}
			past = q.top();
			q.pop();
		}
		q.push(p);
		if (past != NULL) {
			p->left = past;
			past->par = p;
		}
	}

	while ((int)q.size() > 1)
		q.pop();

	getAns(q.top());
	cout << "YES\n";
	for (int i = 0; i < n; i++)
		cout << ans[i][0] << " " << ans[i][1] << " " << ans[i][2] << endl;
	return 0;
}
