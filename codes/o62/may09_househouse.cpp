#include <bits/stdc++.h>
#include "househouse.h"
using namespace std;
#define X first
#define Y second
#define pb push_back
typedef pair<int, int> ii;
typedef long long ll;

struct frac
{
	int a, b;
	frac(int a, int b) : a(a), b(b){}
	bool operator < (frac other) const
	{
		return 1LL*a*other.b< 1LL*other.a*b;
	}
};

int main()
{
	int C, M;
	househouse_init(C, M);
	if(M<= C)
	{
		while(true)
		{
			househouse_pay(1);
		}
		return 0;
	}
	frac opt(1e9, 1);
	int best = -1;
	for(int i = 0; i<= M-1; i++)
	{
		if(frac(C+i, min(i+1, C))< opt)
		{
			opt = frac(C+i, min(i+1, C));
			best = i;
		}
	}
	if(frac(M, C)< opt)
	{
		best = M;
	}
	if(best == M)
	{
		while(best--)
		{
			househouse_pay(1);
		}
		return 0;
	}
	while(best--)
	{
		househouse_pay(1);
	}
	househouse_pay(C);
}