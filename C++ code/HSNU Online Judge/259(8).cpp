#include<cstdio>
#include<vector>
#include<algorithm>
#include<set>
#include<cassert>
using namespace std;
typedef long long LL;
struct Sail
{
	int h,cnt;
	Sail(){}
	Sail(const int _h,const int _c):h(_h),cnt(_c){}
	bool operator<(const Sail &s)const{return h<s.h;} 
};
int N;
vector<Sail>SAIL;
struct Seg
{
	int s[400000];
	void Build(const int id,const int l,const int r)
	{
		s[id]=0;
		if(l==r)return;
		const int mid=(l+r)/2;
		Build(id*2,l,mid),Build(id*2+1,mid+1,r);
	}
	void Add(const int id,const int l,const int r,const int bl,const int br)
	{
		if(l>br||r<bl)return;
		if(bl<=l&&r<=br){s[id]++;return;}
		const int mid=(l+r)/2;
		Add(id*2,l,mid,bl,br),Add(id*2+1,mid+1,r,bl,br);
	}
	void Add(const int bl,const int br){Add(1,0,99999,bl,br);}
	void Output(const int id,const int l,const int r,LL *result)
	{
		if(l==r){result[l]=s[id];return;}
		s[id*2]+=s[id],s[id*2+1]+=s[id],s[id]=0;
		const int mid=(l+r)/2;
		Output(id*2,l,mid,result),Output(id*2+1,mid+1,r,result);
	}
	int Query(const int id,const int l,const int r,const int loc)
	{
		if(l==r)return s[id];
		const int mid=(l+r)/2;
		return s[id]+(loc<=mid?Query(id*2,l,mid,loc):Query(id*2+1,mid+1,r,loc));
	}
	int Query(const int loc){return Query(1,0,99999,loc);}
}SEG;
LL ANS[100000];
void Erase(set<int>&s,int v){assert(s.find(v)!=s.end()),s.erase(v);}
void Insert(set<int>&s,int v){assert(s.find(v)==s.end()),s.insert(v);}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0,h,c;i<N;i++)
	{
		scanf("%d%d",&h,&c);
		SAIL.push_back(Sail(h,c));
	}
	sort(SAIL.begin(),SAIL.end());
	set<int>joint;
	joint.insert(0);
	SEG.Build(1,0,99999);
	for(const Sail &sail:SAIL)
	{
		auto upbound=joint.upper_bound(sail.h-sail.cnt),lowbound=joint.lower_bound(sail.h-sail.cnt);
		int l,r;
		assert(upbound!=joint.begin());
		l=*(--upbound);
		r=(lowbound==joint.end()?sail.h:*lowbound);
		int stable=sail.h-r,unstable=sail.cnt-stable;
		assert(l+unstable<=r);
		SEG.Add(l,l+unstable-1);
		SEG.Add(r,sail.h-1);
		if(unstable)
		{
			if(l!=0&&SEG.Query(l-1)==SEG.Query(l))joint.erase(l);
			joint.insert(l+unstable);
		}
		if(stable)
		{
			if(r!=0&&SEG.Query(r-1)==SEG.Query(r))joint.erase(r);
			joint.insert(sail.h);
		}
//		printf("(%d,%d),(%d,%d)\n",l,l+unstable,r,sail.h);
//		for(auto v:joint)printf(" %d",v);puts("");
	}
	SEG.Output(1,0,99999,ANS);
	LL ans=0LL;
	for(int i=0;i<=99999;i++)ans+=ANS[i]*(ANS[i]-1LL)/2LL;
	printf("%lld\n",ans);
	return 0;
}
