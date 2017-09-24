#include <stack>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <set>
using namespace std;
#define EPS 1e-8
#define PI 3.141592653589793238462643383279

#define sqr(a) (a)*(a)
const int maxn=2e5+1;
struct pol{
    long long x,y;
    double angle;
    long long r_2;
    pol(){}
    pol(long long x,long long y,double angle);
    bool operator <(const pol rhs) const {
        if (abs(angle-rhs.angle)>=EPS)
            return angle<rhs.angle+EPS;
        return r_2<rhs.r_2+EPS;
    }
};
pol p[maxn];
vector<pol> z;
set<pair<int,int>> x;
bool cmp(int i,int j){
    if (p[i].y==p[j].y)
        return p[i].x>p[j].x;
    return p[i].y<p[j].y;
}
long long crossProd(pol a,pol b,pol c){
    return (b.x-a.x)*(c.y-b.y)-(c.x-b.x)*(b.y-a.y);
}
int main(){
    int n;
    cin>>n;
    for(int i=0; i<n; ++i){
        int a,b;
        cin>>a>>b;
        x.insert({a,b});
    }
    int cnt=0;
    for(auto it=x.begin(); it!=x.end(); ++it){
        p[cnt].x=it->first;
        p[cnt++].y=it->second;
    }
    n=cnt;
    if (n==1){
        cout<<0<<"\n"<<0;
        return 0;
    }
    int id=0;
    for (int j=1; j<n; ++j){
        if (cmp(j,id))
            id=j;
    }
    swap(p[id],p[0]);
    for(int i=1; i<n; ++i){
        double ang=atan2(p[i].y-p[0].y,p[i].x-p[0].x);
        while (ang<0)
            ang+=2*PI;
        while (ang>=2*PI)
            ang-=2*PI;
        p[i].angle=ang;
        p[i].r_2=(sqr(p[i].x-p[0].x)+sqr(p[i].y-p[0].y));
    }

    sort(p+1,p+n);
    z.push_back(p[0]);
    z.push_back(p[1]);
    for (int i=2; i<n; ++i){
        while (crossProd(z[z.size()-2],z[z.size()-1],p[i])<0 )
            z.pop_back();
        z.push_back(p[i]);
    }
    double per=0;
    double ans=0;
    for(int i=0; i<z.size(); ++i)
        per+=sqrt(sqr(z[(i+1)%z.size()].x-z[i].x)+sqr(z[(i+1)%z.size()].y-z[i].y));
    cout<<fixed<<setprecision(20);
    cout<<per<<"\n";
    for(int i=1; i<z.size()-1; ++i){

        long long ar=(z[i+1].x-z[0].x)*(z[i].y-z[0].y)-(z[i].x-z[0].x)*(z[i+1].y-z[0].y);
        ans+=ar/2.0;
    }
    cout<<abs(ans);
    return 0;
}
