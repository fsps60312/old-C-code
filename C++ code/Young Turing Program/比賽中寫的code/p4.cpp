//{{{
#include <bits/stdc++.h>
using namespace std;
//types
typedef long long ll;
typedef pair<int,int> pii;
//input
bool SR(int &_x){return scanf("%d",&_x)==1;}bool SR(ll &_x){return scanf("%lld",&_x)==1;}
bool SR(double &_x){return scanf("%lf",&_x)==1;}bool SR(char *_s){return scanf("%s",_s)==1;}
bool RI(){return true;}
template<typename I,typename... T>bool RI(I &_x,T&... _tail){return SR(_x) && RI(_tail...);}
//output
void SP(const int _x){printf("%d",_x);}void SP(const ll _x){printf("%lld",_x);}
void SP(const double _x){printf("%.16lf",_x);}void SP(const char *s){printf("%s",s);}
void PL(){puts("");}
template<typename I,typename... T>void PL(const I _x,const T... _tail)
{SP(_x);if(sizeof...(_tail)) putchar(' ');PL(_tail...);}
//macro
#define SZ(x) ((int)(x).size())
#define ALL(x) (x).begin(),(x).end()
#define REP(i,n) for(int i=0;i<int(n);i++)
#define REP1(i,a,b) for(int i=(a);i<=int(b);i++)
#define pb push_back
#define mkp make_pair
#define F first
#define S second
//debug
#ifdef darry140
template<typename I>
void _DOING(const char *_s,I&& _x){cerr<<_s<<"="<<_x<<endl;}//without ','
template<typename I,typename... T>
void _DOING(const char *_s,I&& _x,T&&... _tail)//with ','
{
    int _c=0;
    static const char _bra[]="({[";
    static const char _ket[]=")}]";
    while(*_s!=',' || _c!=0)//eg. mkp(a,b)
    {
        if(strchr(_bra,*_s)) _c++;
        if(strchr(_ket,*_s)) _c--;
        cerr<<*_s++;
    }
    cerr<<"="<<_x<<", ";
    _DOING(_s+1,_tail...);
}
#define debug(...) do{\
    fprintf(stderr,"%s:%d - ",__PRETTY_FUNCTION__,__LINE__);\
    _DOING(#__VA_ARGS__,__VA_ARGS__);\
}while(0)
template<typename It>
ostream& _OUTC(ostream &_s,It _b,It _e)//container
{
    _s<<"{";
    for(auto _it=_b;_it!=_e;_it++) _s<<(_it==_b?"":" ")<<*_it;
    _s<<"}";
    return _s;
}
template<typename A,typename B>
ostream& operator <<(ostream&_s, const pair<A,B> &_p){return _s<<"("<<_p.F<<","<<_p.S<<")";}
template<typename A,typename B>
ostream& operator <<(ostream&_s, const map<A,B> &_c){return _OUTC(_s,ALL(_c));}
template<typename T>
ostream& operator <<(ostream&_s, const set<T> &_c){return _OUTC(_s,ALL(_c));}
template<typename T>
ostream& operator <<(ostream&_s, const vector<T> &_c){return _OUTC(_s,ALL(_c));}
#else
#define debug(...)
#endif
//}}}

int main()
{
	ll n;RI(n);
	priority_queue<ll,vector<ll>,greater<ll> > pq;
	assert(n>1);
	while(n--)
	{
		ll x;RI(x);pq.push(x);
	}
	
	ll ans=0;
	while(SZ(pq)>1)
	{
		ll a=pq.top();pq.pop();
		ll b=pq.top();pq.pop();
		ans+=a+b;
		pq.push(a+b);
	}
	PL(ans);
    return 0;
}




































/*End Of File*/


