#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cmath>
#define N 100000
#define SIZE 100000
using namespace std;
const double EPS=1e-7;
double cmp(double a,double b){
	if(b-a>=EPS)return 1;
	else if(a-b<=EPS)return 0;
	else return -1;
}
int numPoly,numEdge,ltp,head,tail;
struct Point{
	double x,y;
	Point(){}
	Point(double x,double y):x(x),y(y){}
	void read(){
		scanf("%lf%lf",&x,&y);
	}Point operator+(Point rhs){
		return Point(x+rhs.x,y+rhs.y);
	}Point operator-(Point rhs){
		return Point(x-rhs.x,y-rhs.y);
	}Point operator*(double rhs){
		return Point(x*rhs,y*rhs);
	}Point operator/(double rhs){
		return Point(x/rhs,y/rhs);
	}
}poly[N],all[SIZE];
double dot(Point a,Point b){
	return a.x*b.x+a.y*b.y;
}double cro(Point a,Point b){
	return a.x*b.y-a.y*b.x;
}double ang(Point a){
	double t=atan2(a.y,a.x); 
	if(t<0)t+=acos(0.0)*4.0;
	return t;
}
struct Line{   
	//A+vt
	Point A,v;
	double angle;
	Line(){}
	Line(Point a,Point b){
		v=b-a;
		A=a;
		angle=ang(v);
	}bool operator<(const Line&rhs)const{
		return angle<rhs.angle;
	}
}lines[SIZE],deq[SIZE];
bool OnTheLeft(Line l,Point p){
	return cro(l.v,p-l.A)>=EPS;
}Point intersection(Line A,Line B){
	Point u=A.A-B.A;
	double t=cro(A.v,u)/cro(A.v,B.v);
	return B.A+(B.v*t);
}
int main(){
	scanf("%d",&numPoly);
	while(numPoly--){
		scanf("%d",&numEdge);
		for(int i=0;i<numEdge;i++)
			poly[i].read();
		for(int i=0;i<numEdge;i++)
			lines[ltp++]=Line(poly[i],poly[(i+1)%numEdge]);
	}sort(lines,lines+ltp);
	deq[head=tail=0]=lines[0];
	for(int i=1;i<ltp;i++){
		while(head<tail&&!OnTheLeft(lines[i],all[tail-1]))tail--;
		while(head<tail&&!OnTheLeft(lines[i],all[head]))head++;
		if(cmp(deq[tail].angle,lines[i].angle)==0){
			if(!OnTheLeft(lines[i],deq[tail].A))deq[tail]=lines[i];
		}else{
			deq[++tail]=lines[i];
		}if(head<tail)all[tail-1]=intersection(deq[tail-1],deq[tail]);
	}while(head<tail&&!OnTheLeft(deq[head],all[tail-1]))tail--;
	if(tail-head<=1)return puts("0.000"),0;
	else{
		all[tail]=intersection(deq[head],deq[tail]);
		double ans=0.0;
		for(int i=head;i<tail;i++)
			ans+=cro(all[i],all[i+1]);
		ans+=cro(all[tail],all[head]);
		ans/=2.0;
		printf("%.3f\n",fabs(ans));
	}
}
