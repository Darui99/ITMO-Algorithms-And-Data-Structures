#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int inf = 2147483647;

struct Priority_Queue {
	vector <int> arr, numeric, elem;
	int size;

	Priority_Queue(int n) {
		arr.resize(n + 1);
		numeric.resize(n + 1);
		elem.resize(n + 1);
		size = 0;
	}

	void siftUp(int num) {
		while (num > 1) {
			int par = num / 2;
			if (arr[par] < arr[num]) {
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
			if (son2 > size || arr[son1] >= arr[son2])
				son = son1;
			else
				son = son2;

			if (arr[son] > arr[num]) {
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
		elem[num] = size;
		if ((int)arr.size() <= size) {
			arr.push_back(0);
			numeric.push_back(0);
		}
		arr[size] = x;
		numeric[size] = num;
		siftUp(size);
	}

	pair<int, int> extractMax() {
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

	void increaseKey(int num, int k) {
		num = elem[num];
		int prev = arr[num];
		arr[num] = k;
		if (k > prev)
			siftUp(num);
		else
			siftDown(num);
	}

	void extract(int num) {
		increaseKey(num, inf);
		extractMax();
	}

	int getMax() {
		if (size > 0)
			return arr[1];
		else
			return inf;
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, t, l, r, x;
	cin >> n >> t;
	vector < vector<int> > ins(n), del(n);
	vector <int> arr(t);

	for (int i = 0; i < t; i++) {
		cin >> l >> r >> x;
		l--; r--;
		arr[i] = x;
		ins[l].push_back(i);
		del[r].push_back(i);
	}

	Priority_Queue q = Priority_Queue(n + t);
	vector <int> ans(n, inf);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < (int)ins[i].size(); j++) {
			q.push(arr[ins[i][j]], ins[i][j]);
		}
		ans[i] = q.getMax();
		for (int j = 0; j < (int)del[i].size(); j++) {
			q.extract(del[i][j]);
		}
	}

	for (int i = 0; i < n; i++)
		cout << ans[i] << " ";
	return 0;
}
