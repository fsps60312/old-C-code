#include<cstdio>
#include<algorithm>
using namespace std;
int T,N,M,DJ[5000];
int FindDJ(int a){return DJ[a]==a?a:(DJ[a]=FindDJ(DJ[a]));}
struct Edge
{
	int a,b,se;
	Edge(){}
	Edge(int a,int b,int se):a(a),b(b),se(se){}
	bool operator<(const Edge &e)const{return se>e.se;}
}EDGE[5000*(5000-1)/2];
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			scanf("%d%d",&N,&M);
			for(int i=0;i<N;i++)
			{
				DJ[i]=i;
			}
			for(int i=0;i<M;i++)
			{
				static int a,b,se;
				scanf("%d%d%d",&a,&b,&se);
				EDGE[i]=Edge(a,b,se);
			}
			sort(EDGE,EDGE+M);
			int ans=0,cnt=N;
			for(int u=0;u<M;u++)
			{
				int &se=EDGE[u].se;
				int i;
				for(i=u;i<M&&EDGE[i].se==se;i++)
				{
					int &a=EDGE[i].a,&b=EDGE[i].b;
					a=FindDJ(a),b=FindDJ(b);
					if(a==b)continue;
					cnt--;
					DJ[a]=b;
				}
				u=i;
				ans+=
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}
