#include <bits/stdc++.h>
using namespace std;
#define X first
#define Y second
#define pb push_back
typedef pair<int, int> ii;
typedef long long ll;

int fw[20][20];
int big[20][20];
int sm[20][20];

void foo(int a, int b, int w)
{
	fw[a][b] = fw[b][a] = w;
}
void pre()
{
	for(int i = 1; i<= 16; i++)
	{
		fw[i][i] = 0;
		for(int j = i+1; j<= 16; j++)
		{
			fw[i][j] = fw[j][i] = 1e9;
		}
	}
	int q = 1000;
	foo(1, 2, q);
	foo(2, 9, 1);
	foo(9, 10, q);
	foo(3, 4, q);
	foo(11, 12, q);
	foo(5, 6, q); 
	foo(13, 14, q);
	foo(7, 8, q);
	foo(8, 15, 1);
	foo(15, 16, q);
	foo(1, 3, q);
	foo(3, 5, 1);
	foo(5, 7, q);
	foo(2, 4, q);
	foo(6, 8, q);
	foo(9, 11, q);
	foo(13, 15, q);
	foo(10, 12, q);
	foo(12, 14, 1);
	foo(14, 16, q);
	for(int k = 1; k<= 16; k++)
	{
		for(int i = 1; i<= 16; i++)
		{
			for(int j = 1; j<= 16; j++)
			{
				fw[i][j] = min(fw[i][j], fw[i][k]+fw[k][j]);
			}
		}
	}
	for(int i = 1; i<= 16; i++)
	{
		for(int j = 1; j<= 16; j++)
		{
			big[i][j] = fw[i][j]/1000;
			sm[i][j] = fw[i][j]%1000;
		}
	}
}

ll get(int a, int b, int k)
{
	ll mid = (1LL<<(k-1))-1;
	return big[a][b]*mid+sm[a][b];
}

int findzone(ll x, ll y, int k)
{
	ll mid = 1LL<<(k-1);
	int zone = 0;
	if(x<= mid)
	{
		if(y<= mid) zone = 2;
		else zone = 1;
	}
	else
	{
		if(y<= mid) zone = 4;
		else zone = 3;
	}
	return zone;
}

void solve(int k, ll x, ll y, vector<ll> &ans)
{
	if(k == 1)
	{
		if(x == 1LL && y == 1LL) ans = {1, 2, 0, 1};
		if(x == 1LL && y == 2LL) ans = {0, 1, 1, 2};
		if(x == 2LL && y == 1LL) ans = {2, 1, 1, 0};
		if(x == 2LL && y == 2LL) ans = {1, 0, 2, 1}; 
		return;
	}
	ll mid = 1LL<<(k-1);
	int zone = 0;
	if(x<= mid)
	{
		if(y<= mid) zone = 2;
		else zone = 1;
	}
	else
	{
		if(y<= mid) zone = 4;
		else zone = 3;
	}
	// printf("%lld %lld zone = %d\n", x, y, zone);
	ll xp = x, yp = y;
	if(zone == 3 || zone == 4) xp -= mid;
	if(zone == 3 || zone == 1) yp -= mid;
	vector<ll> res;
	solve(k-1, xp, yp, res);
	// printf("res = [ "); for(ll x : res) printf("%lld ", x); printf("]\n");
	ans.assign(4, 4e18);
	for(int i = 0; i< 4; i++)
	{
		int tar;
		if(i == 0) tar = 1;
		else if(i == 1) tar = 10;
		else if(i == 2) tar = 7;
		else tar = 16;
		// printf("go tar = %d\n", tar);
		for(int j = 1; j<= 4; j++)
		{
			// printf("try %lld %lld [%d][%d]\n", res[j], get(tar, 4*(zone-1)+j, k), tar, 4*(zone-1)+j);
			ans[i] = min(ans[i], res[j-1]+get(tar, 4*(zone-1)+j, k));
		}
	}
}

ll tahm(int k, ll x1, ll y1, ll x2, ll y2)
{
	if(k == 1)
	{
		return abs(x1-x2)+abs(y1-y2);
	}
	ll mid = 1LL<<(k-1);
	int z1 = findzone(x1, y1, k);
	int z2 = findzone(x2, y2, k);
	if(z1 == z2)
	{
		int zone = z1;
		if(zone == 3 || zone == 4) x1 -= mid, x2 -= mid;
		if(zone == 3 || zone == 1) y1 -= mid, y2 -= mid;
		return tahm(k-1, x1, y1, x2, y2);
	}
	if(z1 == 3 || z1 == 4) x1 -= mid;
	if(z1 == 3 || z1 == 1) y1 -= mid;
	if(z2 == 3 || z2 == 4) x2 -= mid;
	if(z2 == 3 || z2 == 1) y2 -= mid;
	vector<ll> r1(4, 0); 
	solve(k-1, x1, y1, r1);
	vector<ll> r2(4, 0); 
	solve(k-1, x2, y2, r2);
	// printf("r1 = [ "); for(ll x : r1) printf("%lld ", x); printf("]\n");
	// printf("r2	 = [ "); for(ll x : r2) printf("%lld ", x); printf("]\n");
	ll best = 4e18;
	for(int i = 1; i<= 4; i++)
	{
		for(int j = 1; j<= 4; j++)
		{
			// printf("try %lld+%lld+%lld [%d][%d]\n", r1[i-1], r2[j-1], get(4*(z1-1)+i, 4*(z2-1)+j, k), 4*(z1-1)+i, 4*(z2-1)+j);
			best = min(best, r1[i-1]+r2[j-1]+get(4*(z1-1)+i, 4*(z2-1)+j, k));
		}
	}
	return best;
}

int main()
{
	pre();
	// printf("big %d sm %d\n", big[7][12], sm[7][12]);
	int k; 
	ll x1, y1, x2, y2;
	scanf("%d", &k);
	scanf("%lld %lld %lld %lld", &x1, &y1, &x2, &y2);
	x1++; y1++; x2++; y2++;
	printf("%lld\n", tahm(k, x1, y1, x2, y2));
}