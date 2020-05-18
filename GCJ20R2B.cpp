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
#define N 102
using namespace std;
typedef long long ll;
const ll mod = 1000000007LL;
int t, c, d;
int cnt[N];
bool vis[N];
int dis[N];
vector<pair<int, int>> edges;
int main() {
  cin>>t;
  for (int cas=1; cas<=t; ++cas) {
    cin>>c>>d;
    edges.clear();
    for (int i = 2; i <= c; ++i) {
      scanf("%d", &cnt[i]);
     // cnt[i] = -cnt[i];
    }
    for (int i = 1; i <= d; ++i) {
      int u, v;
      scanf("%d%d", &u, &v);
      edges.push_back(make_pair(u, v));
    }
    int ans[1002];
    for (int i = 1; i <= d; ++i) {
      ans[i] = 1000000;
    }
    int cur=1;
    memset(vis, false, sizeof(vis));
    vis[1] = true;
    int dd = 1;
    dis[1] = 0;
    while(true) {
      int num=0;
      vector<pair<int, int>> tmp;
      tmp.clear();
      for (int i = 0; i < d; ++i) {
        int u = edges[i].first;
        int v = edges[i].second;
        if (vis[u] && !vis[v] && ((cnt[v]<0 && -cnt[v] == cur) || (cnt[v] >0 &&cnt[v] == dd)) ) {
          tmp.push_back(make_pair(i, v));
          num++;
        } else if (vis[v] && !vis[u] && ((cnt[u]<0 && -cnt[u] == cur) || (cnt[u] >0 && cnt[u]==dd))) {
          tmp.push_back(make_pair(i, u));
          num++;
        }
      }
      if (!num) {
        int mind = 2000000001;
        for (int i = 0; i < d; ++i) {
          int u = edges[i].first;
          int v = edges[i].second;
          if (vis[u] && !vis[v] && (cnt[v]>0)) {
            mind = min(mind, cnt[v]);
          }
          else if (vis[v] && !vis[u] && cnt[u] > 0) {
            mind = min(mind, cnt[u]);
          }
        }
       // if (mind < 1000000001) cout<<"d="<<mind<<endl;
        if (mind >= 2000000001) break;
        dd = mind;
        for (int i = 0; i < d; ++i) {
          int u = edges[i].first;
          int v = edges[i].second;
          if (vis[u] && !vis[v] && (cnt[v]==dd)) {
            tmp.push_back(make_pair(i, v));
          }
          else if (vis[v] && !vis[u] && cnt[u] == dd) {
            mind = min(mind, cnt[u]);
            tmp.push_back(make_pair(i, u));
          }
        }
      }
    //  if (tmp.size() > 0) cout<<tmp.size()<<endl;
      for (int i = 0; i < tmp.size(); ++i) {
        int v= tmp[i].second;
        int id=tmp[i].first;
        int u = edges[id].first;
        if (u==v) u = edges[id].second;
        if (dd - dis[u] <= 0) continue;
        if (vis[v]) continue;
        ans[id+1] = dd-dis[u];
        dis[v] = dd;
        vis[v] = true;
        cur++;
      }
      dd++;
    }
    cout<<"Case #"<<cas<<": ";
    for (int i = 1; i <= d; ++i) {
      cout<<ans[i];
      if (i < d) cout<<" ";
      else cout<<endl;
    }
  }
  return 0;
}
