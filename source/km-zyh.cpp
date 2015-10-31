
bool dfs(int u)
{
	S[u]=1;
	for(int v=1;v<=n;v++)
		if (!T[v]&&U[u]+V[v]==g[u][v])
		{
			T[v]=1;
			if (pre[v]==-1||dfs(pre[v]))
			{
				pre[v]=u;return 1;
			}
		}
	return 0;
}
int main()
{
	memset(pre,-1,sizeof(pre));
	for(int i=1;i<=n;i++) U[i]=-inf;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) U[i]=max(U[i],g[i][j]);
	for(int k=1;k<=n;k++)
		for(;;)
		{
			memset(vis,0,sizeof(vis));
			memset(S,0,sizeof(S));
			memset(T,0,sizeof(T));
			if (dfs(k)) break;
			int D=inf;
			for(int i=1;i<=n;i++)
				if (S[i])
					for(int j=1;j<=n;j++)
						if (!T[j]) D=min(D,U[i]+V[j]-g[i][j]);
			for(int i=1;i<=n;i++) 
				if (S[i]) U[i]-=D;
			for(int j=1;j<=n;j++) 
				if (T[j]) V[j]+=D;
		}
	int ans=0;
	for(int i=1;i<=n;i++)
		if (pre[i]!=-1) ans+=g[pre[i]][i];
		
	return 0;
}
