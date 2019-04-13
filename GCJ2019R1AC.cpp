#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;
int T, N;
vector<string> w;
unordered_map<int, unordered_set<string> > m1;
unordered_map<string, unordered_set<int> > m2;
int main() {
    cin>>T;
    for (int cas = 1; cas <= T; ++cas) {
        cin>>N;
        w.clear();
        int wl = 0;
        for (int i = 0; i < N; ++i) {
            string s;
            cin>>s;
            w.push_back(s);
            wl = max(wl, (int)s.size());
        }
        m1.clear();
        m2.clear();
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < w[i].size(); ++j) {
                string ss = w[i].substr(j, w[i].size() - j);
                m2[ss].insert(i);
            }
        }
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < w[i].size(); ++j) {
                string ss = w[i].substr(j, w[i].size() - j);
                if (m2[ss].size() > 1) {
                    m1[ss.size()].insert(ss);
                }
            }
        }
        int ans = 0;
        int i = wl;
        while(i) {
            if (m1[i].size() > 0) {
                string st = *m1[i].begin();
                m1[i].erase(st);
                ans += 2;
                int n1 = *m2[st].begin();
                m2[st].erase(n1);
                int n2 = *m2[st].begin();
                m2[st].erase(n2);
                if (m2[st].size() < 2) m1[i].erase(st);
                for (int j = i - 1; j > 0; --j) {
                    string tt = w[n1].substr(w[n1].size() - j, j);
                    m2[tt].erase(n1);
                    if (m2[tt].size() < 2) m1[j].erase(tt);
                }
                for (int j = i - 1; j > 0; --j) {
                    string tt = w[n2].substr(w[n2].size() - j, j);
                    m2[tt].erase(n2);
                    if (m2[tt].size() < 2) m1[j].erase(tt);
                }
            } else {
                i--;
            }
        }
        cout<<"Case #"<<cas<<": "<<ans<<endl;
    }
    return 0;
}
