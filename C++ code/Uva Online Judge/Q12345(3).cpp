#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<cmath>
#include<set>
using namespace std;
struct Query
{
	char type;
	int x,y;
};
vector<Query>QUERY;
int N,M,A[50000];
void ReadInput()
{
	int querycount;
	scanf("%d%d",&N,&querycount);
	for(int i=0;i<N;i++)scanf("%d",&A[i]);
	QUERY.clear();
	while(querycount--)
	{
		static char type[2];
		static Query q;
		scanf("%s%d%d",type,&q.x,&q.y);
		q.type=type[0];
		QUERY.push_back(q);
	}
}
void Discretize()
{
	vector<int>v;
	for(int i=0;i<N;i++)v.push_back(A[i]);
	for(const Query &q:QUERY)if(q.type=='M')v.push_back(q.y);
	sort(v.begin(),v.end()),v.resize(unique(v.begin(),v.end())-v.begin());
	M=v.size();
	for(int i=0;i<N;i++)A[i]=lower_bound(v.begin(),v.end(),A[i])-v.begin();
	for(Query &q:QUERY)
	{
		if(q.type=='M')q.y=lower_bound(v.begin(),v.end(),q.y)-v.begin();
		else q.y--;
	}
	v.clear(),vector<int>().swap(v);
}
struct Node
{
	Node *l,*r;
	const int loc;
	Node(const int _loc):l(NULL),r(NULL),loc(_loc){}
};
void Insert(vector<int>&s,const int v)
{
	const int sz=s.size();
	auto it=lower_bound(s.begin(),s.end(),v);
	assert(it==s.end()||v<=(*it));
	if(it!=s.begin())assert((*--it)<v),it++;
	s.insert(it,v);
	assert((int)s.size()==sz+1);
}
void Erase(vector<int>&s,const int v)
{
	const int sz=s.size();
	auto it=lower_bound(s.begin(),s.end(),v);
	assert(it!=s.end()&&(*it)==v),s.erase(it);
	assert((int)s.size()==sz-1);
}
Node *S[50000],*BEGIN[100000],*END[100000];
set<int>LOCS[100000];
vector<int>LEFT[224];
int GAP;
void Insert(Node* &l,Node* &o,Node* &r)
{
	assert(l->r==r&&r->l==l);
	if((r->loc)<N)Erase(LEFT[(r->loc)/GAP],l->loc),Insert(LEFT[(r->loc)/GAP],o->loc);
	Insert(LEFT[(o->loc)/GAP],l->loc);
	l->r=o,o->r=r;
	r->l=o,o->l=l;
}
void Extract(Node* &o)
{
	Node *l=o->l,*r=o->r;
	if((r->loc<N))Erase(LEFT[(r->loc)/GAP],o->loc),Insert(LEFT[(r->loc)/GAP],l->loc);
	Erase(LEFT[(o->loc)/GAP],l->loc);
	l->r=r,r->l=l;
	o->l=o->r=NULL;
}
void PreProcess()
{
	assert(M<=100000);
	Node **pre=new Node*[M];
	for(int i=0;i<M;i++)
	{
		pre[i]=BEGIN[i]=new Node(-1),END[i]=new Node(N);
		BEGIN[i]->r=END[i],END[i]->l=BEGIN[i];
		LOCS[i].clear();
	}
	GAP=min(N,(int)sqrt(N)+1);
	for(int i=0;i<=(N-1)/GAP;i++)LEFT[i].clear();
	for(int i=0;i<N;i++)
	{
		const int v=A[i];
		LOCS[v].insert(i);
		Insert(pre[v],S[i]=new Node(i),END[v]),pre[v]=S[i];
	}
	delete[]pre;
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	ReadInput();
	Discretize();
	PreProcess();
	for(const Query &q:QUERY)
	{
		if(q.type=='M')
		{
			Node* &o=S[q.x];
			Extract(o);
			LOCS[A[q.x]].erase(q.x);
			auto itr=LOCS[q.y].upper_bound(q.x),itl=itr;
			Insert(itl==LOCS[q.y].begin()?BEGIN[q.y]:S[*--itl],o,itr==LOCS[q.y].end()?END[q.y]:S[*itr]);
//			printf("%d-(%d,%d)-%d\n",o->l->loc,o->loc,q.y,o->r->loc);
			LOCS[q.y].insert(q.x);
			A[q.x]=q.y;
		}
		else if(q.type=='Q')
		{
			const int l=(q.x+GAP-1)/GAP,r=(q.y+1)/GAP-1;
			assert((l-1)*GAP<q.x&&q.x<=l*GAP);
			assert((r+1)*GAP-1<=q.y&&q.y<(r+2)*GAP-1);
			int ans=0;
			for(int i=l;i<=r;i++)
			{
				const vector<int>&s=LEFT[i];
				ans+=lower_bound(s.begin(),s.end(),q.x)-s.begin();
			}
			if(q.x/GAP==q.y/GAP)
			{
				for(int i=q.x;i<=q.y;i++)if((S[i]->l->loc)<q.x)ans++;
			}
			else
			{
				for(int i=q.x;i<l*GAP;i++)if((S[i]->l->loc)<q.x)ans++;
				for(int i=q.y;i>=(r+1)*GAP;i--)if((S[i]->l->loc)<q.x)ans++;
			}
			printf("%d\n",ans);
//			assert(ans==q.y-q.x+1);
		}
		else assert(0);
//		for(int i=0;i<=(N-1)/GAP;i++)
//		{
//			printf("[%d]:",i);
//			for(const int v:LEFT[i])printf(" %d",v);puts("");
//		}
	}
	return 0;
}
