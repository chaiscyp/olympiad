#include <bits/stdc++.h>
using namespace std;
#define X first
#define Y second
#define pb push_back
typedef pair<int, int> ii;
typedef long long ll;

const int maxn = 1e5+5;

ll st[5][10*maxn];
ll lz[5][10*maxn];

int n;

void pushdown(ll *st, ll *lz, int p, int L, int R)
{
	if(!lz[p]) return;
	st[p] += lz[p];
	if(L != R)
	{
		lz[2*p] += lz[p];
		lz[2*p+1] += lz[p];
	}
	lz[p] = 0;
}

ll ask(ll *st, ll *lz, int i, int j, int p = 1, int L = 1, int R = n)
{
	if(i> R || j< L) return 0LL;
	pushdown(st, lz, p, L, R);
	if(i<= L && R<= j) return st[p];
	int x = ask(st, lz, i, j, 2*p, L, (L+R)/2);
	int y = ask(st, lz, i, j, 2*p+1, (L+R)/2+1, R);
	return max(x, y);
}

void update(ll *st, ll *lz, int i, int j, ll dx, int p = 1, int L = 1, int R = n)
{
	pushdown(st, lz, p, L, R);
	if(i> R || j< L) return;
	if(i<= L && R<= j) 
	{
		lz[p] += dx;
		pushdown(st, lz, p, L, R);
		return;
	}
	update(st, lz, i, j, dx, 2*p, L, (L+R)/2); update(st, lz, i, j, dx, 2*p+1, (L+R)/2+1, R);
	st[p] = max(st[2*p], st[2*p+1]);
}

struct candy
{
	int a, b, c;
	candy(){}
	candy(int a, int b, int c) : a(a), b(b), c(c){}
	bool operator < (candy other) const
	{
		return a< other.a;
	}
};

struct eve
{
	int x, typ;
	int a, b, c;
	eve(){}
	eve(int x, int typ, int a, int b, int c) : x(x), typ(typ), a(a), b(b), c(c){}
	bool operator < (eve other) const
	{
		if(x != other.x) return x> other.x;
		return typ< other.typ;
	}
};

vector<candy> foo;
vector<eve> bar;
vector<int> vals;

ll dp[5][4*maxn];

int mod(int x)
{
	return lower_bound(vals.begin(), vals.end(), x)-vals.begin();
}

ll run = 0;

int main()
{
	scanf("%d", &n);
	foo.resize(n+1);
	vals.pb(-1);
	vector<int> fuck;
	for(int i = 1; i<= n; i++)
	{
		scanf("%d %d %d", &foo[i].a, &foo[i].b, &foo[i].c);
		vals.pb(foo[i].a);
		fuck.pb(foo[i].a);
		vals.pb(foo[i].b);
	}
	sort(vals.begin(), vals.end());
	vals.erase(unique(vals.begin(), vals.end()), vals.end());
	sort(fuck.begin(), fuck.end());
	fuck.erase(unique(fuck.begin(), fuck.end()), fuck.end());
	// n = begins.size()-1;
	for(int x : fuck)
	{
		bar.pb(eve(mod(x), 1, mod(x), mod(x), 0));
	}
	for(int i = 1; i<= n; i++) 
	{
		bar.pb(eve(mod(foo[i].b), 0, mod(foo[i].a), mod(foo[i].b), -foo[i].c));
		bar.pb(eve(mod(foo[i].a)-1, 0, mod(foo[i].a), mod(foo[i].b), foo[i].c));
	}
	sort(bar.begin(), bar.end());
	n = vals.size();
	for(auto kk : bar)
	{
		int x = kk.x, t = kk.typ;
		int a = kk.a, b = kk.b, c = kk.c;
		if(t == 0)
		{
			for(int k = 0; k< 3; k++) update(st[k], lz[k], a, b, c);
			run -= c;
		}
		else
		{
			dp[0][a] = run;
			update(st[0], lz[0], a, a, run);
			// printf("dp[%d][%d] = %d\n", 0, a, run);
			printf("compute %d\n", a);
			for(int k = 1; k< 3; k++)
			{
				dp[k][a] = run+ask(st[k-1], lz[k-1], a+1, n);
				// printf("dp[%d][%d] = %d\n", k, a, dp[k][a]);
				update(st[k], lz[k], a, a, dp[k][a]);
			}
		}
	}
	ll best = 0;
	for(int i = 1; i<= n; i++)
	{
		best = max(best, dp[2][i]);
	}
	printf("%lld\n", best);
}