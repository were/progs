#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int N = 111111, Mod = 1000000000 + 7, Magic = 3;

typedef unsigned long long ULL;

struct Edge {
	int v, w;
};

vector<Edge> g[N];

int n, m, source, terminal, pre[N], pow2[N];
bool vis[N];

ULL pow3[N];

struct Node {
	int sum, len;
	ULL hash;
	Node *l, *r;
	void rz() {
		sum = (l->sum == l->len) ? l->len + r->sum : l->sum;
		len = l->len + r->len;
		hash = l->hash * pow3[r->len] + r->hash;
	}
}nil[N << 6], *templates[2][N], *dis[N], *tot =nil;

Node *newNode(Node *l, Node *r) {
	++tot;
	tot->l = l;
	tot->r = r;
	tot->rz();
	return tot;
}

Node *newNode(int v) {
	++tot;
	tot->l = tot->r = nil;
	tot->sum = v;
	tot->len = 1;
	tot->hash = 1ull + v;
	return tot;
}

int dfs(Node *t, int l, int r) {
	if(l == r) {
		return t->sum * pow2[l - 1];
	}
	int m = (l + r) / 2;
	return (dfs(t->l, l, m) + dfs(t->r, m + 1, r)) % Mod;
}

int query(int pos, int l, int r, Node *t) {
	if(l >= pos) {
		return t->sum;
	}
	int m = (l + r) / 2;
	if(pos > m) {
		return query(pos, m + 1, r, t->r);
	} else {
		int tmp = query(pos, l, m, t->l);
		return pos + tmp - 1 == m ? tmp + query(pos, m + 1, r, t->r) : tmp;
	}
}

Node *setRange(int a, int b, int v, int l, int r, Node *t) {
	if(b < l || a > r) {
		return t;
	}
	if(a <= l && r <= b) {
		return templates[v][r - l + 1];
	}
	int m = (l + r) / 2;
	Node *res = newNode(setRange(a, b, v, l, m, t->l), setRange(a, b, v, m + 1, r, t->r));
	return res;
}

Node *add(Node *t, int l) {
	int r = l + query(l, 1, N - 1, t) - 1;
	if(l <= r) {
		t = setRange(l, r, 0, 1, N - 1, t);
	}
	t = setRange(r + 1, r + 1, 1, 1, N - 1, t);
	return t;
}

int cmp(Node *t1, Node *t2) {
	if(t1->len == 1) {
		return (int) (t1->hash - t2->hash);
	}
	if(t1->hash == t2->hash) {
		return 0;
	}
	if(t1->r->hash != t2->r->hash) {
		return cmp(t1->r, t2->r);
	}
	return cmp(t1->l, t2->l);
}

struct Data {
	int v;
	Node *dis;
};

struct Comparator {
	bool operator() (const Data &a, const Data &b) {
		return cmp(a.dis, b.dis) > 0;
	};
};

priority_queue<Data, vector<Data>, Comparator> q;

int main() {
	cin >> n >> m;
	for(int i = 0; i < m; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		g[u].push_back(Edge{v, w});
		g[v].push_back(Edge{u, w});
	}
	cin >> source >> terminal;

	pow3[0] = 1ll;
	pow2[0] = 1;
	for(int i = 1; i < N; ++i) {
		pow3[i] = pow3[i - 1] * Magic;
		pow2[i] = pow2[i - 1] * 2 % Mod;
	}

	nil->l = nil->r = nil;
	nil->sum = nil->len = 0;
	nil->hash = 0ll;
	for(int i = 0; i < 2; ++i) {
		templates[i][1] = newNode(i);
		for(int j = 2; j < N; ++j) {
			templates[i][j] = newNode(templates[i][(1 + j) / 2], templates[i][j - (1 + j) / 2]);
		}
	}

	for(int i = 1; i <= n; ++i) {
		dis[i] = i == source ? templates[0][N - 1] : templates[1][N - 1];
	}
	for(q.push(Data{source, dis[source]}); !q.empty(); ) {
		int v;
		while(!q.empty() && vis[v = q.top().v]) {
			q.pop();
		}
		if(vis[v] || v == terminal) {
			if(v == terminal) {
				cout << dfs(dis[terminal], 1, N - 1) << endl;
				vector<int> res;
				for(int i = terminal; i; i = pre[i]) {
					res.push_back(i);
				}
				reverse(res.begin(), res.end());
				cout << res.size() << endl;
				for(size_t i = 0; i < res.size(); ++i) {
					cout << res[i] << (i + 1 < res.size() ? " " : "\n");
				}
				return 0;
			}
			break;
		} else {
			q.pop();
			vis[v] = true;
		}
		for(auto &cur : g[v]) {
			Node *tmp = add(dis[v], cur.w + 1);
			if(cmp(tmp, dis[cur.v]) < 0) {
				q.push(Data{cur.v, dis[cur.v] = tmp});
				pre[cur.v] = v;
			}
		}
	}

	cout << -1 << endl;
	return 0;
}
