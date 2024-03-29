#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
int Sks(const int n)
{
	int ans=0;
	int d=0;
	while((1<<(d+1))<=n)d++;
	if(d==0)return 1;
	ans+=(1<<d)-(d-1);
	if(n&(1<<(d-1)))ans+=(1<<(d-1))-1;
	else ans+=n&((1<<(d-1))-1);
//	printf("ans=%d\n",ans);
	for(int i=d-2,v=0;i>=0;i--)
	{
		if((n&((1<<(i+2))-1))>=(1<<i))ans+=v+1;
		else ans+=v;
		v=(v<<1)+((n>>(i+1))&1);
	}
	return ans;
}
int N,S[1000000],LOC[1000000];
int main()
{
	freopen("in.txt","r",stdin);
	for(;scanf("%d",&N)==1;)
	{
		int sum=0;
		for(int i=0;i<N;i++)scanf("%d",&S[i]),sum+=S[i];
		if(sum==1){printf("1\n1\n");continue;}
		assert(sum>=2);
		vector<vector<int> >anses;
		int adjust=0;
		if(true)
		{
			vector<int>s;
			s.push_back(1);
			s.push_back(sum-1);
			anses.push_back(s);
			adjust-=(sum-2);
		}
		if(S[0]>=2)
		{
			if(sum>2)
			{
				vector<int>s;
				s.push_back(sum-2);
				anses.push_back(s);
			}
		}
		else
		{
			assert(S[0]==1);
			if(N>=3)
			{
				vector<int>s;
				for(int i=2;i<N;i++)s.push_back(S[i]);
				anses.push_back(s);
			}
		}
		puts("a");
		for(int i=0;i<N;i+=2)
		{
			vector<int>s;
			s.push_back(S[i]);
			s.push_back(LOC[i]-S[i]+1);
			--adjust;
			adjust-=(S[i]-1);
		}
		puts("b");
		map<int,int>mans;
		for(int i=0;i<(int)anses.size();i++)
		{
			const vector<int>&s=anses[i];
			vector<int>loc;loc.resize(s.size());
			for(int cur=0,j=(int)s.size()-1;j>=0;j--)loc[j]=(cur+=s[j]);
			for(int j=0;j<(int)s.size();j+=2)
			{
				++mans[loc[j]];
				--mans[loc[j]-s[j]];
			}
		}
		puts("c");
		if(adjust>0)
		{
			for(int i=0;(1<<i)<=adjust;i++)if(adjust&(1<<i))++mans[i];
		}
		else
		{
			adjust*=-1;
			for(int i=0;(1<<i)<=adjust;i++)if(adjust&(1<<i))--mans[i];
		}
		for(map<int,int>::iterator it=mans.begin();it!=mans.end();)
		{
			if(abs(it->second)>=2)
			{
				mans[it->first+1]+=it->second/2;
				it->second%=2;
			}
			if(!it->second)mans.erase(it++);
			else ++it;
		}
		puts("d");
		vector<pair<int,int> >pans;
		int loc=0;
		for(map<int,int>::iterator it=mans.begin();it!=mans.end();++it)
		{
			printf("(%d,%d)\n",it->first,it->second);
			int val=1;
			if(it==mans.begin())val=0;
			else
			{
				--it;
				if(it->second==1)val=0;
				else assert(it->second==-1);
				++it;
			}
			pans.push_back(make_pair(val,(it->first-1)-loc+1));
			pans.push_back(make_pair(val^1,1));
			loc=it->first+1;
		}
		puts("e");
		while(!pans.empty()&&pans.back().first==0)pans.pop_back();
		assert(!pans.empty());
		vector<int>ans;
		for(int i=(int)pans.size()-1,d=1;;d^=1)
		{
			ans.push_back(0);
			for(;i>=0&&(pans[i].first==d||pans[i].second==0);i--)ans.back()+=pans[i].second;
			if(i==-1)break;
		}
		printf("%d\n",(int)ans.size());
		for(int i=0;i<(int)ans.size();i++)
		{
			if(i)putchar(' ');
			printf("%d",ans[i]);
		}
		puts("");
	}
	return 0;
}
