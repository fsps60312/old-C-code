#include<cstdio>
#include<vector>
#include<queue>
#include<cmath>
//#include<cassert>
using namespace std;
void assert(bool valid){if(valid)return;while(1)printf("E");}
const int INF=2147483647;
const double EPS=1e-9;
void getmin(int &a,int b){if(b<a)a=b;}
struct Point
{
	int x,y,z;
	Point(){}
	Point(int x,int y,int z):x(x),y(y),z(z){}
	void Scanf(){scanf("%d%d%d",&x,&y,&z);}
}BEGIN,END;
int T,N;
struct Warmhole
{
	Point entry,exit;
	int creation,shift;
	void Scanf()
	{
		entry.Scanf(),exit.Scanf();
		scanf("%d%d",&creation,&shift);
	}
};
vector<Warmhole>WARMHOLE;
int Hypot(int a,int b,int c){double v=sqrt(a*a+b*b+c*c);if(abs(v-(int)v)<EPS)return (int)v;return (int)(v+1.0);}
int Dis(Point &a,Point &b){return Hypot(a.x-b.x,a.y-b.y,a.z-b.z);}
struct Edge
{
	int to,creation,shift,cost;
	Edge(int to=0,int creation=0,int shift=0,int cost=0):to(to),creation(creation),shift(shift),cost(cost){}
};
vector<Edge>AD[50];
int TIME[50],UPRE[50],CPRE[50],CNT[50],LPRE[50];
bool INQ[50];
int Solve()
{
	static int vis_cnt,vis[50];
	vis_cnt=0;
	queue<int>q;
	for(int i=0;i<N;i++)
	{
		q.push(i);
		Warmhole &w=WARMHOLE[i];
		TIME[i]=min(Dis(BEGIN,w.exit),max(w.creation,Dis(BEGIN,w.entry))+w.shift);
		UPRE[i]=-1;
		INQ[i]=true;
		CNT[i]=0;
		vis[i]=0;
	}
	while(!q.empty())
	{
		int u=q.front();q.pop();
		INQ[u]=false,CNT[u]++;
//printf("u=%d,TIME=%d\n",u,TIME[u]);
		if(CNT[u]>=N)
		{
//printf("CUT[%d]=%d>=%d\n",u,CNT[u],N);
			vis_cnt++;
			vis[u]=vis_cnt;
			for(int i=UPRE[u];;i=UPRE[i])
			{
//				printf("now at %d\n",i);
				if(vis[i]==vis_cnt){u=i;break;}
				vis[i]=vis_cnt;
			}
			vector<int>loop;
			loop.push_back(u);
			for(int i=UPRE[u];i!=u;i=UPRE[i])loop.push_back(i);
//for(int i=0;i<loop.size();i++)printf(" %d",loop[i]);puts("");
			for(int i=0;i<loop.size();i++)CNT[loop[i]]=0;
			int mn=INF,idx=-1;
			for(int i=0;i<loop.size();i++)
			{
				int &j=UPRE[loop[i]];
				if(CPRE[j]==-INF)continue;
				else if(TIME[j]-(LPRE[j]+CPRE[j])<mn)mn=TIME[j]-(LPRE[j]+CPRE[j]),idx=j;
			}
//printf("idx=%d,mn=%d\n",idx,mn);
			if(mn>0)
			{
				assert(idx!=-1);
				TIME[idx]-=mn;
//printf("TIME[%d]=%d\n",idx,TIME[idx]);
				u=idx;
			}
		}
		for(int i=0;i<AD[u].size();i++)
		{
			Edge &e=AD[u][i];
			int time=max(TIME[u]+e.cost,e.creation)+e.shift;
			if(time>=TIME[e.to])continue;
			TIME[e.to]=time;
			UPRE[e.to]=u;
			CPRE[e.to]=e.creation;
			LPRE[e.to]=e.cost;
			if(!INQ[e.to])INQ[e.to]=true,q.push(e.to);
		}
	}
	int ans=Dis(BEGIN,END);
	for(int i=0;i<N;i++)
	{
		Warmhole &w=WARMHOLE[i];
		if(TIME[i]+Dis(w.exit,END)<ans)ans=TIME[i]+Dis(w.exit,END);
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			BEGIN.Scanf(),END.Scanf();
			scanf("%d",&N);
			WARMHOLE.clear();
			for(int i=0;i<N;i++)
			{
				static Warmhole w;
				w.Scanf();
				WARMHOLE.push_back(w);
			}
			for(int i=0;i<N;i++)AD[i].clear();
			for(int i=0;i<N;i++)
			{
				for(int j=0;j<N;j++)
				{
					Warmhole &w1=WARMHOLE[i],&w2=WARMHOLE[j];
					AD[i].push_back(Edge(j,-INF,0,Dis(w1.exit,w2.exit)));
					AD[i].push_back(Edge(j,w2.creation,w2.shift,Dis(w1.exit,w2.entry)));
				}
			}
			printf("%d\n",Solve());
		}
	}
	return 0;
}
