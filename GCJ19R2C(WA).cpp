#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
int T, n;
vector<int> cs, js;
const ll inf = 1000000000;
int main() {
    cin>>T;
    for (int cas = 1;cas <= T; ++cas) {
        cin>>n;
        cs.clear();
        js.clear();
        for (int i = 0; i < n; ++i) {
            int c, j;
            cin>>c>>j;
            cs.push_back(c);
            js.push_back(j);
        }
        bool ok = true;
        ll a1 = -inf;
        ll a2 = -inf;
        ll b1 = -inf;
        ll b2 = -inf;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                ll dc = cs[j]-cs[i];
                ll dj = js[j]-js[i];
                if (dc <= 0 && dj <= 0) {
                    ok = false;
                    break;
                }
                if (dc == 0) {
                    if (dj < 0) {
                        ok = false;
                        break;
                    }
                    if (dj > 0) continue;
                } else if (dj == 0) {
                    if (dc < 0) {
                        ok = false;
                        break;
                    }
                    if (dc > 0) continue;
                } else {
                    if (dc >= 0 && dj >= 0) continue;
                    if (dc > 0 && dj < 0) {
                        if (a1 == -inf) {
                            a1 = -dj;
                            a2 = dc;
                        } else {
                            if (-dj * a2 > dc * a1) {
                                a1 = -dj;
                                a2 = dc;
                            }
                        }
                    } else if (dc < 0 && dj > 0) {
                        if (b1 == -inf) {
                            b1 = dj;
                            b2 = -dc;
                        } else {
                            if (dj * b2 < -dc * b1) {
                                b1 = dj;
                                b2 = -dc;
                            }
                        }
                    }
                }
            }
        }
        ll ansc = inf;
        ll ansj = inf;
        if (a1 == -inf && b1 == -inf) {
            cout<<"Case #"<<cas<<": "<<1<<" "<<1<<endl;
            continue;
        }
        if (a1 == -inf && b1 != -inf) {
            ansc = 1;
            ansj = b2 / b1 + 1;
            cout<<"Case #"<<cas<<": "<<ansc<<" "<<ansj<<endl;
            continue;
        }
        if (a1 != -inf && b1 == -inf) {
            ansj = 1;
            ansc = a1 / a2 + 1;
            cout<<"Case #"<<cas<<": "<<ansc<<" "<<ansj<<endl;
            continue;
        }
        if (b1 * a2 <= a1 * b2) {
            ok = false;
        }
        if (!ok) {
            cout<<"Case #"<<cas<<": IMPOSSIBLE"<<endl;
            continue;
        }
        ll lcm = (ll)a2*(ll)b2/__gcd((ll)a2, (ll)b2);
        
        for (ll i = 1; i <= 100LL*lcm; ++i) {
            ll c1;
            if ((i * b1) % b2 == 0) {
                c1 = i*b1/b2-1;
            } else {
                c1 = i*b1/b2;
            }
            ll c2 = i * a1 / a2;
            if (c2 <= c1) {
                if (c2 < ansc) {
                    ansc = c2;
                    ansj = i;
                } else if (c2 == ansc && i < ansj) {
                    ansc = c2;
                    ansj = i;
                }
            }
        }
        if (ansc < inf) {
            cout<<"Case #"<<cas<<": "<<ansc<<" "<<ansj<<endl;
        } else {
            cout<<"Case #"<<cas<<": IMPOSSIBLE"<<endl;
        }
    }
    return 0;
}
