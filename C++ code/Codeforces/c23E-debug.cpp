#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=7e2+10;
const int mod=1e4;
struct Edge{
	int v;
	int next;
	Edge(){}
	Edge(int next,int v): next(next),v(v){}
}e[maxn<<1];
int head[maxn],E_cnt;
int sz[maxn<<1];
struct Bign{
	int a[80],n;
	Bign(){}
	Bign(int x)
	{
		memset(a,0,sizeof(a));
		n=1;a[0]=x;
	}
	void init(int x)
	{
		n=1;a[0]=x;
	}
	bool operator < (const Bign& x)
	{
		if (n<x.n)
			return 1;
		else
			if (n>x.n)
				return 0;
			else
			{
				for (int i=n-1;i>=0;i--)//?最高位?始找不同?位 
					if (a[i]<x.a[i])
						return 1;
					else
						if (a[i]>x.a[i])
							return 0;
			}
		return 0;
	}
	Bign operator + (const Bign& x)
	{
		Bign t(0);
		t.n=max(n,x.n);
		for (int i=0;i<t.n;i++)
		{
			t.a[i]=t.a[i]+a[i]+x.a[i];
			t.a[i+1]+=t.a[i]/mod;
			t.a[i]%=mod;
		}
		if (t.a[t.n])
			t.n++;
		return t;
	}
	Bign operator * (const Bign& x)
	{
		Bign t(0);
		t.n=n+x.n-1;
		for (int i=0;i<n;i++)
			for (int j=0;j<x.n;j++)
				t.a[i+j]+=a[i]*x.a[j];//乘到i+j位 
		for (int i=0;i<t.n;i++)
		{
			t.a[i+1]+=t.a[i]/mod;
			t.a[i]%=mod;
		}
		if (t.a[t.n])
			t.n++;
		return t;
	}
	void print()
	{
		printf("%d",a[n-1]);
		for (int i=n-2;i>=0;i--)
			printf("%04d",a[i]);
		puts(" ");
	}
}dp[maxn][maxn];
void AddEdge(int u,int v)
{
	e[++E_cnt]=Edge(head[u],v);
	head[u]=E_cnt;
	e[++E_cnt]=Edge(head[v],u);
	head[v]=E_cnt;
}
void tree_dp(int u,int fa)
{
	sz[u]=1;
	dp[u][0].init(0);
	dp[u][1].init(1);
	for (int x=head[u];x;x=e[x].next)
	{
		int v=e[x].v;
		if (v!=fa)
		{
			tree_dp(v,u);
			for (int i=sz[u];i>=0;i--)
				for (int j=sz[v];j>=0;j--)
					dp[u][i+j]=(dp[u][i+j]<dp[u][i]*dp[v][j]) ? dp[u][i]*dp[v][j]:dp[u][i+j];//考?新增子?最优解 
			sz[u]+=sz[v];
		}	
	}
	for (int i=sz[u];i>=1;i--)
	{
		Bign tmp(i);
		tmp=tmp*dp[u][i];
		dp[u][0]=(dp[u][0]<tmp) ? tmp:dp[u][0];
	}
}
int main()
{
	int n,u,v;
	scanf("%d",&n);
	for (int i=1;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		AddEdge(u,v);
	}
	tree_dp(1,0);
	dp[1][0].print();
	return 0;
}
s
