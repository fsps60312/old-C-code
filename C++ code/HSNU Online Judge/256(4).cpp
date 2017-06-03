#include<cstdio>
#include<cassert>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long LL;
void getmax(LL &a,const LL b){if(b>a)a=b;}
int B,N,D,M;
int X[100000][3];
struct Deq
{
	int s[100000],l,r;
	void clear(){l=0,r=-1;}
	void push_back(const int v){s[++r]=v;}
	int pop_front(){return s[l++];}
	int back(){return s[r];}
	int front(){return s[l];}
	bool empty(){return r<l;}
	int size(){return r-l+1;}
}DEQ;
bool Cmp1(const int a,const int b){return X[a][0]<X[b][0];}
LL Solve1()
{
	vector<int>idx;
	for(int i=0;i<N;i++)idx.push_back(i);
	sort(idx.begin(),idx.end(),Cmp1);
	DEQ.clear();
	LL ans=0LL;
	for(const auto i:idx)
	{
		while(!DEQ.empty()&&X[DEQ.front()][0]<X[i][0]-D)DEQ.pop_front();
		ans+=DEQ.size();
		DEQ.push_back(i);
	}
	return ans;
}
struct Seg
{
	int s[600000];
	void Build(const int id,const int l,const int r)
	{
		s[id]=0;
		if(l==r)return;
		const int mid=(l+r)/2;
		Build(id*2,l,mid),Build(id*2+1,mid+1,r);
	}
	void Add(const int id,const int l,const int r,const int bl,const int br,const int v)
	{
		if(l>br||r<bl)return;
		if(bl<=l&&r<=br){s[id]+=v;return;}
		const int mid=(l+r)/2;
		Add(id*2,l,mid,bl,br,v),Add(id*2+1,mid+1,r,bl,br,v);
	}
	int Query(const int id,const int l,const int r,const int loc)
	{
		if(l==r)return s[id];
		const int mid=(l+r)/2;
		if(loc<=mid)return s[id]+Query(id*2,l,mid,loc);
		else return s[id]+Query(id*2+1,mid+1,r,loc);
	}
}SEG;
bool Cmp2(const int a,const int b){return X[a][0]+X[a][1]<X[b][0]+X[b][1];}
LL Solve2()
{
	vector<int>idx;
	for(int i=0;i<N;i++)idx.push_back(i);
	sort(idx.begin(),idx.end(),Cmp2);
	SEG.Build(1,1,M*2-1);
	LL ans=0LL;
	DEQ.clear();
	for(const auto i:idx)
	{
		while(!DEQ.empty()&&(X[i][0]+X[i][1])-(X[DEQ.front()][0]+X[DEQ.front()][1])>D)
		{
			const int v=DEQ.pop_front();
			const int mid=M+X[v][0]-X[v][1];
			SEG.Add(1,1,M*2-1,mid-D,mid+D,-1);
		}
		const int mid=M+X[i][0]-X[i][1];
		int ta=ans;
		ans+=SEG.Query(1,1,M*2-1,mid);
		SEG.Add(1,1,M*2-1,mid-D,mid+D,1);
		DEQ.push_back(i);
	}
	return ans;
}
LL Solve3()
{
	LL ans=0LL;
	for(int i=0;i<N;i++)
	{
		for(int j=i+1;j<N;j++)
		{
			if(abs(X[i][0]-X[j][0])+abs(X[i][1]-X[j][1])+abs(X[i][2]-X[j][2])<=D)ans++;
		}
	}
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d%d",&B,&N,&D,&M)==4)
	{
		for(int i=0;i<N;i++)for(int j=0;j<B;j++)scanf("%d",&X[i][j]),X[i][j]--;
		if(B==1)printf("%lld\n",Solve1());
		else if(B==2)printf("%lld\n",Solve2());
		else if(B==3)printf("%lld\n",Solve3());
		else assert(0);
	}
	return 0;
}