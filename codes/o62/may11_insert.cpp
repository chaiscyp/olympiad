#include <bits/stdc++.h>
using namespace std;
#define X first
#define Y second
#define pb push_back
typedef pair<int, int> ii;
typedef long long ll;

const int maxn = 2e5+5;

int n;

int arr[maxn];

ll sum[maxn];
ll qs[maxn];

int main()
{
	scanf("%d", &n);
	ll best = 0;
	for(int i = 1; i<= n; i++)
	{
		char tmp = '+';
		if(i != 1) scanf(" %c", &tmp);
		int x; scanf("%d", &x);
		if(tmp == '-') x = -x;
		arr[i] = x;
		best += arr[i];
	}
	sum[n] = abs(arr[n]);
	for(int i = n-1; i>= 1; i--)
	{
		sum[i] = sum[i+1]+abs(arr[i]);
	}
	for(int i = 1; i<= n; i++)
	{
		qs[i] = qs[i-1]+arr[i];
	}
	vector<int> neg;
	for(int i = 1; i<= n; i++) if(arr[i]< 0) neg.pb(i);
	for(int i = 0; i+1< (int) neg.size(); i++)
	{
		ll loc = 0;
		loc += arr[neg[i]];
		for(int j = neg[i]+1; j< neg[i+1]; j++)
		{
			loc -= arr[j];
		}
		// printf("[%d, %d) loc = %d\n", neg[i], neg[i+1], loc);
		best = max(best, qs[neg[i]-1]+loc+sum[neg[i+1]]);
	}
	printf("%lld\n", best);
}