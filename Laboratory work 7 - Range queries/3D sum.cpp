#include <bits/stdc++.h>
using namespace std;
typedef unsigned int uint;

vector < vector< vector<uint> > > fen[8];

vector <int> n(3);

void build() {
	for (int t = 0; t < 8; t++) {
		fen[t].resize(n[0] + 2);
		for (int i = 0; i < n[0] + 2; i++) {
			fen[t][i].resize(n[1] + 2);
			for (int j = 0; j < n[1] + 2; j++) {
				fen[t][i][j].resize(n[2] + 2);
			}
		}
	}
}

inline void change(int t, int x, int y, int z, uint s) {
	if (!(t & 1))
		s *= (uint)(1 - x);
	if (!(t & 2))
		s *= (uint)(1 - y);
	if (!(t & 4))
		s *= (uint)(1 - z);
	for (int i = x; i < (int)fen[t].size(); i |= (i + 1)) {
		for (int j = y; j < (int)fen[t][i].size(); j |= (j + 1)) {
			for (int k = z; k < (int)fen[t][i][j].size(); k |= (k + 1)) {
				fen[t][i][j][k] += s;
			}
		}
	}
}

inline uint get(int t, int x, int y, int z) {
	uint res = 0u;
	for (int i = x; i > 0; i = (i & (i + 1)) - 1) {
		for (int j = y; j > 0; j = (j & (j + 1)) - 1) {
			for (int k = z; k > 0; k = (k & (k + 1)) - 1) {
				res += fen[t][i][j][k];
			}
		}
	}
	if (t & 1)
		res *= (uint)x;
	if (t & 2)
		res *= (uint)y;
	if (t & 4)
		res *= (uint)z;
	return res;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> n[0] >> n[1] >> n[2];
	vector < pair<int, int> > order(3);
	for (int i = 0; i < 3; i++) {
		order[i] = make_pair(n[i], i);
	}
	sort(order.begin(), order.end());
	vector <int> perm(3);
	for (int i = 0; i < 3; i++) {
		perm[order[i].second] = i;
		n[i] = order[i].first;
	}
	build();
	int q, lx, rx, ly, ry, lz, rz;
	uint s;
	char type;
	cin >> q;
	vector <int> coor(6), normcoor(6);

	while (q--) {
		cin >> type;
		for (int i = 0; i < 6; i++)
			cin >> coor[i];
		for (int i = 0; i < 3; i++) {
			normcoor[perm[i]] = coor[i];
			normcoor[perm[i] + 3] = coor[i + 3];
		}
		lx = normcoor[0];
		ly = normcoor[1];
		lz = normcoor[2];
		rx = normcoor[3];
		ry = normcoor[4];
		rz = normcoor[5];
		lx++; ly++; lz++;
		if (type == 'a') {
			cin >> s;

			for (int t = 0; t < 8; t++) {
				change(t, lx, ly, lz, s);
				change(t, rx + 1, ly, lz, ~s + 1);
				change(t, lx, ry + 1, lz, ~s + 1);
				change(t, lx, ly, rz + 1, ~s + 1);
				change(t, rx + 1, ry + 1, lz, s);
				change(t, rx + 1, ly, rz + 1, s);
				change(t, lx, ry + 1, rz + 1, s);
				change(t, rx + 1, ry + 1, rz + 1, ~s + 1);
			}
		} else {
			uint ans = 0u;
			for (int t = 0; t < 8; t++) {
				ans += get(t, rx, ry, rz);
				ans -= get(t, lx - 1, ry, rz);
				ans -= get(t, rx, ly - 1, rz);
				ans -= get(t, rx, ry, lz - 1);
				ans += get(t, lx - 1, ly - 1, rz);
				ans += get(t, lx - 1, ry, lz - 1);
				ans += get(t, rx, ly - 1, lz - 1);
				ans -= get(t, lx - 1, ly - 1, lz - 1);
			}
			cout << ans << '\n';
		}
	}

	return 0;
}
