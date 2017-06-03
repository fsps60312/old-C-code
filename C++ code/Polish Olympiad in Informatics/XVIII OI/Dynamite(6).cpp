#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;
const int INF=2147483647;
template<class T>void getmax(T &a,const T &b){if(b>a)a=b;}
template<class T>void getmin(T &a,const T &b){if(b<a)a=b;}
int N,M,D[300000];
vector<int>ET[300000];
namespace WeightPoint
{
	void DfsWeightPoint(const int u,const int parent,const bool *vis,vector<int>&sums,vector<int>&mxszs,vector<int>&nodes)
	{
		int sum=1,mxsz=0;
		for(int i=0;i<(int)ET[u].size();i++)if(ET[u][i]!=parent&&!vis[ET[u][i]])
		{
			DfsWeightPoint(ET[u][i],u,vis,sums,mxszs,nodes);
			sum+=sums.back(),getmax(mxsz,sums.back());
		}
		sums.push_back(sum),mxszs.push_back(mxsz),nodes.push_back(u);
	}
	int FindWeightPoint(const int u,const bool *vis)
	{
		vector<int>sums,mxszs,nodes;
		DfsWeightPoint(u,-1,vis,sums,mxszs,nodes);
		const int n=sums.back();
		assert(n==(int)sums.size()&&n==(int)mxszs.size()&&n==(int)nodes.size());
		for(int i=0;i<n;i++)getmax(mxszs[i],n-sums[i]);
		pair<int,int>ans=make_pair(INF,-1);
		for(int i=0;i<n;i++)getmin(ans,make_pair(mxszs[i],nodes[i]));
		assert(ans.second!=-1);
		return ans.second;
	}
	int PARENT[300000];
	void BuildTree(const int u,const int parent,bool *vis)
	{
		const int root=FindWeightPoint(u,vis);
		PARENT[root]=parent;
		vis[root]=true;
		for(int i=0;i<(int)ET[root].size();i++)if(!vis[ET[root][i]])BuildTree(ET[root][i],root,vis);
	}
	int DIST[300000];
	void BuildTree()
	{
		static bool vis[300000];
		for(int i=0;i<N;i++)vis[i]=false;
		BuildTree(0,-1,vis);
	}
}
namespace Depth
{
	int DEPTH[600000],M;
	struct SegTree
	{
		int S[2400000];
		void Build(const int id,const int l,const int r)
		{
			if(l==r){S[id]=DEPTH[r];return;}
			const int mid=(l+r)/2;
			Build(id*2,l,mid),Build(id*2+1,mid+1,r);
			S[id]=min(S[id*2],S[id*2+1]);
		}
		int Query(const int id,const int l,const int r,const int bl,const int br)const
		{
			if(r<bl||br<l)return INF;
			if(bl<=l&&r<=br)return S[id];
			const int mid=(l+r)/2;
			return min(Query(id*2,l,mid,bl,br),Query(id*2+1,mid+1,r,bl,br));
		}
	}SEG;
	int LOCS[300000],PARENT[300000];
	void DfsDepth(const int u,const int parent,const int depth)
	{
		DEPTH[LOCS[u]=M++]=depth;
		PARENT[u]=parent;
		for(int i=0;i<(int)ET[u].size();i++)if(ET[u][i]!=parent)
		{
			DfsDepth(ET[u][i],u,depth+1);
			DEPTH[LOCS[u]=M++]=depth;
		}
	}
	void BuildDepth()
	{
		M=0;
		DfsDepth(0,-1,0);
		SEG.Build(1,0,M-1);
	}
	int QueryLength(const int va,const int vb)
	{
		int a=LOCS[va],b=LOCS[vb];
//		printf("dist(%d,%d)=%d\n",va+1,vb+1,DEPTH[a]+DEPTH[b]-2*SEG.Query(1,0,M-1,min(a,b),max(a,b)));
		return DEPTH[a]+DEPTH[b]-2*SEG.Query(1,0,M-1,min(a,b),max(a,b));
	}
	bool CmpDepth(const int a,const int b){return DEPTH[LOCS[a]]>DEPTH[LOCS[b]];}
}
int QueryMinDist(const int _a)
{
	int ans=INF;
	for(int a=_a;a!=-1;a=WeightPoint::PARENT[a])if(WeightPoint::DIST[a]!=INF)getmin(ans,WeightPoint::DIST[a]+Depth::QueryLength(a,_a));
	return ans;
}
void UpdateMinDist(const int _a)
{
	for(int a=_a;a!=-1;a=WeightPoint::PARENT[a])getmin(WeightPoint::DIST[a],Depth::QueryLength(a,_a));
}
bool Solve(const int len)
{
	for(int i=0;i<N;i++)WeightPoint::DIST[i]=INF;
	static int order[300000];
	int m=0;
	for(int i=0;i<N;i++)if(D[i])order[m++]=i;
	sort(order,order+m,Depth::CmpDepth);
	int ans=0;
	for(int _i=0;_i<m;_i++)
	{
		const int u=order[_i];
//		printf("u=%d,mindist=%d\n",u+1,QueryMinDist(u));
		if(QueryMinDist(u)<=len)continue;
		if(++ans>M)return false;
		int cur=u;
		for(int i=0;i<len&&Depth::PARENT[cur]!=-1;i++,cur=Depth::PARENT[cur]);
		UpdateMinDist(cur);
//		++ans;
//		printf("set on %d\n",cur+1);
	}
//	printf("len=%d,ans=%d\n",len,ans);
//	return ans<=M;
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)scanf("%d",&D[i]);
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<N-1;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			ET[a].push_back(b),ET[b].push_back(a);
		}
		WeightPoint::BuildTree();
		Depth::BuildDepth();
		int l=0,r=N-1;
		while(l<r)
		{
			const int mid=(l+r)/2;
			if(Solve(mid))r=mid;
			else l=mid+1;
		}
		printf("%d\n",r);
	}
	return 0;
}
