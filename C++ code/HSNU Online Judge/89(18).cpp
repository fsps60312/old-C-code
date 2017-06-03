#include<cstdio>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;
const int INF=2147483647;
int N,X,Y,K;
vector<char>DIGIT,DEP;
vector<int>PRE;
int DP[2][10][901][910];
vector<int>V[2];
struct Edge
{
	int u,c;
	Edge(){}
	Edge(const int _u,const int _c):u(_u),c(_c){}
};
vector<Edge>ET[10];
inline bool Better(int a,int b)
{
	if(a==-1)return true;
	for(;a!=-1;)
	{
		if(DIGIT[a]!=DIGIT[b])return DIGIT[b]<DIGIT[a];
		if(a==b)return false;
		a=PRE[a],b=PRE[b];
	}
	assert(0);
}
int main()
{
//	N=2,X=9,Y=9,K=5;
	scanf("%d%d%d%d",&N,&X,&Y,&K);
	for(int i=0;i<10;i++)for(int j=N*9;j>=0;j--)for(int k=(N+1)*9;k>=0;k--)DP[0][i][j][k]=DP[1][i][j][k]=-1;
	V[0].clear(),V[1].clear();
	int mn=INF,mx=-INF;
	for(int i=0;i<10;i++)//initial number
	{
		ET[i].clear();
		for(int n=0,v,c;n<10;n++)//add n*k
		{
			v=i+n*K,c=v/10+v%10-i;
			ET[i].push_back(Edge(v/10,c));
			mn=min(mn,c),mx=max(mx,c);
		}
	}
	V[0].push_back(0);
	DP[0][0][0][0]=0;
	DIGIT.push_back(-1),PRE.push_back(-1),DEP.push_back(0);
	for(int d=0,digitloc=1;digitloc<=N;digitloc++,d^=1)
	{
		int bestzero=-1;
		for(int s=V[d].size()-1;s>=0;s--)
		{
			const int u=V[d][s];
			const int cost=u/10%1000;
			const int orig=u/10/1000;
			int &now=DP[d][u%10][orig][cost];
			if(u%10==0&&orig+1==X&&cost+ET[0][1].c==Y)
			{
				int uu=now;
				while(DEP[uu]+1<N)
				{
					int sz=DIGIT.size();
					DIGIT.push_back(0),PRE.push_back(uu),DEP.push_back(DEP[uu]+1);
					uu=sz;
				}
				int sz=DIGIT.size();
				DIGIT.push_back(1),PRE.push_back(uu),DEP.push_back(DEP[uu]+1);
				if(Better(bestzero,sz))bestzero=sz;
			}
			for(int i=(digitloc==N?1:0);i<10;i++)
			{
				const Edge &e=ET[u%10][i];
				if(orig+i>X||orig+i+(N-digitloc)*9<X||cost+e.c+(N-digitloc)*mn>Y||cost+e.c+(N-digitloc)*mx<Y)continue;
				const int nxt=(orig+i)*10*1000+(cost+e.c)*10+e.u;
				int &dest=DP[d^1][e.u][orig+i][cost+e.c];
				int sz=DIGIT.size();
				DIGIT.push_back(i),PRE.push_back(now),DEP.push_back(DEP[now]+1);
				if(Better(dest,sz))
				{
					if(dest==-1)V[d^1].push_back(nxt);
					dest=sz;
				}
				else DIGIT.pop_back(),PRE.pop_back(),DEP.pop_back();
			}
			now=-1;
		}
		V[d].clear();
		if(bestzero!=-1)
		{
			DP[N&1][ET[0][1].u][X][Y]=bestzero;
			break;
		}
	}
	int ans=-1;
	for(int i=0;i<10;i++)
	{
		const int dp=DP[N&1][i][X][Y];
//		printf("dp[%d]:",i);for(int j=0;j<dp.size();j++)printf(" %d",dp[j]);puts("");
		if(dp!=-1&&Better(ans,dp))
		{
			assert(DIGIT[dp]!=0);
			ans=dp;
		}
	}
	if(DEP[ans]!=N)puts("-1");
	else
	{
		int cnt=0;
		while(PRE[ans]!=-1)
		{
			printf("%c",'0'+DIGIT[ans]);
			ans=PRE[ans];
			cnt++;
		}
		assert(cnt==N);
		puts("");
	}
	return 0;
}
