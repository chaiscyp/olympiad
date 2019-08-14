#include <bits/stdc++.h>
using namespace std;
#define X first
#define Y second
#define pb push_back
typedef pair<int, int> ii;
typedef long long ll;

const int maxn = 1e5+5;

vector<int> adj[maxn];

int T[3*maxn], A[3*maxn], B[3*maxn];

int n, q;


struct dsu
{
	int par[maxn];
	int cent[maxn];
	dsu(int _n)
	{
		for(int i = 1; i<= _n; i++)
		{
			par[i] = cent[i] = i;
		}
	}
	int findset(int x)
	{
		if(x == par[x]) return x;
		return par[x] = findset(par[x]);
	}
	int findmaster(int x)
	{
		return cent[findset(x)];
	}
	void unionset(int x, int y)
	{
		int a = findset(x), b = findset(y);
		par[a] = b;
	}
	void changemaster(int a)
	{
		cent[findset(a)] = a;
	}
};

dsu cass(n);

int dep[maxn];
int dp[22][maxn];

void dfs(int u = 1, int p = 0)
{
	for(int i = 1; i<= 20; i++) dp[i][u] = dp[i-1][dp[i-1][u]];
	for(int v : adj[u])
	{
		if(v == p) continue;
		dp[0][v] = u;
		dep[v] = dep[u]+1;
		dfs(v, u);
	}
}

int LCA(int u, int v)
{
	if(dep[u]< dep[v]) swap(u, v);
	for(int i = 20; i>= 0; i--)
	{
		int x = dp[i][u];
		if(dep[x]>= dep[v])
		{
			u = x;
		}
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

int dist(int a, int b)
{
	int x = LCA(a, b);
	return dep[a]+dep[b]-dep[x]-dep[x];
}

int main()
{
	scanf("%d %d", &n, &q);
	cass = dsu(n);
	for(int i = 1; i<= q; i++)
	{
		scanf("%d", &T[i]);
		scanf("%d", &A[i]);
		if(T[i] != 2) scanf("%d", &B[i]);
	}
	for(int i = 1; i<= q; i++)
	{
		if(T[i] == 1)
		{
			adj[A[i]].pb(B[i]);
			adj[B[i]].pb(A[i]);
		}
	}
	for(int i = 1; i<= n; i++)
	{
		if(!dep[i])
		{
			dep[i] = 1;
			dfs(i, 0);
		}
	}
	for(int i = 1; i<= q; i++)
	{
		if(T[i] == 1)
		{
			cass.unionset(A[i], B[i]);
		}
		else if(T[i] == 2)
		{
			cass.changemaster(A[i]);
		}
		else
		{
			int u, v; u = A[i]; v = B[i];
			int x = cass.findmaster(u);
			assert(cass.findmaster(u) == cass.findmaster(v));
			if(dist(u, x)< dist(v, x)) printf("%d\n", u);
			else printf("%d\n", v);
		}
	}
}