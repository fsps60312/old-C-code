#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
bool Contains(const vector<int>&s,const int val){return lower_bound(s.begin(),s.end(),val)!=upper_bound(s.begin(),s.end(),val);}
vector<int>ET[100000];
int N,M,K,A,B,DIST[100000],ANS[100000];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d%d%d%d",&N,&M,&K,&A,&B);
	K--;
	for(int i=0;i<N;i++)ET[i].clear();
	for(int i=0,a,b;i<M;i++)
	{
		scanf("%d%d",&a,&b);a--;b--;
		ET[a].push_back(b);
		ET[b].push_back(a);
	}
	for(int i=0;i<N;i++)DIST[i]=INF;
	queue<int>q;q.push(K);
	DIST[K]=0;
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		for(const int nxt:ET[u])if(DIST[nxt]==INF)
		{
			DIST[nxt]=DIST[u]+1;
			q.push(nxt);
		}
	}
	for(int i=0;i<N;i++)ANS[i]=(DIST[i]%2)*A+(DIST[i]/2)*B;
	bool *vis=new bool[N];
	for(int i=0;i<N;i++)vis[i]=false,DIST[i]=INF;
	q.push(K);
	DIST[K]=0;
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		for(const int nxt:ET[u])if(!vis[nxt])
		{
			vis[nxt]=true;
			for(const int oxt:ET[nxt])if(DIST[oxt]!=INF)
			{
				DIST[oxt]=DIST[u]+1;
				q.push(oxt);
			}
		}
	}
	delete[]vis;
	for(int i=0;i<N;i++)if(DIST[i]!=INF)getmin(ANS[i],DIST[i]*B);
	for(int i=0;i<N;i++)printf("%d\n",ANS[i]);
	return 0;
}
