#include <bits/stdc++.h>
#define sez(a) (int)(a.size())
using namespace std;
typedef long double ld;
typedef long long ll;
struct pt{
    int x,y;
    bool operator <(const pt & rhs) const{
        return x<rhs.x || x==rhs.x && y<rhs.y;
    }
};
bool comp(pt fi,pt se){
     return fi.x<se.x || fi.x==se.x && fi.y<se.y;
}
int cross_prod(pt a,pt b,pt c){
    //cout<<"CROSS "<<a.x<<" "<<a.y<<" "<<b.x<<" "<<b.y<<" "<<c.x<<" "<<c.y<<"\n";
    //cout<<(a.x-b.x)*(c.y-b.y)-(a.y-b.y)*(c.x-b.x)<<"\n";
    return (a.x-b.x)*(c.y-b.y)-(a.y-b.y)*(c.x-b.x);
}
vector<pt> convex_hull(vector<pt> &pts){
    if (pts.size()<=2){
        return pts;
    }
    sort(pts.begin(),pts.end(),comp);
    pt fi=pts.front();
    vector<pt> down;
    vector<pt> up;
    int n=pts.size();
    down.push_back(fi);
    up.push_back(fi);
    for(int i=1; i<n; ++i){
        while(down.size()>=2 && cross_prod(down[down.size()-2],down.back(),pts[i])<=0){
     //       cout<<"DOWN "<<down[down.size()-2].x<<" "<<down[down.size()-2].y<<" "<<down.back().x<<" "<<down.back().y<<" "<<pts[i].x<<" "<<pts[i].y<<"\n";
            down.pop_back();
        }
        down.push_back(pts[i]);
        while(up.size()>=2 && cross_prod(up[up.size()-2],up.back(),pts[i])>=0){
            //cout<<"UP "<<up[up.size()-2].x<<" "<<up[up.size()-2].y<<" "<<up.back().x<<" "<<up.back().y<<" "<<pts[i].x<<" "<<pts[i].y<<"\n";
            up.pop_back();
        }
        up.push_back(pts[i]);
    }
   // cout<<"UP\n";
//    for(int i=0; i<up.size(); ++i){
//        cout<<up[i].x<<" "<<up[i].y<<"\n";
//    }
//    cout<<"UPEND\n";
    for(int i=down.size()-1; i>0; --i){
        up.push_back(down[i]);
    }
    return up;
}
int main(){
    #ifdef kolya
        freopen("input.txt","r",stdin);
    #endif // kolya
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin>>n;
    vector<pt> z;
    for(int i=0; i<n; ++i){
        int x,y;
        cin>>x>>y;
        z.push_back({x,y});
    }
    vector<pt> hull=convex_hull(z);
//    for(int i=0; i<hull.size(); ++i){
//        cout<<hull[i].x<<" "<<hull[i].y<<"\n";
//    }
   // cout<<hull.size();
    ld per=0;
    ld area=0;
    n=hull.size();
    for(int i=0; i<n; ++i){
        per+=sqrt((hull[(i+1)%n].x-hull[i].x)*(hull[(i+1)%n].x-hull[i].x)+(hull[(i+1)%n].y-hull[i].y)*(hull[(i+1)%n].y-hull[i].y));
        area+=0.5*(hull[(i+1)%n].x-hull[i].x)*(hull[(i+1)%n].y+hull[i].y);
    }
    cout.precision(15);
    cout<<fixed<<per<<"\n";
    cout<<fixed<<abs(area);
}
