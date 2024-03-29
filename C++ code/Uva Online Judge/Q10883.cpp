#include<cstdio>
#include<cstdlib>
int T,n;
double S;
double pow(double a,int b)
{
	double ans=1;
	while(b)
	{
		if(b&1)
		{
			ans*=a;
		}
		a*=a;
		b>>=1;
	}
	return ans;
}
double C(int a,int b)
{
	if(b<=a/2) b=a-b;
	//printf(" %d %d\n",a,b);
	double ans=1;
	for(int i=b+1;i<=a;i++)
	{//i=2,a=2,b=1
		ans*=i;
		ans/=i-b;
		//printf(" %lf\n",ans);
	}
	return ans;
}
int main()
{
	scanf("%d",&T);
	double ans;
	for(int kase=1;kase<=T;kase++)
	{
		scanf("%d",&n);
		n--;
		ans=0;
		for(int i=0;i<=n;i++)
		{
			scanf("%lf",&S);
			//printf(" %lf %lf\n",S,C(n,i));
			ans+=S*C(n,i);
		}
		ans/=pow(2,n);//2^n
		printf("Case #%d: %.3lf\n",kase,ans);
	}
	return 0;
}
