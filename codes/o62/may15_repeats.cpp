#include <bits/stdc++.h>
using namespace std;
#define X first
#define Y second
#define pb push_back
typedef pair<int, int> ii;
typedef long long ll;

const int maxn = 1e3+5;

int k;
int ans[maxn];
char s[maxn];
int n;

int match = 0;

set<int> pos[26];

void add(char x, int ind, int tar)
{
	int buck = x-'a';
	pos[buck].insert(ind);
	if(pos[buck].find(tar) != pos[buck].end())
	{
		match++;
	}
}

void rm(char x, int ind, int tar)
{
	int buck = x-'a';
	if(pos[buck].find(tar) != pos[buck].end())
	{
		match--;
	}
	pos[buck].erase(ind);
}

int main()
{
	scanf("%d", &k);
	scanf("%s", s+1);
	n = strlen(s+1);
	for(int len = 2; len<= n; len += 2)
	{
		for(int i = 0; i< 26; i++) pos[i].clear();
		match = 0;
		for(int i = 1; i<= len/2; i++)
		{
			add(s[i], i, i+len/2);
		}
		for(int i = len/2+1; i<= len; i++)
		{
			add(s[i], i, i-len/2);
		}
		ans[len/2-match]++;
		for(int i = 2; i+len-1<= n; i++)
		{
			rm(s[i-1], i-1, (i-1)+len/2);
			add(s[i+len-1], i+len-1, i+len-1-len/2);
			ans[len/2-match]++;
		}
	}
	int res = 0;
	for(int i = 0; i<= k; i++) res += ans[i];
	printf("%d\n", res);
}