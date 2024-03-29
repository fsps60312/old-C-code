#include<cstdio>
#include<cassert>
using namespace std;
int N,K;
double P[20],S[2][20][20];
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		for(int i=0;i<N;i++)scanf("%lf",&P[i]);
		if(N<=K)
		{
			for(int i=0;i<N;i++)
			{
				if(i)putchar(' ');
				printf("%.10f",1.0);
			}
			puts("");
			continue;
		}
		for(int i=0;i<K;i++)for(int j=0;j<N;j++)S[0][i][j]=(j==i?1.0:0.0);
		int d=0;
		for(int tick=0;tick<=10;tick++,d^=1)
		{
			for(int i=0;i<K;i++)for(int j=0;j<N;j++)S[d^1][i][j]=0.0;
			for(int i=0;i<N;i++)
			{
				if(true)
				{
					double p=P[i];
					for(int k=0;k<K;k++)p*=1.0-S[d][k][i];
					S[d^1][0][i]+=p;
					for(int k=0;k<K-1;k++)for(int l=0;l<N;l++)if(l!=i)S[d^1][k+1][l]+=p*S[d][k][l];
				}
				for(int j=0;j<K;j++)
				{
					double p=P[i]*S[d][j][i];
					for(int k=0;k<K;k++)if(k!=j)p*=1.0-S[d][k][i];
					S[d^1][0][i]+=p; 
					for(int k=0;k<K;k++)for(int l=0;l<N;l++)if(l!=i)
					{
						if(k<j)S[d^1][k+1][l]+=p*S[d][k][l];
						if(k>j)S[d^1][k][l]+=p*S[d][k][l];
					}
				}
			}
		}
		for(int i=0;i<N;i++)
		{
			double ans=0.0;
			for(int j=0;j<K;j++)
			{
				double p=S[d][j][i];
				for(int k=0;k<K;k++)if(k!=j)p*=1.0-S[d][k][i];
				ans+=p;
			}
			if(i)putchar(' ');
			printf("%.10f",ans);
		}
		puts("");
	}
	return 0;
}
