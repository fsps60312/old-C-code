#include<cstdio>
#include<cassert>
#include<map>
#include<utility>
using namespace std;
int K;
namespace SegTree
{
	map<int,int>D;
	inline int GetC(const int i)
	{
		auto it=D.upper_bound(i);
		assert(it!=D.begin());
		return (--it)->second;
	}
	int C[700000][100],TAG[700000];
	inline void Rebuild(const int id,const int loc)
	{
		TAG[id]=-1;
		for(int i=0;i<K*K;i++)C[id][i]=0;
		++C[id][GetC(loc)*K+GetC(loc+1)];
	}
	inline void SetTag(const int id,const int c,const int cnt)
	{
		TAG[id]=c;
		for(int i=0;i<K*K;i++)C[id][i]=0;
		C[id][c*K+c]=cnt;
	}
	inline void Maintain(const int id)
	{
		TAG[id]=-1;
//		assert(TAG[id]==-1);
		for(int i=0;i<K*K;i++)C[id][i]=C[id*2][i]+C[id*2+1][i];
	}
	int N;
	void Build(const int id,const int l,const int r)
	{
		if(l==r)
		{
			Rebuild(id,r);
			return;
		}
		else
		{
			const int mid=(l+r)/2;
			Build(id*2,l,mid),Build(id*2+1,mid+1,r);
			Maintain(id);
		}
	}
	void Build(const int _N,const char *str)
	{
		N=_N;
		D.clear();
		for(int i=0;i<N;i++)D[i]=str[i]-'a';
		Build(1,0,N-2);
	}
	void PutDown(const int id,const int l,const int mid,const int r)
	{
		if(TAG[id]==-1)return;
		const int c=TAG[id];TAG[id]=-1;
		SetTag(id*2,c,mid-l+1),SetTag(id*2+1,c,r-mid);
	}
	void ModifyOne(const int id,const int l,const int r,const int loc)
	{
		if(l==r)
		{
			assert(loc==r);
			Rebuild(id,loc);
			return;
		}
		else
		{
			const int mid=(l+r)/2;
			PutDown(id,l,mid,r);
			if(loc<=mid)ModifyOne(id*2,l,mid,loc);
			else ModifyOne(id*2+1,mid+1,r,loc);
			Maintain(id);
		}
	}
	void ModifyToSame(const int id,const int l,const int r,const int bl,const int br,const int c)
	{
		if(r<bl||br<l)return;
		if(bl<=l&&r<=br)
		{
			SetTag(id,c,r-l+1);
			return;
		}
		const int mid=(l+r)/2;
		PutDown(id,l,mid,r);
		ModifyToSame(id*2,l,mid,bl,br,c),ModifyToSame(id*2+1,mid+1,r,bl,br,c);
		Maintain(id);
	}
	void Modify(const int l,const int r,const int c)
	{
		if(r+1<N)
		{
			const int t=GetC(r+1);
			D[r+1]=t;
		}
		D[l]=c;
		auto it=D.find(l);
		for(++it;it!=D.end()&&it->first<=r;)D.erase(it++);
		if(l-1>=0)ModifyOne(1,0,N-2,l-1);
		if(r+1<N)ModifyOne(1,0,N-2,r);
		ModifyToSame(1,0,N-2,l,r-1,c);
	}
};
int N,M;
char S[200001];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&N,&M,&K)==3)
	{
		scanf("%s",S);
		SegTree::Build(N,S);
		for(int type;M--;)
		{
			scanf("%d",&type);
			if(type==1)
			{
				int l,r;
				static char c[2];
				scanf("%d%d%s",&l,&r,c),--l,--r;
				SegTree::Modify(l,r,c[0]-'a');
			}
			else if(type==2)
			{
				static char s[11];
				scanf("%s",s);
				static int loc[11];
				for(int i=0;i<K;i++)loc[s[i]-'a']=i;
				int ans=1;
				for(int i=0;i<K*K;i++)if(loc[i/K]>=loc[i%K])ans+=SegTree::C[1][i];
				printf("%d\n",ans);
			}
			else assert(0);
		}
	}
}
