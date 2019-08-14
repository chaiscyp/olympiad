#include <bits/stdc++.h>
using namespace std;
#define X first
#define Y second
#define pb push_back
typedef pair<int, int> ii;
typedef long long ll;

int n, m; 
int a, b;

int t1, t2, t3;

vector< ii > vec;
vector<int> all;

int dp[505][1005][505];

int solve(int u, int cov, int rem)
{
	if(rem<= 0) return 0;
	if(u == m) return 1e9;
	if(dp[u][cov][rem] != -1) return dp[u][cov][rem];
	int x = solve(u+1, cov, rem);
	int y;
	if(vec[u].X< cov)
	{
		if(vec[u].Y> cov) y = all[vec[u].Y]-all[cov]+solve(u+1, vec[u].Y, rem-1);
		else y = solve(u+1, cov, rem-1);
	}
	else
	{
		y = all[vec[u].Y]-all[vec[u].X]+solve(u+1, vec[u].Y, rem-1);
	}
	return dp[u][cov][rem] = min(x, y);
}

int main()
{
	scanf("%d %d", &n, &m);
	scanf("%d %d", &a, &b);
	if(a> b) swap(a, b);
	vec.resize(m);
	for(int i = 0; i< m; i++)
	{
		scanf("%d %d", &vec[i].X, &vec[i].Y);
		if(vec[i].X> vec[i].Y) swap(vec[i].X, vec[i].Y);
		all.pb(vec[i].X); 
		all.pb(vec[i].Y);
		int c; scanf("%d", &c);
		if(c<= a) t3++;
		else if(c<= b) t1++;
		else t2++;
	}
	all.pb(0);
	sort(all.begin(), all.end());
	all.erase(unique(all.begin(), all.end()), all.end());
	for(int i = 0; i< m; i++)
	{
		vec[i].X = lower_bound(all.begin(), all.end(), vec[i].X)-all.begin();
		vec[i].Y = lower_bound(all.begin(), all.end(), vec[i].Y)-all.begin();
	}
	if(t3)
	{
		printf("-1\n"); return 0;
	}
	sort(vec.begin(), vec.end());
	memset(dp, -1, sizeof dp);
	int res = solve(0, 0, t1);
	printf("%d\n", res*a+(n-res-1)*b);
}
