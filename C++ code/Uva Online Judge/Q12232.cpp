#include<cstdio>
#include<cstdlib>
#define debug(...) ;//__VA_ARGS__
int n,Q;
struct pairtype{int head,v;};
pairtype S[20001];
bool conflicting;
bool isnum(char a){return a>='0'&&a<='9';}
bool inthree(char *d,int &a,int &b,int &c)
{
	a=b=c=0;
	while(!isnum(*d))d++;
	while(isnum(*d)){a*=10;a+=(*d)-'0';d++;}
	//debug(printf("a=%d\n",a););
	while(!isnum(*d))d++;
	while(isnum(*d)){b*=10;b+=(*d)-'0';d++;}
	//debug(printf("b=%d\n",b););
	while(!isnum(*d)&&(*d))d++;
	if(!(*d))return false;
	while(isnum(*d)){c*=10;c+=(*d)-'0';d++;}
	//debug(printf("c=%d\n",c););
	return true;
}
pairtype findset(int a)
{
	if(S[a].head==a)return S[a];
	if(S[a].head==0)return (pairtype){-a,0};
	pairtype b=findset(S[a].head);
	if(b.head>0)
	{
		S[a].head=a;
		S[a].v^=b.v;
		return S[a];
	}
	else
	{
		S[a].head=-b.head;
		b.v^=S[a].v;
		S[a].v=b.v;
		return b;
	}
}
void give(int v)
{
	if(conflicting)return;
	if(v==-1)printf("I don't know.\n");
	else printf("%d\n",v);
}
int main()
{
	freopen("in.txt","r",stdin);
	int kase=1;
	while(scanf("%d%d",&n,&Q)==2&&(n||Q))
	{
		printf("Case %d:\n",kase++);
		debug(printf("n=%d Q=%d\n",n,Q););
		conflicting=false;
		for(int i=1;i<=n;i++)S[i].head=S[i].v=0;
		char tstr[1000];do{scanf("%c",&tstr[0]);}while(tstr[0]!='\n');
		int qn=0;
		while(Q--)
		{
			int sl=-1;
			while(scanf("%c",&tstr[++sl])==1&&tstr[sl]!='\n');tstr[sl]=0;
			debug(printf("tstr=\"%s\"\n",tstr););
			debug(
			{
				for(int i=1;i<=n;i++)printf("%d:%d\t%d\n",i,S[i].head,S[i].v);
			});
			int ni=0;while(tstr[ni]==' ')ni++;
			if(tstr[ni++]=='I')
			{
				//debug(printf("I\n"););
				qn++;
				int p,q,v;
				if(inthree(&tstr[ni],p,q,v))
				{
					//debug(printf("inthree is true\n"););
					p++,q++;
					pairtype j=findset(p),j2=findset(q);
					if(j2.head==j.head)
					{
						if(j2.v^j.v!=v)
						{
							printf("The first %d facts are conflicting.\n",qn);
							conflicting=true;
						}
					}
					else if(j.head>0)
					{
						S[q].head=q;
						S[q].v=v^j.v;
					}
					else
					{
						S[q].head=-j.head;
						S[q].v=v^j.v;
					}
				}
				else
				{
					//debug(printf("inthree is false\n"););
					p++;
					pairtype j=findset(p);
					if(j.head>0)
					{
						if(S[j.head].v!=q^j.v)
						{
							printf("The first %d facts are conflicting.\n",qn);
							conflicting=true;
						}
					}
					else
					{
						j.head*=-1;
						S[j.head].head=j.head;
						S[j.head].v=q^j.v;
					}
				}
			}
			else
			{
				//debug(printf("Q\n"););
				while(!isnum(tstr[ni]))ni++;
				int k;sscanf(&tstr[ni],"%d",&k);
				while(isnum(tstr[ni]))ni++;
				if(k==1)
				{
					sscanf(&tstr[ni],"%d",&k);k++;
					pairtype p=findset(k);
					debug(printf("p=%d %d\n",p.head,p.v););
					if(p.head>0)give(p.v);
					else give(-1);
				}
				else
				{
					int hn=0,ans=0;
					bool ok=true;
					for(int i=0,j;i<k;i++)
					{
						sscanf(&tstr[ni],"%d",&j);
						while(!isnum(tstr[ni]))ni++;
						while(isnum(tstr[ni]))ni++;
						j++;
						pairtype p=findset(j);
						debug(printf("j=%d:p=%d %d\n",j,p.head,p.v););
						if(hn&&p.head<0&&hn!=p.head)ok=false;
						hn=p.head;
						ans^=p.v;
					}
					give(ok?ans:-1);
				}
			}
		}
		printf("\n");
	}
	return 0;
}
