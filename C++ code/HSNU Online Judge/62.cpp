#include<cstdio>
#include<cassert>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int &b){if(b<a)a=b;}
int N,K,DP[1000][1000][26];//min simplicity: change k, last is c
char S[1001];
int main()
{
	scanf("%d%d%s",&N,&K,S);
	for(int i=0;i<N;i++)assert('A'<=S[i]&&S[i]<='Z');
	for(int i=0;i<N;i++)for(int j=0;j<=K;j++)for(int c=0;c<26;c++)DP[i][j][c]=INF;
	for(int c=0;c<26;c++)
	{
		if('A'+c==S[0])DP[0][0][c]=1;
		else DP[0][1][c]=1;
	}
	for(int i=0;i+1<N;i++)
	{
		for(int j=0;j<=K;j++)
		{
			for(int c=0;c<26;c++)
			{
				int &dp=DP[i][j][c];
				if(dp==INF)continue;
				getmin(DP[i+1][j][S[i+1]-'A'],dp+1);//no change
				int k=j;
				if('A'+c!=S[i+1])k++;
				getmin(DP[i+1][k][c],dp);
			}
		}
	}
	int ans=INF;
	for(int i=0;i<=K;i++)for(int c=0;c<26;c++)getmin(ans,DP[N-1][i][c]);
	printf("%d\n",ans);
	return 0;
}
