#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")
using namespace std;
#define X first
#define Y second
#define pb push_back
typedef pair<int, int> ii;
typedef long long ll;

const int maxn = 5e5+5;

vector<int> adj[maxn];
int dp[maxn];

int n, m; 
int out[105];
int carry[105];
int make[105];
int pass[105];

int cnt = 1;

int T[maxn]; // 1 NOT 2 OR 3 AND
int A[maxn];
int B[maxn];

int findpath(int u)
{
	if(dp[u] != -1) return dp[u];
	int best = 0;
	for(int v : adj[u])
	{
		best = max(best, 1+findpath(v));
	}
	return dp[u] = best;
}

bool cmp(int a, int b)
{
	return findpath(a)< findpath(b);
}

int buildgate(int t, int a, int b)
{
	T[cnt] = t;
	A[cnt] = a;
	B[cnt] = b;
	if(a>= 0 && b>= 0)
	{
		adj[cnt].pb(a);
		adj[cnt].pb(b);
	}
	cnt++;
	return cnt-1;
}

int create_and(vector<int> &elem)
{
	vector<int> foo = elem;
	vector<int> bar;
	while((int)foo.size()> 1)
	{
		for(int i = 0; i< (int) foo.size(); i += 2)
		{
			if(i+1< (int) foo.size()) bar.pb(buildgate(3, foo[i], foo[i+1]));
			else bar.pb(foo[i]);
		}
		foo = bar;
		bar.clear();
	}
	return foo[0];
}

int create_or(vector<int> &elem)
{
	vector<int> foo = elem;
	vector<int> bar;
	while((int)foo.size()> 1)
	{
		for(int i = 0; i< (int) foo.size(); i += 2)
		{
			if(i+1< (int) foo.size()) bar.pb(buildgate(2, foo[i], foo[i+1]));
			else bar.pb(foo[i]);
		}
		foo = bar;
		bar.clear();
	}
	return foo[0];
}

int create_adder(int a, int b, int c)
{
	int x = buildgate(2, a, b);
	int y = buildgate(3, a, b);
	int z = buildgate(1, y, y);
	int ab = buildgate(3, x, z);
	int tmp = buildgate(2, ab, c);
	int tmp2 = buildgate(3, ab, c);
	int tmp3 = buildgate(1, tmp2, tmp2);
	int abc = buildgate(3, tmp, tmp3);
	return abc;
}

int main()
{
	memset(dp, -1, sizeof dp);
	scanf("%d %d", &n, &m);
	carry[0] = 0;
	for(int i = 0; i< n; i++)
	{
		make[i] = buildgate(3, -(i+1), -n-(i+1));
		pass[i] = buildgate(2, -(i+1), -n-(i+1));
	}
	//create carry
	for(int i = 1; i<= n; i++)
	{
		vector<int> fin;
		for(int g = 0; g< i; g++)
		{
			vector<int> want;
			want.pb(make[g]);
			for(int j = g+1; j< i; j++)
			{
				want.pb(pass[j]);
			}
			sort(want.begin(), want.end(), cmp);
			fin.pb(create_and(want));
			// printf("sub %d depth %d\n", g, findpath(fin.back()));
			want.clear();
		}
		vector<int> want;
		for(int j = 0; j< i; j++) want.pb(pass[j]);
		want.pb(carry[0]);
		fin.pb(create_and(want));
		// printf("sz = %d\n", want.size());
		// printf("last sub depth %d\n", findpath(fin.back()));
		want.clear();
		sort(want.begin(), want.end());
		sort(fin.begin(), fin.end(), cmp);
		carry[i] = create_or(fin);
		// printf("carry %d depth %d\n", i, findpath(carry[i]));
	}
	for(int i = 0; i< n; i++)
	{
		out[i] = create_adder(-(i+1), -n-(i+1), carry[i]);
	}
	out[n] = carry[n];
	printf("%d\n", cnt-1);
	for(int i = 0; i<= n; i++) printf("%d ", out[i]);
	printf("\n");
	for(int i = 1; i< cnt; i++)
	{
		if(T[i] == 1)
		{
			printf("NOT ");
			printf("%d\n", A[i]);
		}
		else
		{
			if(T[i] == 2) printf("OR ");
			else printf("AND ");
			printf("%d %d\n", A[i], B[i]);
		}
	}
}