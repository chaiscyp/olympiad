#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")
using namespace std;
#define X first
#define Y second
#define pb push_back
typedef pair<int, int> ii;
typedef long long ll;

struct node
{
	ll sum, opt;
	int a, b, pr;
	node *left, *right;
	node(int a, int b) : a(a), b(b)
	{
		pr = (rand()<<16)^rand();
		sum = a; opt = 1LL*a+b;
		left = right = NULL;
	}
	void calc()
	{
		sum = 1LL*a+(left?left->sum:0LL)+(right?right->sum:0LL);
		ll tmp = 1LL*a+b;
		opt = 0;
		if(right) opt = max(opt, right->opt);
		opt = max(opt, (right?right->sum:0LL)+tmp);
		ll run = (right?right->sum:0LL)+a;
		if(left) opt = max(opt, run+(left->opt));
	}
};

typedef node* ps;

ps merge(ps L, ps R)
{
	if(!L || !R) return L?L:R;
	if(L->pr> R->pr)
	{
		L->right = merge(L->right, R);
		L->calc();
		return L;
	}
	else
	{
		R->left = merge(L, R->left);
		R->calc();
		return R;
	}
}

pair<ps, ps> split(node *big, int key)
{
	if(!big) return {big, big};
	int here = big->b;
	if(here<= key)
	{
		auto tmp = split(big->right, key);
		big->right = tmp.X;
		big->calc();
		return {big, tmp.Y};
	}
	else
	{
		auto tmp = split(big->left, key);
		big->left = tmp.Y;
		big->calc();
		return {tmp.X, big};
	}
}

ps root = NULL;

int main()
{
	srand(time(NULL));
	int n, t, m1, m2;
	scanf("%d %d %d %d", &n, &t, &m1, &m2);
	ll last = 0;
	for(int i = 1; i<= n; i++)
	{
		int x, y; scanf("%d %d", &x, &y);
		int a, b;
		if(t == 1) 
		{
			a = x; b = y;
		}
		else
		{
			a = x+(last%m1); b = y+(last%m2);
		}
		auto tmp = split(root, b);
		root = merge(tmp.X, new node(a, b));
		root = merge(root, tmp.Y);
		last = root->opt;
		printf("%lld\n", root->opt);
	}
}