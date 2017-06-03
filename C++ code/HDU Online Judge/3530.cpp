#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
int N;
LL L,R,S[100000];
struct Deq
{
	int s[100000],l,r;
	void clear(){l=0,r=-1;}
	int front(){return s[l];}
	int back(){return s[r];}
	void pop_back(){r--;}
	void pop_front(){l++;}
	void push_back(const int &v){s[++r]=v;}
	bool empty(){return r<l;}
}MN,MX;
int main()
{
	while(scanf("%d%lld%lld",&N,&L,&R)==3)
	{
		for(int i=0;i<N;i++)scanf("%lld",&S[i]);
		MN.clear(),MX.clear();
		int ans=0;
		for(int i=0,l=0;i<N;i++)
		{
			while(!MN.empty()&&S[MN.back()]>=S[i])MN.pop_back();
			while(!MX.empty()&&S[MX.back()]<=S[i])MX.pop_back();
			MN.push_back(i),MX.push_back(i);
			while(S[MX.front()]-S[MN.front()]>R)
			{
//				assert(l<=i);
				if(S[MX.front()]==l)MX.pop_front();
				if(S[MN.front()]==l)MN.pop_front();
				l++;
			}
			if(S[MX.front()]-S[MN.front()]>=L&&i-l+1>ans)ans=i-l+1;
		}
		printf("%d\n",ans);
	}
	return 0;
}