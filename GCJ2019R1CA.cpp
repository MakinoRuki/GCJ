#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <unordered_set>
#define N 300
using namespace std;
int T,a;
vector<string>c;
int main() {
    cin>>T;
    for (int cas = 1; cas <= T; ++cas) {
        cin>>a;
        c.clear();
        for (int i = 0; i < a; ++i) {
            string s;
            cin>>s;
            c.push_back(s);
        }
        bool ok=true;
        string ans = "";
        unordered_set<int>S;
        S.clear();
        for (int i = 0; i < a;++i) {
            S.insert(i);
        }
        for (int i = 0; i < 500; ++i) {
            if (S.empty()) break;
            bool r=false,p=false,s=false;
            vector<int>rs;
            vector<int>ps;
            vector<int>ss;
            rs.clear();
            ps.clear();
            ss.clear();
            for (auto st : S) {
                if (c[st][i%c[st].size()] == 'P') {
                    p=true;
                    ps.push_back(st);
                }
                if (c[st][i%c[st].size()] == 'R') {
                    r=true;
                    rs.push_back(st);
                }
                if (c[st][i%c[st].size()] == 'S') {
                    s=true;
                    ss.push_back(st);
                }
            }
            if (r&&s&&p) {
                ok=false;
                break;
            } else if (p&&!s&&!r) {
                ans += "S";
                S.clear();
                break;
            } else if(!p && s&&!r) {
                ans += "R";
                S.clear();
                break;
            } else if(!p && !s && r) {
                ans += "P";
                S.clear();
                break;
            } else if (!p&&s&&r) {
                ans += "R";
                for (int j = 0; j < ss.size(); ++j) {
                    S.erase(ss[j]);
                }
            } else if(p&&!s&&r) {
                ans += "P";
                for (int j = 0; j < rs.size(); ++j) {
                    S.erase(rs[j]);
                }
            } else if(p&&s&&!r) {
                ans += "S";
                for (int j = 0; j < ps.size(); ++j) {
                    S.erase(ps[j]);
                }
            }
        }
        if (!S.empty() || !ok) {
            cout<<"Case #"<<cas<<": IMPOSSIBLE"<<endl;
        } else {
            cout<<"Case #"<<cas<<": "<<ans<<endl;
        }
    }
    return 0;
}
