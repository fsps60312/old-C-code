#include<cstdio>
#include<cassert>
#include<vector>
#include<set>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
void getmin(LL &a,const LL &b){if(b<a)a=b;}
struct Edge
{
	int a,b;
	LL cost;
	Edge(){}
	Edge(const int _a,const int _b,const LL &_cost):a(_a),b(_b),cost(_cost){}
};
vector<Edge>EDGE;
struct Pq
{
	int ei;
	LL cost;
	Pq():ei(),cost(){}
	Pq(const int _ei,const LL &_cost):ei(_ei),cost(_cost){}
	bool operator<(const Pq &p)const{return cost!=p.cost?cost<p.cost:ei<p.ei;}
};
int N,M;
vector<int>ET[100000];
LL DIST[400000];
bool VIS[400000];
set<Pq>PQ;
void Insert(const Pq &p)
{
	if(p.cost>=DIST[p.ei]||VIS[p.ei])return;
	PQ.erase(Pq(p.ei,DIST[p.ei]));
	DIST[p.ei]=p.cost;
	PQ.insert(p);
	assert((int)PQ.size()<=M*2);
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		EDGE.clear();
		for(int i=0,a,b,c;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&c),a--,b--;
			EDGE.push_back(Edge(a,b,c));
			ET[a].push_back(i*2),ET[b].push_back(i*2+1);
		}
		LL ans=INF;
		for(int i=0;i<M*2;i++)VIS[i]=false,DIST[i]=INF;
		PQ.clear();
		for(int i=0;i<(int)ET[0].size();i++)Insert(Pq(ET[0][i],EDGE[ET[0][i]>>1].cost));
		while(!PQ.empty())
		{
			const Pq p=*PQ.begin();PQ.erase(PQ.begin());
			assert(!VIS[p.ei]);
			VIS[p.ei]=true;
			const Edge &e=EDGE[p.ei>>1];
			const int u=(p.ei&1?e.a:e.b);
			if(u==N-1){getmin(ans,p.cost+e.cost);continue;}
			for(int i=0;i<(int)ET[u].size();i++)
			{
				const int ei=ET[u][i];
				const Edge &nxte=EDGE[ei>>1];
				Insert(Pq(ei,p.cost+max(e.cost,nxte.cost)));
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
