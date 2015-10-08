#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
#define REP(i,x,y) for(int i=(x);i<(y);i++)
#define DREP(i,x,y) for(int i=(x);i>(y);i--)
#define N 300000
char st[N],st1[N];
int n,w[N],rank[N],height[N],sa[N];
bool sa_init_equal(int *x,int i,int j,int len)
{
	int s1=i+len<n?x[i+len]:-1,s2=j+len<n?x[j+len]:-1;
	return x[i]==x[j]&&s1==s2;
}
void build()
{
	int *x=rank,*y=height,r=128;
	fill(w,w+r,0);
	REP(i,0,n)w[st[i]]++;
	REP(i,1,r)w[i]+=w[i-1];
	DREP(i,n-1,-1)sa[--w[st[i]]]=i;
	r=0;
	REP(i,0,n)
	{
		if(i==0||st[sa[i]]!=st[sa[i-1]])r++;
		x[sa[i]]=r-1;
	}for(int k=1;r<n;k<<=1,swap(x,y))
	{
		fill(w,w+r,0);
		int y_n=0;
		REP(i,n-k,n)y[y_n++]=i;
		REP(i,0,n)if(sa[i]-k>=0)y[y_n++]=sa[i]-k;
		REP(i,0,n)w[x[y[i]]]++;
		REP(i,1,r)w[i]+=w[i-1];
		DREP(i,n-1,-1)sa[--w[x[y[i]]]]=y[i];
		r=0;
		REP(i,0,n)
		{
			if(i==0||!sa_init_equal(x,sa[i],sa[i-1],k))
				r++;
			y[sa[i]]=r-1;
		}
	}if(rank!=x)copy(x,x+r,rank);
	for(int i=0,j=0;i<n;i++)
	{
		if(j)j--;
		if(rank[i]==n-1)continue;
		int p=sa[rank[i]+1];
		while(p+j<n&&i+j<n&&st[p+j]==st[i+j])j++;
		height[rank[i]]=j;
	}
}int pos;
int main(){
	gets(st);
	pos=n=strlen(st);
	st[n++]='#';
	gets(st+n);
	n=strlen(st);
	build();
	int ans=0;
	REP(i,0,n-1)
	{
		int x=sa[i],y=sa[i+1];
		if(x>y)swap(x,y);
		if(x<pos&&y>pos)ans=max(height[i],ans);
	}printf("%d\n",ans);
}
