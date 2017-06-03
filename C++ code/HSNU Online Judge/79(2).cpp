#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
int N,S,K,FA[100000],W[100000];
vector<int>ET[100000],H[100000];
queue<int>COVER[100000][21];
void BuildH(const int &u,const int &fa,const int &dep)
{
	FA[u]=fa;
	H[dep].push_back(u);
	for(int i=0;i<ET[u].size();i++)
	{
		const int &nxt=ET[u][i];
		if(nxt==fa)continue;
		BuildH(nxt,u,dep+1);
	}
}
bool PutWeapon(int s)
{
	for(int i=0;;i++)
	{
		for(int k=i;k<=K;k++)
		{
			queue<int>&q=COVER[s][k];
			while(!q.empty())
			{
				if(W[q.front()]){W[q.front()]--;return false;}
				else q.pop();
			}
		}
		if(i==K)break;
		s=FA[s];
	}
	W[s]+=S;
	for(int i=0;i<=K;i++,s=FA[s])
	{
		COVER[s][K-i].push(s);
	}
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&N,&S,&K)==3)
	{
		for(int i=0;i<N;i++)
		{
			W[i]=0;
			ET[i].clear(),H[i].clear();
			for(int j=0;j<=K;j++)COVER[i][j]=queue<int>();
		}
		for(int i=1,a,b;i<N;i++)
		{
			scanf("%d%d",&a,&b);
			a--,b--;
			ET[a].push_back(b);
			ET[b].push_back(a);
		}
		BuildH(0,0,0);
		int ans=0;
		for(int h=N-1;h>=0;h--)
		{
			for(int j=0;j<H[h].size();j++)
			{
				const int &u=H[h][j];
				if(PutWeapon(u))ans++;
			}
		}
		printf("%d\n",ans);
		break;
	}
	return 0;
}