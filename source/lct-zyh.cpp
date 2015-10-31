#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#define LL long long
#define lc sp[x].son[0]
#define rc sp[x].son[1]
using namespace std;
struct node
{
	int son[2],fa;
	bool Rev;
	inline bool isson(int x){return x==son[1];}
}sp[100010];
char s[10];
int n,m,x,y;
void read(int &x)
{
	char ch=getchar();int mark=1;for(;ch!='-'&&(ch<'0'||ch>'9');ch=getchar());if (ch=='-') mark=-1,ch=getchar();
	for(x=0;ch>='0'&&ch<='9';ch=getchar()) x=x*10+ch-48;x*=mark;
}
inline void pushdown(int x)
{
	if (sp[x].Rev)
	{
		if (lc) sp[lc].Rev^=1;
		if (rc) sp[rc].Rev^=1;
		swap(lc,rc);
		sp[x].Rev=0;
	}
}
inline bool Truefa(int x)
{
	int f=sp[x].fa;
	return sp[f].son[sp[f].isson(x)]==x;
}
void rot(int x,bool mk)
{
	int y=sp[x].fa,z=sp[y].fa;
	sp[x].fa=z;
	if (z&&Truefa(y)) sp[z].son[sp[z].isson(y)]=x;
	sp[y].son[mk]=sp[x].son[!mk];
	if (sp[x].son[!mk]) sp[sp[x].son[!mk]].fa=y;
	sp[x].son[!mk]=y;
	sp[y].fa=x;
}
void splay(int x,int fa)
{
	while (sp[x].fa!=fa)
	{
		int y=sp[x].fa,z=sp[y].fa;
		if (z) pushdown(z);
		pushdown(y);pushdown(x);
		bool t1=sp[y].isson(x),t2;
		if (z!=fa)
		{
			t2=sp[z].isson(y);
			if (t1==t2) rot(y,t2),rot(x,t1);
			else rot(x,t1),rot(x,t2);
		}
		else rot(x,t1);
	}
}
int Find_top(int x)
{
	for(;Truefa(x);x=sp[x].fa);
	return x;
}
int Find_root(int x)
{
	x=Find_top(x); 
	for(pushdown(x);sp[x].son[0];x=sp[x].son[0],pushdown(x));
	return x;
}
void Access(int x)
{
	int add=0;
	for(;x;)
	{
		int r=Find_top(x);
		splay(x,sp[r].fa);
		pushdown(x);
		sp[x].son[1]=add;
		add=x;
		x=sp[x].fa;
	}
}
void RotRoot(int x)
{
	Access(x);
	splay(x,0);
	sp[x].Rev^=1;
}
void Link(int x,int y)
{
	RotRoot(y);
	Access(x);
	pushdown(x);
	sp[x].son[1]=y;sp[y].fa=x;
	Access(y);
}
void Cut(int x,int y)
{
	RotRoot(x);
	Access(y);
	splay(x,0);
	pushdown(x);
	sp[x].son[1]=0;
	sp[y].fa=0;
}
int main()
{
	read(n);read(m);
	for(int i=1;i<=m;i++)
	{
		scanf("%s",s);
		read(x);read(y);
		if (s[0]=='c')
		{
			RotRoot(x);Access(y);
			if (Find_root(y)==x) printf("YES\n");
			else printf("NO\n");
		}
		else if (s[0]=='a')	Link(x,y);
		else Cut(x,y);
	}
	return 0;
}
