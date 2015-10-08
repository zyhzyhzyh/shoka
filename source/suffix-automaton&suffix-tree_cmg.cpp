#include<cstdio>
//妈妈我终于会写后缀树了！

#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
#define N 1500000
struct node{
	node*go[27],*pa;
	node*trans[27];
	int l,stpos,r;
}T[N],*stp=T,*root,*last,*samid[N];
int n,sa[N],height[N],rank[N],cnt;char st[N];
void expand(int x)
{
	node*p=stp++,*t=last;
	p->l=last->l+1;
	p->stpos=last->stpos+1;
	samid[p->stpos]=p;
	last=p;
	for(;t&&!t->go[x];t=t->pa)t->go[x]=p;
	if(!t)p->pa=root;
	else{
		if(t->l+1==t->go[x]->l)p->pa=t->go[x];
		else{
			node*r=stp++,*q=t->go[x];
			*r=*q;
			r->l=t->l+1;
			r->stpos=-1;
			q->pa=p->pa=r;
			for(;t&&t->go[x]==q;t=t->pa)t->go[x]=r;
		}
	}
}void build_suffixtree()
{
	for(int i=n;i>=1;i--)
	{
		for(node*x=samid[i];x&&!x->r;x=x->pa)x->r=i-1;
	}
	for(node *x=--stp;x>root;x--)
	{
		node*fa=x->pa;
		fa->trans[st[x->r-fa->l]-'a']=x;
	}
}void dfs(node*x)
{
	if(x->stpos>=1)sa[cnt++]=x->stpos-1;
	for(int i=0;i<26;i++)
		if(x->trans[i])dfs(x->trans[i]);
}int q[N],head,tail,Left[N],Right[N];
int main(){
	gets(st);root=stp++;last=root;
	n=strlen(st);
	for(int i=n-1;i>=0;i--)
		expand(st[i]-'a');
	reverse(st,st+n);
	build_suffixtree();
	dfs(root)；
		reverse(st,st+n);
	for(int i=0;i<n;i++)sa[i]=n-sa[i]-1;
	for(int i=0;i<n;i++)rank[sa[i]]=i;
	//get a suffix array ！

	for(int i=0,j=0;i<n;i++)
	{
		if(j)j--;
		if(rank[i]==n-1)continue;
		int p=sa[rank[i]+1];
		while(p+j<n&&i+j<n&&st[i+j]==st[p+j])
			j++;
		height[rank[i]]=j;
	}long long ans=(long long)(n+1)*n*(n-1)/2LL;
	head=0;q[tail++]=0;
	for(int i=1;i<n-1;i++)
	{
		while(head<tail&&height[q[tail-1]]>height[i])tail--;
		if(head<tail)Left[i]=q[tail-1]+1;
		else Left[i]=0;
		q[tail++]=i;
	}q[tail=0]=n-2;tail++;Right[n-2]=n-2;
	for(int i=n-3;i>=0;i--)
	{
		while(head<tail&&height[q[tail-1]]>=height[i])tail--;
		if(head<tail)Right[i]=q[tail-1]-1;
		else Right[i]=n-2;
		q[tail++]=i;
	}for(int i=0;i<n-1;i++)
	{
		ans-=(long long)(i-Left[i]+1)*(Right[i]-i+1)*2LL*height[i];
	}cout<<ans<<endl;
}
