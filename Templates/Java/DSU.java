class DSU {
	int[] fa, sz;

	DSU(int n) {
		fa = new int[n];
		sz = new int[n];
		for(int i = 0; i < n; ++i) {
			sz[i] = 1;
			fa[i] = i;
		}
	}

	int get(int x) {
		if(fa[x] == x) {
			return x;
		}
		return fa[x] = get(fa[x]);
	}

	int size(int x) {
		return sz[get(x)];
	}

	void merge(int a, int b) {
		a = get(a);
		b = get(b);
		if(sz[a] > sz[b]) {
			merge(b, a);
		} else {
			sz[a] += sz[b];
			fa[b] = a;
		}
	}
}

