#include <iostream>
#include <algorithm>
#include <cstring>

#define rep(i,n) for(int i=0;i<n;i++)

using namespace std;

struct node{
  int a,b,c;
} v[500010];

bool operator < (node a, node b){
  return a.a!=b.a?a.a>b.a:a.b<b.b;
}

int n,h[500010],ans;

int main(){
  cin>>n;
  rep(i,n)cin>>v[i].a;
  rep(i,n)cin>>v[i].b,h[i]=v[i].b;
  rep(i,n)cin>>v[i].c;
  sort(v,v+n);
  sort(h,h+n);
  rep(i,n)v[i].b = n-(lower_bound(h,h+n,v[i].b)-h);

  memset(h,128,sizeof(h));
  
  rep(i,n){
    int temp = -0x7fffffff;

    for(int j=v[i].b-1;j;j-=j&-j) {
      temp=max(temp,h[j]);
    }
    if(temp>v[i].c)ans++;
    for(int j=v[i].b;j<=n;j+=j&-j)h[j]=max(h[j],v[i].c);
  }
  cout<<ans<<endl;

}