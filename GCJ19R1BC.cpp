#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define N 100010
using namespace std;
typedef long long ll;
int T, n, k;
struct node {
    int l, r;
    int val;
}tree[2][N*4];
int skl[2][N];
void init(int idx, int root, int l, int r) {
	tree[idx][root].l=l;
	tree[idx][root].r = r;
    if (l == r) {
        tree[idx][root].val = skl[idx][l];
        return;
    }
    int m = (l+r)/2;
    init(idx, root*2+1, l, m);
    init(idx, root*2+2, m+1, r);
    tree[idx][root].val = max(tree[idx][root*2+1].val, tree[idx][root*2+2].val);
}
int query(int idx, int root, int l, int r) {
    if (tree[idx][root].l == l && tree[idx][root].r == r) {
        return tree[idx][root].val;
    }
    int m = (tree[idx][root].l+tree[idx][root].r) / 2;
    if (r <= m) return query(idx, root*2+1, l, r);
    else if (l > m) return query(idx, root*2+2, l, r);
    else return max(query(idx, root*2+1, l, m), query(idx, root*2+2, m+1, r));
}
int main() {
//	freopen("data0.txt","r",stdin);
    cin>>T;
    for (int cas =1; cas<= T; ++cas) {
        cin>>n>>k;
        for (int i = 0; i < n; ++i) {
            cin>>skl[0][i];
        }
        for (int i = 0; i < n; ++i) {
            cin>>skl[1][i];
        }
        init(0, 0, 0, n - 1);
        init(1, 0, 0, n - 1);
        ll ans=0LL;
        for (int i = 0; i < n; ++i) {
            if (skl[1][i] > skl[0][i]+k) continue;
            int L=i, R=i;
            int l = 0, r = i-1;
            while(l < r) {
                int m = (l+r)/2;
                if (query(0, 0, m, i-1) >= skl[0][i]) {
                    l = m+1;
                } else {
                    r = m;
                }
            }
            if (i-1>=0 && query(0, 0, r, i-1) < skl[0][i])L = r;
            l = i+1, r = n-1;
            while(l < r) {
                int m=(l+r+1)/2;
                if (query(0, 0, i+1, m) > skl[0][i]) {
                    r = m-1;
                }else {
                    l=m;
                }
            }
            if(i+1<n && query(0, 0, i+1, r) <= skl[0][i])R = r;
            int L2 = i, R2 = i;
            l =L,r=i-1;
            while(l<r) {
                int m=(l+r)/2;
                if (query(1, 0, m,i-1) > skl[0][i]+k) {
                    l=m+1;
                } else {
                    r=m;
                }
            }
            if(i-1>=L && query(1, 0, r, i-1) <= skl[0][i]+k)L2=r;
            l = i+1, r=R;
            while(l<r) {
                int m=(l+r+1)/2;
                if (query(1, 0, i+1,m) > skl[0][i]+k) {
                    r=m-1;
                } else {
                    l=m;
                }
            }
            if(i+1<=R && query(1, 0, i+1, r) <= skl[0][i]+k)R2=r;
         //   if (i==0)cout<<L<<" "<<R<<" "<<L2<<" "<<R2<<endl;
            ans += (ll)(i-L2+1)*(ll)(R2-i+1);
            int L3=i,R3=i;
            if (skl[1][i] < skl[0][i]-k) {
                //int L3=i,R3=i;
                int l = L2, r=i-1;
                while(l<r) {
                    int m = (l+r)/2;
                    if (query(1, 0, m, i-1) < skl[0][i]-k) {
                        r=m;
                    }else {
                        l=m+1;
                    }
                }
                if(i-1>=L2 && query(1, 0, r, i-1)<skl[0][i]-k)L3=r;
                l = i+1, r=R2;
                while(l<r) {
                    int m=(l+r+1)/2;
                    if (query(1, 0, i+1, m) < skl[0][i]-k) {
                        l=m;
                    } else {
                        r=m-1;
                    }
                }
                if(i+1<=R2 && query(1, 0, i+1, r)<skl[0][i]-k)R3=r;
              //  cout<<L3<<" "<<R3<<endl;
                ans -= (ll)(i-L3+1)*(ll)(R3-i+1);
            }
          //  cout<<i<<" "<<L<<" "<<R<<" "<<L2<<" "<<R2<<" "<<L3<<" "<<R3<<endl;
        }
        cout<<"Case #"<<cas<<": "<<ans<<endl;
    }
    return 0;
}
