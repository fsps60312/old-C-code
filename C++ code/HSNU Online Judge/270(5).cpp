#include<cstdio>
#include<vector>
#include<cmath>
#include<map>
#include<queue>
#include<algorithm>
using namespace std;
int N,R,Q,REGION[200000],BOSS[200000],INTV[200000][2];
vector<int>ET[200000],MEMBER[25000];
queue<int>INPUT;
void GetInt(int &ans)
{
	assert(scanf("%d",&ans)==1);
	INPUT.push(ans);
}
int &GetInput(){static int ans;ans=INPUT.front();INPUT.pop();return ans;}
void BuildIDX(const int u,int &cnt,int *idx)
{
	INTV[u][0]=idx[u]=cnt++;
	for(const auto nxt:ET[u])BuildIDX(nxt,cnt,idx);
	INTV[u][1]=cnt-1;
}
void ReIndex()
{
	static int idx[200000];
	static int cnt;
	BuildIDX(0,cnt=0,idx);
	for(int i=0;i<R;i++)MEMBER[i].clear();
	for(int i=0;i<N;i++)ET[i].clear();
	MEMBER[REGION[idx[0]]=--GetInput()].push_back(idx[0]);
	for(int _i=1;_i<N;_i++)
	{
		const int i=idx[_i];
		ET[BOSS[i]=idx[--GetInput()]].push_back(i);
		MEMBER[REGION[i]=--GetInput()].push_back(i);
	}
	for(int i=0;i<R;i++)sort(MEMBER[i].begin(),MEMBER[i].end());
	BuildIDX(idx[0],cnt=0,idx);
	for(int i=0;i<N;i++)assert(idx[i]==i);
}
void BuildDown(const int r1,int *ans)
{
	static int change[200001];
	for(int i=0;i<=N;i++)change[i]=0;
	for(const auto &m:MEMBER[r1])change[INTV[m][0]]++,change[INTV[m][1]+1]--;//,printf("m=%d(%d,%d)\n",m,INTV[m][0],INTV[m][1]);
//	printf("change:");for(int i=0;i<=N;i++)printf(" %d",change[i]);puts("");
	for(int i=0;i<R;i++)ans[i]=0;
	for(int i=0,now=0;i<N;i++)ans[REGION[i]]+=(now+=change[i]);
}
void BuildUp(const int r2,int *ans)
{
	static int sum[200001];
	for(int i=1;i<=N;i++)sum[i]=(REGION[i-1]==r2?1:0);
	for(int i=1;i<=N;i++)sum[i]+=sum[i-1];
	for(int i=0;i<R;i++)ans[i]=0;
	for(int i=0;i<N;i++)ans[REGION[i]]+=(sum[INTV[i][1]+1]-sum[INTV[i][0]]);
}
int LRD[447][25000],LRU[447][25000],BSZ;
map<int,int>BIG;
int BinSearchUp(const vector<int>&s,const int value)
{
	int l=0,r=(int)s.size();
	while(l<r)
	{
		const int mid=(l+r)/2;
		if(s[mid]<value)l=mid+1;
		else r=mid;
	}
	return r;
}
int BinSearchDown(const vector<int>&s,const int value)
{
	int l=-1,r=(int)s.size()-1;
	while(l<r)
	{
		const int mid=(l+r+1)/2;
		if(s[mid]<=value)l=mid;
		else r=mid-1;
	}
	return r;
}
int Solve(const int r1,const int r2)
{
	const auto it1=BIG.find(r1),it2=BIG.find(r2);
	if(it1==BIG.end()&&it2==BIG.end())
	{
		int ans=0;
		vector<int>&mem2=MEMBER[r2];
		for(const auto m:MEMBER[r1])ans+=BinSearchDown(mem2,INTV[m][1])-BinSearchUp(mem2,INTV[m][0])+1;
//		puts("a");
		return ans;
	}
	else if(it1!=BIG.end())
	{
//		puts("b");
		return LRD[it1->second][r2];
	}
	else
	{
//		puts("c");
		assert(it2!=BIG.end());
		return LRU[it2->second][r1];
	}
}
int main()
{
//	freopen("D:\\Users\\Burney\\Downloads\\regions\\regions.018.in","r",stdin);
//	freopen("out.txt","w",stdout);
	assert(scanf("%d%d%d",&N,&R,&Q)==3);
	for(int i=0;i<R;i++)MEMBER[i].clear();
	for(int i=0;i<N;i++)ET[i].clear();
	assert(INPUT.empty());
	GetInt(REGION[0]),MEMBER[--REGION[0]].push_back(0);
	for(int i=1;i<N;i++)
	{
		GetInt(BOSS[i]),GetInt(REGION[i]);
		ET[--BOSS[i]].push_back(i),MEMBER[--REGION[i]].push_back(i);
	}
	ReIndex();
//	for(int i=0;i<N;i++)
//	{
//		printf("i=%d,region=%d,(%d,%d):",i,REGION[i],INTV[i][0],INTV[i][1]);
//		for(const auto nxt:ET[i])printf(" %d",nxt);puts("");
//	}
//	for(int i=0;i<R;i++)
//	{
//		printf("group %d:",i);for(const auto m:MEMBER[i])printf(" %d",m);puts("");
//	}
	do
	{
		multimap<int,int,greater<int> >sot;
		for(int i=0;i<R;i++)sot.insert(make_pair(MEMBER[i].size(),i));
		BSZ=(int)sqrt(N);
		assert(BSZ<=447);
		BIG.clear();
		auto it=sot.begin();
		for(int i=0,region;i<BSZ;i++)
		{
			BIG[region=(it++)->second]=i;
			BuildDown(region,LRD[i]),BuildUp(region,LRU[i]);
//			printf("region=%d\n",region);
//			printf("DOWN:");for(int j=0;j<R;j++)printf(" %d",LRD[i][j]);puts("");
//			printf("UP  :");for(int j=0;j<R;j++)printf(" %d",LRU[i][j]);puts("");
		}
	}while(0);
	while(Q--)
	{
		static int r1,r2;assert(scanf("%d%d",&r1,&r2)==2);
		printf("%d\n",Solve(--r1,--r2));
	}
	return 0;
}
