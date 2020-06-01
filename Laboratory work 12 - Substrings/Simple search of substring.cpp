#include <bits/stdc++.h>
using namespace std;

int main() {
    string a, b;
	cin >> a >> b;

	vector <int> ans;

	for (int i = 0; i + (int)a.size() - 1 < (int)b.size(); i++) {
		bool flag = true;
		for (int j = 0; j < (int)a.size(); j++)
			flag &= (a[j] == b[i + j]);
		if (flag)
			ans.push_back(i);
	}

	cout << (int)ans.size() << '\n';
	for (int i = 0; i < (int)ans.size(); i++)
		cout << ans[i] + 1 << ' ';
	return 0;
}
