#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
const int INF=2147483647;
struct Fraction
{
	int up,down;
	Fraction(){}
	Fraction(const int _up,const int _down):up(_up),down(_down){}
	void operator*=(const int a)
	{
		if(down%a==0)down/=a;
		else assert(up<=INF/a),up*=a;
	}
	void operator/=(const int a)
	{
		if(up%a==0)up/=a;
		else assert(down<=INF/a),down*=a;
	}
};
bool operator<(const Fraction &f1,const Fraction &f2){return (LL)f1.up*f2.down<(LL)f2.up*f1.down;}
bool operator<=(const Fraction &f1,const Fraction &f2){return (LL)f1.up*f2.down<=(LL)f2.up*f1.down;}
struct Rect
{
	int id;
	Fraction x1,x2,y1,y2;
	Rect(){}
	Rect(const int _id,const int _x1,const int _x2,const int _y1,const int _y2):id(_id),x1(Fraction(_x1,1)),x2(Fraction(_x2,1)),y1(Fraction(_y1,1)),y2(Fraction(_y2,1)){}
	Rect(const int _id,const Fraction _x1,const Fraction _x2,const Fraction _y1,const Fraction _y2):id(_id),x1(_x1),x2(_x2),y1(_y1),y2(_y2){}
};
void Multiply(vector<Rect>&s,const int down,const int up)
{
	for(int i=0;i<(int)s.size();i++)
	{
		Rect &r=s[i];
		r.x1/=down,r.x2/=down,r.y1/=down,r.y2/=down;
		r.x1*=up,r.x2*=up,r.y1*=up,r.y2*=up;
	}
}
#include<map>
#include<queue>
struct Pq
{
	Fraction y2,x1;
	Pq(){}
	Pq(const Fraction _y2,const Fraction _x1):y2(_y2),x1(_x1){}
};
bool operator<(const Pq &p1,const Pq &p2){return p2.y2<p1.y2;}
const int UNUSED=1200;
struct CmpY2{bool operator()(const Rect &r1,const Rect &r2){return r1.y2<r2.y2;}};
Rect Merge(const Rect &r1,const Rect &r2,bool *illuminated)
{
	illuminated[r1.id]=illuminated[r2.id]=true;
	Rect ans;
	ans.x1=max(r1.x1,r2.x1);
	ans.y1=max(r1.y1,r2.y1);
	ans.x2=min(r1.x2,r2.x2);
	ans.y2=min(r1.y2,r2.y2);
	ans.id=UNUSED;
	assert(ans.x1<ans.x2&&ans.y1<ans.y2);
	return ans;
}
void Filter(vector<Rect>&s,const vector<Rect>&windows,bool *illuminated)
{
	for(int i=1;i<(int)s.size();i++)assert(s[i-1].y2<=s[i].y2);
	for(int i=1;i<(int)windows.size();i++)assert(windows[i-1].y2<=windows[i].y2);
	vector<Rect>ans;
	priority_queue<Rect,vector<Rect>,CmpY2>plight,pwindow;
	map<Fraction,Rect>mlight,mwindow;
	for(int i=0,j=0;;)
	{
		const bool is_light=(i<(int)s.size()&&(j==(int)windows.size()||s[i].y1<=windows[j].y1));
		if(!is_light&&j==(int)windows.size())break;
		const Rect &one=(is_light?s[i]:windows[j]);
		priority_queue<Rect,vector<Rect>,CmpY2>&pnew=(is_light?plight:pwindow),&pold=(is_light?pwindow:plight);
		map<Fraction,Rect>&mnew=(is_light?mlight:mwindow),&mold=(is_light?mwindow:mlight);
		if(true)
		{
			while(!pnew.empty()&&pnew.top().y2<=one.y1)mnew.erase(pnew.top().x1),pnew.pop();
			while(!pold.empty()&&pold.top().y2<=one.y1)mold.erase(pold.top().x1),pold.pop();
		}
		map<Fraction,Rect>::iterator it=mold.lower_bound(one.x1);
		if(it!=mold.begin())
		{
			--it;
			if(one.x1<it->second.x2)ans.push_back(Merge(one,it->second,illuminated));
			++it;
		}
		for(;it!=mold.end()&&it->first<one.x2;++it)
		{
			ans.push_back(Merge(one,it->second,illuminated));
		}
		pnew.push(one);
		mnew[one.x1]=one;
		++(is_light?i:j);
	}
	s.clear();
	for(int i=0;i<(int)ans.size();i++)
	{
		const Rect &r=ans[i];
		if(r.x1<Fraction(1000,1)&&Fraction(-1000,1)<r.x2&&r.y1<Fraction(1000,1)&&Fraction(0,1)<r.y2)s.push_back(r);
	}
}
int N,M;
vector<Rect>LEFT,RIGT;
bool ILLUMINATED[1201];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		LEFT.clear(),RIGT.clear();
		for(int i=0,x1,x2,y1,y2;i<N+M;i++)
		{
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			(i<N?LEFT:RIGT).push_back(Rect(i,x1,x2,y1,y2));
		}
		for(int i=0;i<N;i++)ILLUMINATED[i]=false;
		sort(LEFT.begin(),LEFT.end(),CmpY2());
		sort(RIGT.begin(),RIGT.end(),CmpY2());
		vector<Rect>now=RIGT;
		for(int i=0;i<(int)now.size();i++)now[i].id=UNUSED;
		for(int signify=2;signify<=2000;signify++)
		{
			Multiply(now,signify-1,signify);
			Filter(now,signify%2==0?LEFT:RIGT,ILLUMINATED);
		}
		vector<int>ans;
		for(int i=0;i<N;i++)if(ILLUMINATED[i])ans.push_back(i);
		printf("%d\n",(int)ans.size());
		for(int i=0;i<(int)ans.size();i++)
		{
			if(i)putchar(' ');
			printf("%d",ans[i]+1);
		}
		puts("");
	}
	return 0;
}
