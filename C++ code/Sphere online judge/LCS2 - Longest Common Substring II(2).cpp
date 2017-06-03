#include<cstdio>
#include<cassert>
#include<string>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
struct Node
{
	Node *green,*edge[26];
	const int max_len;
	int dp;
	Node(const int _max_len):green(NULL),max_len(_max_len),dp(-1){for(int i=0;i<26;i++)edge[i]=NULL;}
};
struct SuffixAutomaton
{
	Node *root,*last;
	void Initialize(){root=last=new Node(0);}
	void Extend(const int c)
	{
		Node *cur=last;last=new Node(last->max_len+1);
		for(;cur&&cur->edge[c]==NULL;cur=cur->green)cur->edge[c]=last;
		if(!cur)last->green=root;
		else
		{
			Node *pgreen=cur->edge[c];
			if(pgreen->max_len==cur->max_len+1)last->green=pgreen;
			else
			{
				Node *wish=new Node(cur->max_len+1);
				for(;cur&&cur->edge[c]==pgreen;cur=cur->green)cur->edge[c]=wish;
				for(int i=0;i<26;i++)wish->edge[i]=pgreen->edge[i];
				wish->green=pgreen->green;
				pgreen->green=wish;
				last->green=wish;
			}
		}
	}
}SAM[10];
void Print(Node *o,string now)
{
	if(!o)return;
	puts(now.c_str());
	for(int i=0;i<26;i++)Print(o->edge[i],now+(char)('a'+i));
}
int N;
int Dfs(Node **cur)
{
	for(int i=0;i<N;i++)if(cur[i]==NULL)return 0;
	int &ans=cur[0]->dp; 
	if(ans!=-1)return ans;
	Node **nxt=new Node*[N];
	for(int c=0;c<26;c++)
	{
		for(int i=0;i<N;i++)nxt[i]=cur[i]->edge[c];
		getmax(ans,Dfs(nxt)+1);
	}
	delete[]nxt;
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	static char str[100001];
	for(N=0;fgets(str,2147483647,stdin);N++)
	{
		SAM[N].Initialize();
		int i;
		for(i=0;str[i]&&str[i]!='\n';i++)SAM[N].Extend(str[i]-'a');
		assert(0<i&&i<=100000);
	}
	assert(0<N&&N<=10);
	Node **cur=new Node*[N];
	for(int i=0;i<N;i++)cur[i]=SAM[i].root;
	for(int i=0;i<N;i++)
	{
		printf("i=%d\n",i);
		Print(cur[i],"");
	}
	printf("%d\n",Dfs(cur)-1);
	delete[]cur;
	return 0;
}
