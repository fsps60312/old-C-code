#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL INF=1LL<<62;
void getmin(LL &a,const LL b){if(b<a)a=b;}
int N;
LL A,B,S[1000001],LSUM[1000002],RSUM[1000002];
vector<LL>P;
void BuildP()
{
	bool *isp=new bool[70001];
	for(int i=2;i<=70000;i++)isp[i]=true;
	for(int i=2;i<=70000;i++)if(isp[i])
	{
		P.push_back(i);
		for(int j=2;i*j<=70000;j++)isp[i*j]=false;
	}
//	for(int i=0;i<100;i++)printf("%lld\n",P[i]);
}
LL Solve(const LL g,const int lb,const int rb)
{
	if(g==1LL)return INF;
	LSUM[lb-1]=0;
	for(int i=lb;i<=rb;i++)LSUM[i]=LSUM[i-1]+(S[i]%g==0?0:B);
	for(int i=lb-1;i<=rb;i++)LSUM[i]+=A*(rb-i);
	RSUM[rb+1]=0;
	for(int i=rb;i>=lb;i--)RSUM[i]=RSUM[i+1]+(S[i]%g==0?0:B);
	for(int i=rb+1;i>=lb;i--)RSUM[i]+=A*(i-lb);
//	for(int i=lb;i+1<=rb;i++)for(int j=i+1;j<=rb;j++)assert(LSUM[i]+RSUM[j]>=A*(rb-lb+1));
	int l=lb;
	for(;l<=rb&&(S[l]%g==0||(S[l]+1)%g==0||(S[l]-1)%g==0);l++);
	if(l==rb+1)
	{
		LL ans=INF;
		for(int i=lb,j=lb-1;i<=rb+1;i++)
		{
			assert(j<i&&LSUM[j]+RSUM[i]-A*(rb-lb+1)>=0LL);
			getmin(ans,LSUM[j]+RSUM[i]-A*(rb-lb+1));
			if(LSUM[i-1]<LSUM[j])j=i-1;
		}
		return ans;
	}
	else
	{
		int r=rb;
		for(;S[r]%g==0||(S[r]+1)%g==0||(S[r]-1)%g==0;r--);
		LL ans=INF,ans1=INF,ans2=INF;
		for(int i=lb;i<l;i++)getmin(ans1,LSUM[i]);
		for(int i=rb+1;i>r;i--)getmin(ans2,RSUM[i]);
		if(ans1!=INF&&ans2!=INF)getmin(ans,ans1+ans2-A*(rb-lb+1));
		ans1=ans2=INF;
		for(int i=lb-1;i<l;i++)getmin(ans1,LSUM[i]);
		for(int i=rb;i>r;i--)getmin(ans2,RSUM[i]);
		if(ans1!=INF&&ans2!=INF)getmin(ans,ans1+ans2-A*(rb-lb+1));
		return ans;
	}
}
void GetF(LL n,vector<LL>&f)
{
	f.clear();
	for(int i=0;P[i]*P[i]<=n;i++)if(n%P[i]==0)
	{
		while(n%P[i]==0)n/=P[i];
		f.push_back(P[i]);
	}
	if(n>1)f.push_back(n);
}
int main()
{
//	freopen("in.txt","r",stdin);
	BuildP();
	while(scanf("%d%lld%lld",&N,&A,&B)==3)
	{
		for(int i=1;i<=N;i++)scanf("%lld",&S[i]);
		LL ans=INF;
		vector<LL>f;
		GetF(S[1],f);
		for(const LL i:f)getmin(ans,Solve(i,1,N));
		GetF(S[N],f);
		for(const LL i:f)getmin(ans,Solve(i,1,N));
		S[1]++;
		GetF(S[1],f);
		for(const LL i:f)getmin(ans,Solve(i,2,N)+B);
		S[1]-=2;
		GetF(S[1],f);
		for(const LL i:f)getmin(ans,Solve(i,2,N)+B);
		S[1]++;
		S[N]++;
		GetF(S[N],f);
		for(const LL i:f)getmin(ans,Solve(i,1,N-1)+B);
		S[N]-=2;
		GetF(S[N],f);
		for(const LL i:f)getmin(ans,Solve(i,1,N-1)+B);
		S[N]++;
		printf("%lld\n",ans);
	}
}
