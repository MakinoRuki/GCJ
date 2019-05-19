#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
int T;
int n;
vector<int> cs, js;
int main() {
    cin>>T;
    for (int cas =1; cas<=T; ++cas) {
        cin>>n;
        cs.clear();
        js.clear();
        for (int i = 0; i <n; ++i) {
            int c, j;
            cin>>c>>j;
            cs.push_back(c);
            js.push_back(j);
        }
        set<pair<int, int> > vis;
        vis.clear();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;
                if ((cs[i] >= cs[j] && js[i] >= js[j]) || (cs[i] <= cs[j] && js[i] <= js[j])) {
                    continue;
                }
                int d = __gcd(cs[i]-cs[j], js[i]-js[j]);
                int cd = (cs[i]-cs[j])/d;
                int jd = (js[i]-js[j])/d;
                if (vis.find(make_pair(cd, jd)) != vis.end()) {
                    continue;
                }
                vis.insert(make_pair(cd, jd));
            }
        }
        cout<<"Case #"<<cas<<": "<<vis.size() + 1<<endl;
    }
    return 0;
}
