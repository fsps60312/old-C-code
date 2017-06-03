#include<cstdio>
#include<cassert>
#include<algorithm>
#include<vector>
using namespace std;
const int INF=2147483647;
template<class T>void getmin(T &a,const T &b){if(b<a)a=b;}
template<class T>void getmax(T &a,const T &b){if(a<b)a=b;}
int N;
void GetWidth(const char *g,int *w)
{
	for(int i=0,ans=0;i<N;i++)
	{
		if(ans)--ans;
		while(ans<1000&&(i-ans<0||g[i-ans]!='X')&&(i+ans>=N||g[i+ans]!='X'))++ans;
		w[i]=ans;
	}
}
char GRID[2000][2001];
vector<int>ShipIsVertical()
{
	int axis=-1;
	vector<int>ans,locs;
	for(int r=0;r<N;r++)
	{
		int left=INF,rigt=-INF;
		for(int c=0;c<N;c++)if(GRID[r][c]=='r')getmin(left,c),getmax(rigt,c);
		if(left!=INF)
		{
			if((left+rigt)%2!=0)return vector<int>();
			const int ta=(left+rigt)/2;
			if(axis==-1)axis=ta;
			else if(axis!=ta)return vector<int>();
			ans.push_back((rigt-left)/2+1);
			locs.push_back(r);
		}
	}
	assert(locs.back()-locs.front()==(int)locs.size()-1);
	return ans;
}
vector<int>RotateGrid()
{
	if(ShipIsVertical().empty())
	{
		for(int i=0;i<N;i++)
		{
			for(int j=i+1;j<N;j++)swap(GRID[i][j],GRID[j][i]);
		}
//		puts("rotated");
	}
//	else puts("unmoved");
	const vector<int>&ans=ShipIsVertical();
	assert(!ans.empty());
	return ans;
}
void GetSpace(const int n,const int *width,const vector<int>&ship,bool *ans)
{
	for(int i=1;i<(int)ship.size();i++)assert(ship[i-1]<=ship[i]);
	int cur=(int)ship.size()-1;
	for(int i=0;i<n;i++)
	{
		while(cur>=0&&ship[cur]>width[i])--cur;
		++cur;
		if(cur==(int)ship.size())ans[i]=true,--cur;
		else ans[i]=false;
	}
}
int WIDTH[2000][2000];
bool SPACE[2000][2000];
void GetSpace(const vector<int>&ship,int &start_r,int &start_c,int &offset)
{
	vector<int>upon,down;
	if(true)
	{
		int cur=0;
		while(cur<(int)ship.size()&&(cur==0||ship[cur-1]<=ship[cur]))upon.push_back(ship[cur++]);
		while(cur<(int)ship.size())down.push_back(ship[cur++]);
	}
	reverse(down.begin(),down.end());
	for(int c=0;c<N;c++)
	{
		static int widths[6000];
		static bool ansu[6000],ansd[6000];
		for(int i=0;i<2000;i++)widths[i]=widths[2000+N+i]=1000;
		for(int i=0;i<N;i++)widths[2000+i]=WIDTH[i][c];
		GetSpace(4000+N,widths,upon,ansu);
		reverse(widths,widths+(4000+N));
		GetSpace(4000+N,widths,down,ansd);
		reverse(ansd,ansd+(4000+N));
		for(int i=0;i<N;i++)SPACE[i][c]=(ansu[2000+i]&&ansd[2000+i+1]);
	}
	for(int i=0;i<N;i++)for(int j=0;j<N;j++)if(GRID[i][j]=='r')
	{
		for(int k=j;;k++)if(k+1==N||GRID[i][k+1]!='r')
		{
			assert((j+k)%2==0);
			offset=(int)upon.size()-1;
			start_r=i+offset,start_c=(j+k)/2;
			return;
		}
	}
	assert(0);
}
#include<queue>
int Bfs(const int start_r,const int start_c,const int upon_offset,const int down_offset,const int hori_offset)
{
//	printf("(%d,%d),up=%d,down=%d,hori=%d\n",start_r,start_c,upon_offset,down_offset,hori_offset);for(int i=0;i<N;i++){for(int j=0;j<N;j++)putchar('0'+SPACE[i][j]);puts("");}
	static int dist[2000][2000];
	assert(0<=start_r&&start_r<N&&0<=start_c&&start_c<N);
	for(int i=0;i<N;i++)for(int j=0;j<N;j++)dist[i][j]=INF;
	queue<int>q;
	q.push(start_r),q.push(start_c),q.push(0);
	int ans=INF;
	while(!q.empty())
	{
		const int r=q.front();q.pop();
		const int c=q.front();q.pop();
		const int now_dist=q.front();q.pop();
		if(r<0){getmin(ans,now_dist+down_offset);continue;}
		if(r>=N){getmin(ans,now_dist+upon_offset);continue;}
		if(c<0||c>=N){getmin(ans,now_dist+hori_offset);continue;}
		if(!SPACE[r][c]||dist[r][c]<=now_dist)continue;
		dist[r][c]=now_dist; 
		static int d[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
		for(int i=0;i<4;i++)q.push(r+d[i][0]),q.push(c+d[i][1]),q.push(now_dist+1);
	}
	return ans;
}
int Solve()
{
	const vector<int>&ship=RotateGrid();
	for(int i=0;i<N;i++)GetWidth(GRID[i],WIDTH[i]);
//	for(int i=0;i<N;i++){for(int j=0;j<N;j++)putchar('0'+WIDTH[i][j]);puts("");}
	int start_r,start_c,upon_offset,hori_offset;
	GetSpace(ship,start_r,start_c,upon_offset);
	hori_offset=0;
	for(int i=0;i<(int)ship.size();i++)getmax(hori_offset,ship[i]-1);
	return Bfs(start_r,start_c,upon_offset,(int)ship.size()-1-upon_offset,hori_offset);
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("rob7a.in","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%s",GRID[i]);
		const int ans=Solve();
		if(ans==INF)puts("NIE");
		else printf("%d\n",ans);
	}
	return 0;
}
