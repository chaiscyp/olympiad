#include <bits/stdc++.h>
using namespace std;
#define X first
#define Y second
#define pb push_back
typedef pair<int, int> ii;
typedef long long ll;

const int maxn = 2e5+5;

vector< ii > adj[maxn];
int dp[22][maxn];
int dep[maxn];
int pp[maxn];

int n, q, a, b;

const int inf = 2e9+5;

void dfs(int u = 1, int p = 0)
{
	for(int i = 1; i<= 20; i++) dp[i][u] = dp[i-1][dp[i-1][u]];
	for(auto kk : adj[u])
	{
		int v = kk.X, w = kk.Y;
		if(v == p) continue;
		dep[v] = dep[u]+1;
		pp[v] = w;
		dp[0][v] = u;
		dfs(v, u);
	}
}

int LCA(int u, int v)
{
	if(dep[u]< dep[v]) swap(u, v);
	for(int i = 20; i>= 0; i--)
	{
		int x = dp[i][u];
		if(dep[x]>= dep[v]) u = x;
	}
	if(u == v) return u;
	for(int i = 20; i>= 0; i--)
	{
		int x = dp[i][u], y = dp[i][v];
		if(x == y) continue;
		u = x; v = y;
	}
	return dp[0][u];
}

int pos[maxn];
int S[maxn];
bool mark[maxn];
int len[maxn];
int A[maxn], B[maxn];

int solve(int u, int p)
{
	int best = 0;
	for(auto kk : adj[u])
	{
		int v = kk.X, w = kk.Y;
		if(v == p || mark[v]) continue;
		best = max(best, w+solve(v, u));
	}
	return best;
}

struct node
{
	int opt, a, b;
	node(){}
	node(int opt, int a, int b): opt(opt), a(a), b(b){}
};

node st[4*maxn];
int m;

void pull(int p)
{
	st[p].opt = max(st[2*p].opt, st[2*p+1].opt);
	st[p].opt = max(st[p].opt, st[2*p].b+st[2*p+1].a);
	st[p].a = max(st[2*p].a, st[2*p+1].a);
	st[p].b = max(st[2*p].b, st[2*p+1].b);
}

void build(int p = 1, int L = 1, int R = m)
{
	if(L == R)
	{
		st[p] = node(len[L], A[L], B[L]);
		return;
	}
	int M = (L+R)/2;
	build(2*p, L, M); build(2*p+1, M+1, R);
	pull(p);
}

node ask(int i, int j, int p = 1, int L = 1, int R = m)
{
	if(i> R || j< L) return node(-inf, -inf, -inf);
	if(i<= L && R<= j) return st[p];
	int M = (L+R)/2;
	node x = ask(i, j, 2*p, L, M);
	node y = ask(i, j, 2*p+1, M+1, R);
	node res;
	res.opt = max(x.opt, y.opt);
	res.opt = max(res.opt, x.b+y.a);
	res.a = max(x.a, y.a);
	res.b = max(x.b, y.b);
	return res;
}

int main()
{
	scanf("%d %d %d %d", &n, &q, &a, &b);
	for(int i = 1; i< n; i++)
	{
		int u, v, w; scanf("%d %d %d", &u, &v, &w);
		adj[u].pb(ii(v, w)); adj[v].pb(ii(u, w));
	}
	dep[1] = 1; dfs();
	int x = LCA(a, b);
	int cur = a;
	vector<int> p1, p2;
	vector<int> w1, w2;
	p1.pb(-1);
	w1.pb(-1);
	while(cur != x)
	{
		p1.pb(cur);
		w1.pb(pp[cur]);
		cur = dp[0][cur];
	}
	cur = b;
	while(cur != x)
	{
		p2.pb(cur);
		w2.pb(pp[cur]);
		cur = dp[0][cur];
	}
	reverse(p2.begin(), p2.end());
	reverse(w2.begin(), w2.end());
	p1.pb(x);
	for(int kk : p2) p1.pb(kk);
	for(int kk : w2) w1.pb(kk);
	m = ((int) p1.size())-1;
	for(int i = 1; i<= m; i++) pos[p1[i]] = i;
	for(int i = 1; i<= m; i++) mark[p1[i]] = true;
	for(int i = 2; i<= m; i++) S[i] = S[i-1]+w1[i-1];
	for(int i = 1; i<= m; i++)
	{
		len[i] = solve(p1[i], 0);
	}
	for(int i = 1; i<= m; i++) A[i] = len[i]+S[i];
	for(int i = 1; i<= m; i++) B[i] = len[i]-S[i];
	build();
	while(q--)
	{
		int x, y; scanf("%d %d", &x, &y);
		int px = pos[x], py = pos[y];
		if(px> py) swap(px, py);
		printf("%d\n", ask(px, py).opt);
	}
}