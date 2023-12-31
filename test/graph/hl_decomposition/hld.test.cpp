#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"
#include <bits/stdc++.h>
using namespace std;

#include "../../../graph/hld.cpp"
#include "../../../data_structure/fenwick_tree.cpp"

int main() {
	int N, Q;
	cin >> N >> Q;

	fenwick_tree<long long> ft(N);
	heavy_light_decomposition hld(N);

	vector<int> A(N);
	for (int i = 0; i < N; i++) {
		cin >> A[i];
	}
	for (int i = 0; i < N - 1; i++) {
		int u, v;
		cin >> u >> v;
		hld.add_edge(u, v);
	}

	hld.hld_start();
	for (int i = 0; i < N; i++) {
		auto Update = [&](int i, int pos) {
			ft.add(pos, A[i]);
		};
		hld.update(i, Update);
	}

	while (Q--) {
		int t;
		cin >> t;

		if (t == 0) {
			int p, x;
			cin >> p >> x;

			auto Update = [&](int i, int pos) {
				ft.add(pos, x);
			};

			hld.update(p, Update);
		}

		else {
			int u, v;
			cin >> u >> v;

			auto Query = [&](int x, int y) {
				return ft.sum(x, y);
			};
			auto F = [&](long long a, long long b) {
				return a + b;
			};
			long long e = 0;

			cout << hld.query(u, v, Query, F, e) << '\n';
		}
	}
}
