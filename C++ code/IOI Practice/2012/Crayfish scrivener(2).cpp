#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
unsigned int Rand()
{
	static unsigned int seed=0x20160721;
	seed*=0x163636;
	return seed+=seed>>20;
}
struct Node
{
	char C;
	Node *CH[2];
	unsigned int SZ;
	Node(const char _C):C(_C),CH{NULL,NULL},SZ(1){}
};
Node *Copy(Node *o)
{
	Node *ans=new Node(o->C);
	for(int d=0;d<2;d++)ans->CH[d]=o->CH[d];
	ans->SZ=o->SZ;
	return ans;
}
unsigned int Sz(Node *o){return o?o->SZ:0;}
void Maintain(Node *o)
{
	o->SZ=Sz(o->CH[0])+1+Sz(o->CH[1]);
}
Node *Merge(Node *a,Node *b)
{
	if(!a||!b)return a?a:b;
	if(Rand()%(Sz(a)+Sz(b))<Sz(a))
	{
		Node *o=Copy(a);
		o->CH[1]=Merge(o->CH[1],b);
		Maintain(o);
		return o;
	}
	else
	{
		Node *o=Copy(b);
		o->CH[0]=Merge(a,o->CH[0]);
		Maintain(o);
		return o;
	}
}
char GetLetter(Node *o,const unsigned int i)
{
	assert(i<Sz(o));
	if(i==Sz(o->CH[0]))return o->C;
	if(i<Sz(o->CH[0]))return GetLetter(o->CH[0],i);
	else return GetLetter(o->CH[1],i-Sz(o->CH[0])-1);
}
int N;
vector<Node*>S;
void Init()
{
	S.clear(),S.push_back(NULL);
}
void TypeLetter(char L)
{
	Node *o=Merge(S.back(),new Node(L));
	S.push_back(o);
}
void UndoCommands(int U)
{
	Node *o=S[S.size()-1-U];
	S.push_back(o);
}
char GetLetter(int P)
{
	return GetLetter(S.back(),P);
}
