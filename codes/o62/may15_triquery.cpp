#include <bits/stdc++.h>
using namespace std;
#define X first
#define Y second
#define pb push_back
typedef pair<int, int> ii;
typedef long long ll;

const int maxn = 3005;

ll tri[2*maxn][maxn];
ll sq[maxn][maxn];

ll arr[maxn][maxn];

int n;

void updatetri(int x, int y, ll dx)
{
	for(; x<= 2*n; x += x&(-x))
	{
		for(int k = y; k<= n; k += k&(-k))
		{
			tri[x][k] += dx;
		}
	}
}

void updatesq(int x, int y, ll dx)
{
	for(; x<= 2*n; x += x&(-x))
	{
		for(int k = y; k<= n; k += k&(-k))
		{
			sq[x][k] += dx;
		}
	}
}

ll asktri(int x, int y)
{
	ll res = 0;
	for(; x; x -= x&(-x))
	{
		int k = y;
		for(; k; k -= k&(-k)) res += tri[x][k];
	}
	return res;
}

ll asksq(int x, int y)
{
	ll res = 0;
	for(; x; x -= x&(-x))
	{
		int k = y;
		for(; k; k -= k&(-k)) res += sq[x][k];
	}
	return res;
}

void help(int x1, int y1, int x2, int y2, ll dx)
{
	updatetri(x1, y1, dx);
	updatetri(x2+1, y1, -dx);
	updatetri(x1, y2+1, -dx);
	updatetri(x2+1, y2+1, dx);
}

void mod(int x, int y, ll v)
{
	ll dx = v-arr[x][y];
	updatesq(x, y, dx);
	//diagonal
	help(x+y, y, x+y, n, dx/2);
	help(1, y, x+y-1, n, dx);
	arr[x][y] = v;
}

ll getsq(int x1, int y1, int x2, int y2)
{
	if(x2< x1) return 0;
	if(y2< y1) return 0;
	ll res = asksq(x2, y2);
	res -= asksq(x1-1, y2);
	res -= asksq(x2, y1-1);
	res += asksq(x1-1, y1-1);
	return res;
}

int main()
{
	int q; 
	scanf("%d %d", &n, &q);
	while(q--)
	{
		int t, a, b;
		ll c; scanf("%d %d %d %lld", &t, &a, &b, &c);
		if(t == 2)
		{
			mod(a, b, c);
		}
		else
		{
			int D = a+b-c+1;
			ll base = 0;
			// printf("base = %lld\n", base);
			base = asktri(D, b);
			base -= asktri(D, b-c);
			base -= getsq(a+1, b-c+1, n, b);
			printf("%lld\n", base); 
		}
	}
}