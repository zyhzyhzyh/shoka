#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#define LL long long
using namespace std;
struct SAP
{
	const int M=1000010,N=1010;
	struct Edge
	{
		int next,other,va;
	}e[M];
	int head[N],di[N],dis[N],pre[N],vh[N],his[N],tot,S,T,inf=2e9;
	inline void add(int x,int y,int z)
	{
		e[++tot].next=head[x];head[x]=tot;e[tot].other=y;e[tot].va=z;
		e[++tot].next=head[y];head[y]=tot;e[tot].other=x;e[tot].va=0;
	}
	void init()
	{
		memset(head,0,sizeof(head));memset(dis,0,sizeof(dis));tot=1;
		memset(vh,0,sizeof(vh));
	}
	int flow()
	{
		for(int i=S;i<=T;i++) di[i]=head[i];
		vh[0]=T+1;int u=S,aug=inf,ans=0;
		while (dis[S]<T+1)
		{
			bool flag=0;his[u]=aug;
			for(int i=di[u];i;i=e[i].next)
			{
				int v=e[i].other;
				if (e[i].va>0&&dis[u]==dis[v]+1)
				{
					pre[v]=di[u]=i;flag=1;aug=min(aug,e[i].va);u=v;
					if (u==T)
					{
						ans+=aug;
						for(;u!=S;u=e[pre[u]^1].other) 
						{
							e[pre[u]].va-=aug;
							e[pre[u]^1].va+=aug;
						}
						aug=inf;
					}
					break;
				}
			}
			if (flag) continue;
			if (--vh[dis[u]]==0) break;
			int Min=T+1,j;
			for(int i=head[u];i;i=e[i].next)
			{
				int v=e[i].other;
				if (e[i].va>0&&dis[v]<Min)
				{
					Min=dis[v];j=i;
				}
			}
			vh[dis[u]=Min+1]++;di[u]=j;
			if (u!=S)
			{
				u=e[pre[u]^1].other;aug=his[u];
			}
		}
		return ans;
	}
};
int main()
{
	return 0;
}
