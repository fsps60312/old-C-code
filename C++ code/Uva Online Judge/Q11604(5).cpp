#include<cstdio>
//#include<cassert>
#include<string>
#include<vector>
#include<map>
#include<stack>
using namespace std;
int N,L,SZ;
char LINE1[22],LINE2[22];
string V[100];
vector<vector<int> >TO;
vector<string>RI;
map<string,int>IDX;
vector<bool>VIS,NEW;
int GetIdx(string s)
{
	if(IDX.find(s)==IDX.end())
	{
		RI.push_back(s);
		TO.push_back(vector<int>());
		NEW.push_back(true);
		VIS.push_back(false);
		return IDX[s]=SZ++;
	}
	else return IDX[s];
}
void BuildTO(int u)
{
	string &v=RI[u];
	NEW[u]=false;
	for(int i=0;i<N;i++)
	{
		string &s=V[i];
		for(int j=0;;j++)
		{
			if(j==s.size())
			{
				TO[u].push_back(GetIdx(v.substr(j)));
				break;
			}
			if(j==v.size())
			{
				TO[u].push_back(GetIdx(s.substr(j)));
				break;
			}
			if(s[j]!=v[j])break;
		}
	}
}
struct Stk
{
	int u,i;
	Stk(){}
	Stk(int u,int i):u(u),i(i){}
};
stack<Stk>STK;
bool Dfs(int _u)
{
	STK=stack<Stk>();
	STK.push(Stk(_u,-1));
	while(!STK.empty())
	{
		int u=STK.top().u,i=STK.top().i;STK.pop();
		if(i==-1)
		{
			if(VIS[u])continue;
			if(!u)return true;
			VIS[u]=true;
			if(NEW[u])BuildTO(u);
		}
		i++;
		if(i==TO[u].size())
		{
			VIS[u]=false;
			continue;
		}
		STK.push(Stk(u,i));
		int &j=TO[u][i];
		STK.push(Stk(j,-1));
	}
	return false;
}
bool solve()
{
	for(int i=0;i<N;i++)
	{
		for(int j=i+1;j<N;j++)
		{
			for(int k=0;;k++)
			{
				if(k==V[i].size())
				{
					if(Dfs(GetIdx(V[j].substr(k))))return true;
					break;
				}
				if(k==V[j].size())
				{
					if(Dfs(GetIdx(V[i].substr(k))))return true;
					break;
				}
				if(V[i][k]!=V[j][k])break;
			}
		}
	}
	return false;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N)
	{
		TO.clear();
		RI.clear();
		IDX.clear();
		NEW.clear(),VIS.clear();
		SZ=0;
		GetIdx("");
		for(int i=0;i<N;i++)
		{
			scanf("%s%s",LINE1,LINE2);
			V[i]=LINE2;
		}
		static int kase=1;
		printf("Case #%d: %smbiguous.\n",kase++,solve()?"A":"Not a");
	}
	return 0;
}