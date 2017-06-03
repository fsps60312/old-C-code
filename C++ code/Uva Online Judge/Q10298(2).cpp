#include<cstdio>
#define termin(x,...) {while(1)printf(x,##__VA_ARGS__);}
char LINE[1000001];
int N,SA[1000001],HT[1000001],RANK[1000001],TMPS[2][1000001];
void show(char *msg,int *bse,int n){printf("%s:",msg);for(int i=0;i<n;i++)printf(" %d",bse[i]);puts("");}
void buildSA()
{
	int *c=RANK,*x=TMPS[0],*y=TMPS[1];
	int kind=256;
	for(int i=0;i<kind;i++)c[i]=0;
	for(int i=0;i<N;i++)c[x[i]=LINE[i]]++;
	for(int i=1;i<kind;i++)c[i]+=c[i-1];
	for(int i=N-1;i>=0;i--)SA[--c[x[i]]]=i;//SA[x]=y -> rank x is loc y
	for(int dis=1;dis<N;dis<<=1)
	{
		int p=0;
		for(int i=N-dis;i<N;i++)y[p++]=i;
		for(int i=0;i<N;i++)if(SA[i]>=dis)y[p++]=SA[i]-dis;
		for(int i=0;i<kind;i++)c[i]=0;
		for(int i=0;i<N;i++)c[x[i]]++;
		for(int i=1;i<kind;i++)c[i]+=c[i-1];
		for(int i=N-1;i>=0;i--)SA[--c[x[y[i]]]]=y[i];
		p=0;
		y[SA[0]]=p++;
		for(int i=1;i<N;i++)
		{
			if(x[SA[i]]!=x[SA[i-1]])y[SA[i]]=p++;
			else if(SA[i]+dis>=N&&SA[i-1]+dis>=N)y[SA[i]]=p-1;
			else if(SA[i]+dis>=N||SA[i-1]+dis>=N)y[SA[i]]=p++;
			else y[SA[i]]=x[SA[i]+dis]==x[SA[i-1]+dis]?p-1:p++; 
		}
		kind=p;
		if(kind>=N)break;
		int *tmp=x;x=y,y=tmp;
	}
}
void buildHT()
{
	for(int i=0;i<N;i++)RANK[SA[i]]=i;
	int ans=0;
	for(int loc=0,i;loc<N;loc++)
	{
		if(ans)ans--;
		i=RANK[loc];
		if(!i){HT[loc]=0;continue;}
		while(LINE[SA[i]+ans]==LINE[SA[i-1]+ans])ans++;
		HT[loc]=ans;
	}
}
int solve()
{
	int *cnt=TMPS[0];
	for(int i=0;i<N;i++)cnt[i]=0;
	for(int i=0;i<N;i++)cnt[HT[i]]++;
	for(int i=N-1;i>=1;i--)cnt[i-1]+=cnt[i];
	for(int i=1;i<N;i++)
	{
		if(N%i)continue;
		if(cnt[i]>=N/i-1)return N/i;
	}
	return 1;
}
int main()
{
	while(scanf("%s",LINE)==1)
	{
		N=-1;while(LINE[++N])if(LINE[N]>=256||LINE[N]<0)termin("not in range\n");
		if(N==1&&LINE[0]=='.')break;
		buildSA();
		buildHT();
//		show("HT",HT,N);
		printf("%d\n",solve());
	}
	return 0;
}