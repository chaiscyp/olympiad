#include <bits/stdc++.h>
using namespace std;
#define X first
#define Y second
#define pb push_back
typedef pair<int, int> ii;
typedef long long ll;

const int maxn = 1e5+5;

int n, q; 

int st[4*maxn];
int lz[4*maxn];

void pushdown(int p, int L, int R)
{
	if(lz[p] == -1) return;
	st[p] = 0;
	if(L != R)
	{
		lz[2*p] = lz[p];
		lz[2*p+1] = lz[p];
	}
	lz[p] = -1;
}

int ask(int i, int j, int p = 1, int L = 1, int R = n-1)
{
	if(i> R || j< L) return 0;
	pushdown(p, L, R);
	if(i<= L && R<= j) return st[p];
	int M = (L+R)/2;
	int x = ask(i, j, 2*p, L, M);
	int y = ask(i, j, 2*p+1, M+1, R);
	return x+y;
}

void setzero(int i, int j, int p = 1, int L = 1, int R = n-1)
{
	pushdown(p, L, R);
	if(i> R || j< L) return;
	if(i<= L && R<= j)
	{
		lz[p] = 0;
		pushdown(p, L, R);
		return;
	}
	int M = (L+R)/2;
	setzero(i, j, 2*p, L, M);
	setzero(i, j, 2*p+1, M+1, R);
	st[p] = st[2*p] + st[2*p+1];
}

void uppoint(int x, int dx, int p = 1, int L = 1, int R = n-1)
{
	pushdown(p, L, R);
	if(x> R || x< L) return;
	if(L == R)
	{
		st[p] += dx;
		return;
	}
	int M = (L+R)/2;
	uppoint(x, dx, 2*p, L, M);
	uppoint(x, dx, 2*p+1, M+1, R);
	st[p] = st[2*p] + st[2*p+1];
}

int travL(int want, int p = 1, int L = 1, int R = n-1)
{
	pushdown(p, L, R);
	if(L == R) return L;
	int M = (L+R)/2;
	pushdown(2*p, L, M); pushdown(2*p+1, M+1, R);
	int cur = st[2*p];
	if(cur> want) return travL(want, 2*p, L, M);
	return travL(want-cur, 2*p+1, M+1, R);
} 

int travR(int want, int p = 1, int L = 1, int R = n-1)
{
	pushdown(p, L, R);
	if(L == R) return L;
	int M = (L+R)/2;
	pushdown(2*p, L, M); pushdown(2*p+1, M+1, R);
	int cur = st[2*p+1];
	if(cur> want) return travR(want, 2*p+1, M+1, R);
	return travR(want-cur, 2*p, L, M);
}

int modleft(int x, int want)
{
	int base = ask(x, n-1);
	int res = travR(base+want);
	return res+1;
}

int modright(int x, int want)
{
	int base = ask(1, x);
	int res = travL(base+want);
	return res-1;
}

int main()
{
	memset(lz, -1, sizeof lz);
	scanf("%d %d", &n, &q);
	for(int i = 1; i<= n-1; i++) uppoint(i, 10);
	while(q--)
	{
		int typ; scanf("%d", &typ);
		if(typ == 1)
		{
			int x, dx; scanf("%d %d", &x, &dx);
			int west = ask(1, x-1), east = ask(x+1, n-1);
			int mid = dx/2;
			int wL, wR;
			if(west>= mid && east>= mid)
			{
				wL = wR = mid;
			}
			else if(west< mid)
			{
				wL = west; wR = dx-wL;
			}
			else
			{
				wR = east; wL = dx-wR;
			}
			// printf("wL = %d wR = %d\n", wL, wR);
			int x1 = modleft(x, wL), x2 = modright(x, wR);
			// printf("x1 = %d x2 = %d\n", x1, x2);
			int s1 = ask(x1, x-1), s2 = ask(x+1, x2);
			setzero(x1, x-1); setzero(x+1, x2);
			int r1 = wL-s1, r2 = wR-s2;
			// printf("r1 = %d r2 = %d\n", r1, r2);
			uppoint(x1-1, -r1); uppoint(x2+1, -r2);
			uppoint(x, dx);
		}
		else
		{
			int x; scanf("%d", &x);
			printf("%d\n", ask(x, x));
		}
	}
}