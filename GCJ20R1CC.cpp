#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cmath>
#include <set>
#include <map>
#define N 10002
using namespace std;
typedef long long ll;
const ll mod = 1000000007LL;
int t;
int n, d;
ll a[N];
ll getgcd(ll x, ll y) {
  return y==0 ? x : getgcd(y, x%y);
}
int main() {
  //freopen("in.txt", "r", stdin);
  //freopen("out.txt", "w", stdout);
  cin>>t;
  for (int cas=1; cas<=t; ++cas) {
    cin>>n>>d;
    for (int i = 1; i <= n; ++i) {
      scanf("%lld", &a[i]);
    }
    map<pair<ll, ll>, vector<pair<ll, ll>>> mp;
    mp.clear();
    double lv = 0, rv = 400000000000.0;
    for (int j = 1; j <= 50; ++j) {
    //  cout<<"rv="<<rv<<endl;
      double mid = (lv+rv)*0.5;
      int tot=0;
      for (int i = 1; i <= n; ++i) {
        tot += (int)floor((double)a[i]/mid);
      }
      if (tot >= d) {
        lv = mid;
      } else {
        rv = mid;
      }
    }
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= d; ++j) {
        if (a[i]>rv*j) continue;
        ll d2=getgcd(a[i], j);
        mp[make_pair(a[i]/d2, j/d2)].push_back(make_pair(a[i], j));
      }
    }
    int ans=d;
    for (auto& itr : mp) {
      sort(itr.second.begin(), itr.second.end());
      int cnt1=0;
      int cnt2=0;
      for (int i = 0; i < itr.second.size(); ++i) {
        if (cnt1+itr.second[i].second <= d) {
          cnt1 += itr.second[i].second;
          cnt2++;
        } else {
          break;
        }
      }
      ans = min(ans, d-cnt2);
    }
    cout<<"Case #"<<cas<<": "<<ans<<endl;
  }
  return 0;
}
