#include <bits/stdc++.h>
using namespace std;
#define X first
#define Y second
#define pb push_back
typedef pair<int, int> ii;
typedef long long ll;

int n, k;

const int maxn = 1e5+5;
vector< vector<int> > arr;
int val[maxn];
vector<int> all;

int numone(vector<int> &A)
{
	int res = 0;
	for(int i = 0; i< k; i++) res += A[i];
	return res;
}

bool cmp(vector<int> &A, vector<int> &B)
{
	int na = 0, nb = 0;
	for(int i = 0; i< k; i++)
	{
		na += A[i]; nb += B[i];
	}
	return na< nb;
}

int rngx[35], rngy[35];

int cum[35];

int ok[35];

vector<int> buck[maxn];
int main()
{
	scanf("%d %d", &n, &k);
	arr.resize(n);
	for(int i = 0; i< n; i++)
	{
		arr[i].resize(k);
		int tot = 0;
		for(int j = 0; j< k; j++)
		{
			scanf("%1d", &arr[i][j]);
			tot *= 2;
			tot += arr[i][j];
		}
		all.pb(tot);
		val[i] = tot;
	}
	sort(all.begin(), all.end());
	all.erase(unique(all.begin(), all.end()), all.end());
	for(int i = 0; i< n; i++)
	{
		int pos = lower_bound(all.begin(), all.end(), val[i])-all.begin();
		buck[pos].pb(i+1);
	}
	sort(arr.begin(), arr.end());
	arr.erase(unique(arr.begin(), arr.end()), arr.end());
	sort(arr.begin(), arr.end(), cmp);
	if(arr.size() == 1)
	{
		printf("-1\n");
		return 0;
	}
	int m = arr.size();
	for(int i = 0; i< 35; i++) rngx[i] = 1e9;
	for(int i = 0; i< m; i++)
	{
		int q = numone(arr[i]);
		rngx[q] = min(rngx[q], i);
		rngy[q] = max(rngy[q], i);
	}
	int dat = 0;
	bool first = true;
	for(int i = k; i>= 0; i--)
	{
		if(rngx[i] == 1e9) continue;
		bool bad = true;
		if(first)
		{
			bad = false;
			first = false;	
		}
		else
		{
			for(int j = rngx[i]; j<= rngy[i]; j++)
			{
				for(int q = 0; q< k; q++)
				{
					if(arr[j][q] == 1 && cum[q])
					{
						bad = false;
						break;
					}
				}
			}
		}
		ok[i] = !bad;
		if(ok[i])
		{
			for(int j = rngx[i]; j<= rngy[i]; j++)
			{
				for(int q = 0; q< k; q++)
				{
					if(arr[j][q] == 0) cum[q]++;
				}
			}
			for(int num = i+1; num<= k; num++)
			{
				if(ok[num]) continue;
				ok[num] = true;
				for(int j = rngx[num]; j<= rngy[num]; j++)
				{
					for(int q = 0; q< k; q++)
					{
						if(arr[j][q] == 0) cum[q]++;
					}
				}
			}
		}
	}
	vector<int> ans;
	for(int num = 0; num<= k; num++)
	{
		if(!ok[num]) continue;
		for(int i = rngx[num]; i<= rngy[num]; i++)
		{
			int tot = 0;
			for(int j = 0; j< k; j++)
			{
				tot *= 2;
				tot += arr[i][j];
			}
			int pos = lower_bound(all.begin(), all.end(), tot)-all.begin();
			for(int x : buck[pos])
			{
				ans.pb(x);
			}
		}
	}
	sort(ans.begin(), ans.end());
	for(int x : ans) printf("%d ", x);
	printf("\n");
}