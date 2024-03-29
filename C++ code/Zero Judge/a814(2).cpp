#include<cstdio>
#include<cassert>
using namespace std;
int T,N,M,S[1000000],CNT[1000001];
struct Treap
{
	Treap *ch[2];
	int sz,v;
	Treap(const int &_v):v(_v),sz(1),ch{NULL,NULL}{}
}*L=NULL,*R=NULL;
int Sz(Treap* &o){return o?o->sz:0;}
void Maintain(Treap* &o){o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);}
void Rotate(Treap* &o,const int &cu)
{
	Treap *u=o;
	o=o->ch[cu];
	u->ch[cu]=o->ch[cu^1];
	o->ch[cu^1]=u;
	Maintain(u),Maintain(o); 
}
void Rotate(Treap* &o)
{
	if(Sz(o->ch[0])>Sz(o->ch[1]))Rotate(o,0);
	else if(Sz(o->ch[1])>Sz(o->ch[0]))Rotate(o,1);
}
void Insert(Treap* &o,const int &v,const int &d)
{
	if(!o){o=new Treap(v);return;}
	Insert(o->ch[v<o->v?d:d^1],v,d);
	Maintain(o);
	Rotate(o);
}
int Top(Treap* &o)
{
	if(!o->ch[0])return o->v;
	return Top(o->ch[0]);
}
void Pop(Treap* &o)
{
	if(!o->ch[0]){Treap *u=o;o=o->ch[1];delete u;return;}
	Pop(o->ch[0]);
	Maintain(o);
	Rotate(o);
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		for(int i=1;i<=M;i++)CNT[i]=0;
		int sum=0;
		for(int i=0;i<N;i++)if(CNT[S[i]]++==1)sum++;
		for(int i=1;i<=M;i++)if(!CNT[i])Insert(L,i,0),Insert(R,i,1);
		bool found=false;
		for(int i=N-1;i>=0;i--)
		{
			CNT[S[i]]--;
			if(CNT[S[i]]==0)Insert(L,S[i],0),Insert(R,S[i],1);
			else if(CNT[S[i]]==1)sum--;
			if(sum==0&&Top(R)>S[i])
			{
				found=true;
				bool changed=false;
				for(int j=i+1;j<N||!changed;)
				{
					if(!changed&&Top(L)>S[i])
					{
						changed=true;
						S[i]=Top(L);
					}
					else if(j<N)S[j++]=Top(L);
					Pop(L);
				}
				while(Sz(L))Pop(L);
				while(Sz(R))Pop(R);
				break;
			}
		}
		assert(found);
		printf("%d",S[0]);
		for(int i=1;i<N;i++)printf(" %d",S[i]);
		puts("");
	}
	return 0;
}
