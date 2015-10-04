#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define maxSegN 200005

struct segnode{
	int count,l,r;//data?
	int mark;//mark,sample(addition)
	segnode*c[2];
	void add(int x){mark+=x;count+=(r-l+1)*x;}
	void push(){
		if(c[0]&&mark){
			c[0]->add(mark);
			c[1]->add(mark);
			mark=0;
		}
	}
	void maintain(){
		if(c[0]){
			count=c[0]->count+c[1]->count;
			//more information maintain?
		}
	}
}pool[maxSegN],*stp,*root;
segnode*segbuild(int l,int r){
	segnode*o=stp++;
	o->l=l;o->r=r;//sometimes it's useless;
	int mid=(l+r)/2;
	if(l<r)o->c[0]=segbuild(l,mid),o->c[1]=segbuild(mid+1,r),o->maintain();
	else{
		//init information?
	}
	return o;
}
int ql,qr,qv;//query L,query R,query value
int query(segnode*o,int l,int r){
	o->push();
	if(ql<=l&&r<=qr)return o->count;
	else{
		int mid=(l+r)/2,ans=0;
		if(ql<=mid)ans+=query(o->c[0],l,mid);
		if(qr>mid)ans+=query(o->c[1],mid+1,r);
		return ans;
	}
}
void modify(segnode*o,int l,int r){
	o->push();
	if(ql<=l&&r<=qr)o->add(qv);
	else{
		int mid=(l+r)/2;
		if(ql<=mid)modify(o->c[0],l,mid);
		if(qr>mid)modify(o->c[1],mid+1,r);
		o->maintain();
	}
}
void segInit(int N){
	memset(pool,0,sizeof pool);//dangerous!O(N)per test case.
	stp=pool;
	root=segbuild(1,N);
}
int main(){
	int n;
	scanf("%d",&n);
	segInit(n);
	return 0;
}
