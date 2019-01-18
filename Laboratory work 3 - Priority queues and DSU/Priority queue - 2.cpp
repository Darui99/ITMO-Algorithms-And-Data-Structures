#include <bits/stdc++.h>
using namespace std;

struct Priority_Queue {
	vector <int> arr, numeric, elem;
	int size;

	Priority_Queue() {
		arr.push_back(0);
		numeric.push_back(0);
		size = 0;
	}

	void siftUp(int num) {
		while (num > 1) {
			int par = num / 2;
			if (arr[par] > arr[num]) {
				swap(arr[par], arr[num]);
				int first = numeric[par], second = numeric[num];
				swap(numeric[par], numeric[num]);
				swap(elem[first], elem[second]);
				num = par;
			} else {
				break;
			}
		}
	}

	void siftDown(int num) {
		while (true) {
			int son, son1 = num * 2, son2 = num * 2 + 1;
			if (son1 > size)
				break;
			if (son2 > size || arr[son1] <= arr[son2])
				son = son1;
			else
				son = son2;

			if (arr[son] < arr[num]) {
				swap(arr[son], arr[num]);
				int first = numeric[son], second = numeric[num];
				swap(numeric[son], numeric[num]);
				swap(elem[first], elem[second]);
				num = son;
			} else {
				break;
			}
		}
	}

	void push(int x, int num) {
		size++;
		elem.push_back(size);
		if ((int)arr.size() <= size) {
			arr.push_back(0);
			numeric.push_back(0);
		}
		arr[size] = x;
		numeric[size] = num;
		siftUp(size);
	}

	pair<int, int> extractMin() {
		if (size == 0)
			return make_pair(0, -1);

		int first = numeric[1], second = numeric[size];
		swap(numeric[1], numeric[size]);
		swap(elem[first], elem[second]);
		swap(arr[1], arr[size]);

		size--;
		siftDown(1);
		return make_pair(arr[size + 1], numeric[size + 1]);
	}

	void decreaseKey(int num, int k) {
		num = elem[num];
		int prev = arr[num];
		arr[num] = k;
		if (k < prev)
			siftUp(num);
		else
			siftDown(num);
	}
};

int main() {
    freopen("priorityqueue2.in", "r", stdin);
    freopen("priorityqueue2.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	Priority_Queue q = Priority_Queue();

	int cur_num = 0, x, onum, query = 1;
	vector <int> num, pushnum;
	vector <bool> del;
	string type;
	while (cin >> type) {
		num.push_back(cur_num);
		del.push_back(false);
		if (type == "push") {
			cin >> x;
			q.push(x, cur_num);
			pushnum.push_back(query);
			cur_num++;
		}
		if (type == "extract-min") {
			pair<int, int> res = q.extractMin();
			if (res.second == -1) {
				cout << "*\n";
			} else {
				cout << res.first << " " << pushnum[res.second] << '\n';
				del[res.second] = true;
			}
		}
		if (type == "decrease-key") {
			cin >> onum >> x;
			if (!del[num[onum - 1]])
				q.decreaseKey(num[onum - 1], x);
		}
		query++;
	}

	return 0;
}
