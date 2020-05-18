#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cmath>
#include <set>
#include <map>
#include <queue>
#define N 100005
using namespace std;
typedef long long ll;
const ll mod = 1000000007LL;
int t, n;
ll L, R;
int main() {
  cin>>t;
  for (int cas=1; cas<=t; ++cas) {
    cin>>L>>R;
    ll x=1;
    if (L >= R) {
      ll l = 1, r = 2000000000LL;
      while(l < r) {
        ll m=(l+r)/2;
        ll tot=(1+m)*m/2;
        if (L-tot < R) {
          r = m;
        } else {
          l = m + 1;
        }
      }
      if (L - (r+1)*r/2 >= 0) {
        L -= (r+1)*r/2;
        x = r;
      } else {
        r--;
        L -= (r+1)*r/2;
        cout<<"Case #"<<cas<<": "<<r<<" "<<L<<" "<<R<<endl;
        continue;
      }
      l = 0, r = 2000000000LL;
      while(l < r) {
        ll m = (l+r+1)/2;
        ll tr = (m+1)/2;
        ll tl = (m-tr);
        ll sr = (tr >= 1 ? ((x+tr)*tr) : 0);
        ll sl = (tl >= 1 ? ((x+tl+1)*tl) : 0);
        if (sr <= R && sl <= L) {
          l = m;
        } else {
          r = m-1;
        }
      }
      if (r) {
        ll tr = (r+1)/2;
        ll tl = (r-tr);
        ll sr = (tr >= 1 ? ((x+tr)*tr) : 0);
        ll sl = (tl >= 1 ? ((x+tl+1)*tl) : 0);
        L -= sl;
        R -= sr;
      }
      cout<<"Case #"<<cas<<": "<<x + r<<" "<<L<<" "<<R<<endl;
    } else if (L < R) {
      ll l = 1, r = 2000000000LL;
      while(l < r) {
        ll m = (l+r)/2;
        ll tot = (1+m)*m/2;
        if (R - tot <= L) {
          r = m;
        } else {
          l = m+1;
        }
      }
   //   cout<<"r="<<r<<endl;
      if (R - (r+1)*r/2 >= 0) {
        R -= (r+1)*r/2;
        x = r;
      } else {
        r--;
        R -= (r+1)*r/2;
        cout<<"Case #"<<cas<<": "<<r<<" "<<L<<" "<<R<<endl;
        continue;
      }
      l = 0; r = 2000000000LL;
      while(l < r) {
        ll m = (l+r+1)/2;
        ll tl = (m+1)/2;
        ll tr = (m-tl);
        ll sl = (tl >= 1 ? ((x+tl)*tl) : 0);
        ll sr = (tr >= 1 ? ((x+tr+1)*tr) : 0);
        if (sr <= R && sl <= L) {
          l = m;
        } else {
          r = m-1;
        }
      }
   //   cout<<"r2="<<r<<endl;
      if (r) {
        ll tl = (r+1)/2;
        ll tr = (r-tl);
        ll sl = (tl >= 1 ? ((x+tl)*tl) : 0);
        ll sr = (tr >= 1 ? ((x+tr+1)*tr) : 0);
        L -= sl;
        R -= sr;
      }
      cout<<"Case #"<<cas<<": "<<x + r<<" "<<L<<" "<<R<<endl;
    }
  }
  return 0;
}
