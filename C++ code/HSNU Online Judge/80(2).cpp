#include<cstdio>
#include<algorithm>
#include<cassert>
using namespace std;
char S[20000002];
int DP[20000001],N;
int main()
{
//	freopen("in.txt","r",stdin);
	static char c;
	S[0]='A';
	N=1;
	while((c=getchar())!=-1)
	{
		if(c=='\n')break;
		assert(c>='a'&&c<='z');
		S[N++]=c;
		S[N++]='A';
	}
	S[N]='\0';
//	puts(S);
	int ans=0;
	DP[0]=1;
	for(int i=1,idx=0;i<N;i++)
	{
		int &len=DP[i];
		if(idx+DP[idx]-1>i)
		{
			len=min(DP[idx-(i-idx)],idx+DP[idx]-1-i);
		}
		else
		{
			len=1;
		}
		while(i-len>=0&&S[i-len]==S[i+len])len++;
		if(S[i]=='A')ans=max(ans,len-1);
		else ans=max(ans,len-1);
//		printf("len=%d\n",len);
		if(i+len-1>idx+DP[idx]-1)idx=i;
	}
	printf("%d\n",ans);
	return 0;
}
