#include<cstdio>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;
typedef long long LL;
const LL INF=1000000000000000LL;//9223372036854775807LL;
void getmin(LL &a,const LL &b){if(b<a)a=b;}
void getmax(LL &a,const LL &b){if(b>a)a=b;}
LL Gcd(const LL &a,const LL &b){return b==0LL?a:Gcd(b,a%b);}
void bssert(bool valid){if(valid)return;for(;;)putchar('E');}
struct Edge
{
	int to;
	LL cost;
	Edge(){}
	Edge(const int _t,const LL &_c):to(_t),cost(_c){}
};
struct Djset
{
	int s[1000];
	void clear(const int n){for(int i=0;i<n;i++)s[i]=i;}
	int Find(const int a){return s[a]==a?a:(s[a]=Find(s[a]));}
	bool Merge(int a,int b){if((a=Find(a))==(b=Find(b)))return false;s[a]=b;}
}DJSET;
struct Hungary
{
	int M,N;
	vector<Edge>EA[500],EB[500];
	LL WA[500],WB[500],LOW[500];
	int MATCH[500];
	bool VA[500],VB[500];
	bool Match(const int u)
	{
		if(VA[u])return false;
		VA[u]=true;
		for(int i=0;i<(int)EA[u].size();i++)
		{
			const Edge &e=EA[u][i];
			if(e.cost==WA[u]+WB[e.to])
			{
				VB[e.to]=true;
				if(MATCH[e.to]==-1||Match(MATCH[e.to]))
				{
					MATCH[e.to]=u;
					return true;
				}
			}
			else
			{
				assert(e.cost<WA[u]+WB[e.to]);
				getmin(LOW[e.to],WA[u]+WB[e.to]-e.cost);
			}
		}
		return false;
	}
	void Update()
	{
		LL low=INF;
		for(int i=0;i<N;i++)if(!VB[i])getmin(low,LOW[i]);
		assert(low!=INF);//sth. wrong here
		for(int i=0;i<M;i++)if(VA[i])WA[i]-=low;
		for(int i=0;i<N;i++)if(VB[i])WB[i]+=low;
	}
	void Solve()
	{
		DJSET.clear(M+N);
		for(int i=0;i<M;i++)for(const Edge &e:EA[i])DJSET.Merge(i,M+e.to);
		for(int i=0;i<M;i++)WA[i]=INF;
		for(int i=0;i<N;i++)WB[i]=0,MATCH[i]=-1;
		for(int i=0;i<M;i++)
		{
			if(EA[i].empty()){WA[i]=0LL;continue;}
			for(;;)
			{
				for(int j=0;j<M;j++)VA[j]=false;
				for(int j=0;j<N;j++)VB[j]=false,LOW[j]=INF;
				if(Match(i))break;
				else Update();
				const int gn=DJSET.Find(EA[i][0].to);
				bool found=false;
				for(int j=0;j<N;j++)if(DJSET.Find(M+j)==gn&&MATCH[j]==-1){found=true;break;}
				if(!found)
				{
					WA[i]=0LL;
					for(const Edge &e:EA[i])getmax(WA[i],e.cost-WB[e.to]);
					break;
				}
			}
		}
	}
	LL GetSum()
	{
		LL ans=0LL;
		for(int i=0;i<M;i++)ans+=WA[i];
		for(int i=0;i<N;i++)ans+=WB[i];
		return ans;
	}
}HUNGARY;
const LL BASE=2*2*2*3*3*5*7;
int N,M,K;
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	static int casecount;scanf("%d",&casecount);
	while(casecount--)
	{
		scanf("%d%d%d",&M,&N,&K);
		HUNGARY.M=M,HUNGARY.N=N;
		for(int i=0;i<M;i++)HUNGARY.EA[i].clear();
		for(int i=0;i<N;i++)HUNGARY.EB[i].clear();
		for(int i=0,a,b;i<K;i++)
		{
			static LL q,p;
			scanf("%d%d%lld%lld",&a,&b,&q,&p);
			bssert(p>=1LL&&p<=10LL);
			a--,b--;
			bssert(a>=0&&a<M&&b>=0&&b<N);
			const LL cost=q*(BASE/p);
			HUNGARY.EA[a].push_back(Edge(b,cost));
			HUNGARY.EB[b].push_back(Edge(a,cost));
		}
		HUNGARY.Solve();
		LL ans=HUNGARY.GetSum();
		LL g=Gcd(ans,BASE);
		printf("%lld %lld\n",ans/g,BASE/g);
	}
	return 0;
}
