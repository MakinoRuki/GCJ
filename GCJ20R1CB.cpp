#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cmath>
#include <set>
#include <map>
#define N 200005
using namespace std;
typedef long long ll;
const ll mod = 1000000007LL;
int t, x, y;
vector<pair<pair<ll, string>, int>> qs;
vector<pair<int, int>> cs;
int upb[30];
ll pw[17];
ll u;
bool has[27];
int main() {
  freopen("in.txt", "r", stdin);
  //freopen("out.txt", "w", stdout);
  cin>>t;
  pw[0] = 1LL;
  for (int i = 1; i <= 16; ++i) {
      pw[i] = pw[i-1] * 10LL;
  }
  for (int cas=1; cas<=t; ++cas) {
      for (int i = 0; i < 26; ++i) {
          upb[i] = 10;
      }
      cin>>u;
      qs.clear();
      cs.clear();
      set<pair<int,int>> ss;
      ss.clear();
      memset(has, false, sizeof(has));
      for (int i = 0; i < 10000; ++i) {
          ll q;
          string s;
          cin>>q>>s;
          int cnt=0;
          ll q2=q;
          while(q2) {
              cnt++;
              q2/=10;
          }
          qs.push_back(make_pair(make_pair(q,s), cnt));
          if (q==-1) continue;
          cs.push_back(make_pair(0, 0));
          if (cnt==s.size()) {
              upb[s[0]-'A'] = (int)min((ll)upb[s[0]-'A'], q/pw[cnt-1]);
          }
          for (int j = 0; j < s.size(); ++j) {
            has[s[j]-'A'] = true;
          }
      }
      for (int i = 0; i < 26; ++i) {
          if (upb[i] < 10) {
              ss.insert(make_pair(upb[i], i));
          }
      }
      string ans(10, ' ');
      bool vis[26];
      memset(vis, false, sizeof(vis));
      if (qs[0].first.first == -1) {
        for (int i= 0; i < 26; ++i) {
          if (!has[i]) continue;
          int j;
          for (j = 0; j < 10000; ++j) {
            if (qs[j].first.second[0] == 'A'+i) break;
          }
          if (j >= 10000) {
            ans[0] = 'A' + i;
            vis[i] = true;
            break;
          }
        }
        for (int i = 1; i <= 9; ++i) {
          for (int j = 0; j < 26; ++j) {
            if (has[j] && !vis[j]) {
              ans[i] = 'A'+j;
              vis[j] = true;
              break;
            }
          }
        }
        cout<<"Case #"<<cas<<": "<<ans<<endl;
        continue;
      }
      int i;
      for (i = 1; i <= 9; ++i) {
          while(!ss.empty()) {
              auto top = *ss.begin();
              ss.erase(top);
              if (!vis[top.second]) {
                  ans[i] = 'A'+top.second;
                  vis[top.second]=true;
                  break;
              }
          }
          if (ans[i] == ' ' && ss.empty()) {
              break;
          }
      }
      for (int i2 = 0; i2 < 26; ++i2) {
          if (!vis[i2] && has[i2]) {
              int j = 0;
              for (j = 0; j < 10000; ++j) {
                  if ((qs[j].first.second)[0] == 'A'+i2) break;
              }
              if (j >= 10000) {
                  ans[0] = 'A'+i2;
                  vis[i2]=true;
                  break;
              }
          }
      }
      for (; i <= 9; ++i) {
          int j;
          for (j = 0; j < 26; ++j) {
              if (!vis[j] && has[j]) break;
          }
          ans[i] = 'A'+j;
          vis[j] = true;
      }
      cout<<"Case #"<<cas<<": "<<ans<<endl;
  }
  return 0;
}
