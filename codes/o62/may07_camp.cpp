#include <bits/stdc++.h>
using namespace std;
#define X first
#define Y second
#define pb push_back
typedef pair<int, int> ii;
typedef long long ll;

const int maxn = 250005;

struct task
{
	int a, b, w; 
	task(int a = 0, int b = 0, int w = 0) : a(a), b(b), w(w){}
	bool operator < (task other) const
	{
		if(a != other.a) return a< other.a;
		return b< other.b;
	}
};

task arr[maxn];
ll dp[maxn][2];
int n;

int st[4*maxn];

int ask(int i, int j, int p = 1, int L = 1, int R = n)
{
	if(i> R || j< L) return 0;
	if(i<= L && R<= j) return st[p];
	int x = ask(i, j, 2*p, L, (L+R)/2);
	int y = ask(i, j, 2*p+1, (L+R)/2+1, R);
	return max(x, y);
}

void update(int x, int dx, int p = 1, int L = 1, int R = n)
{
	if(x> R || x< L) return;
	if(L == R)
	{
		st[p] += dx;
		return;
	}
	update(x, dx, 2*p, L, (L+R)/2);
	update(x, dx, 2*p+1, (L+R)/2+1, R);
	st[p] = max(st[2*p], st[2*p+1]);
}

ll solve(int u, bool aval)
{
	if(u == n+1) return 0;
	if(dp[u][aval] != -1) return dp[u][aval];
	ll best = 0;
	if(aval == 1) best = arr[u].w+solve(u+1, 0);
	best = max(best, solve(u+1, aval));
	int ed = arr[u].b;
	int nxt = upper_bound(arr+u+1, arr+n+1, task(arr[u].b, 0, 0))-arr;
	// if(u == 1) printf("nxt is %d\n", nxt);
	best = max(best, arr[u].w+solve(nxt, aval));
	if(aval) best = max(best, arr[u].w+ask(u+1, nxt-1)+solve(nxt, 0));
	return dp[u][aval] = best;
}

int main()
{
	scanf("%d", &n);
	for(int i = 1; i<= n; i++) scanf("%d %d %d", &arr[i].a, &arr[i].b, &arr[i].w);
	sort(arr+1, arr+n+1);
	for(int i = 1; i<= n; i++) update(i, arr[i].w);
	memset(dp, -1, sizeof dp);
	printf("%lld\n", solve(1, 1));
}