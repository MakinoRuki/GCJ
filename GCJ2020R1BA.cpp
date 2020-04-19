// 首先x和y必须不同奇同偶。然后，除了2^0以外，都只能凑偶数的delta。
// 因此第一步要把1加到(x,y)中的奇数上。然后x和y都变成了偶数，而我们也只能最小放个2。
// 这时我们可以x和y同除以2，2/2=1，我们就又回到了之前的情况。

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
int t, x, y;
int main() {
    cin>>t;
    for (int cas=1; cas<=t; ++cas) {
        cin>>x>>y;
        string ans = "";
        bool ok = true;
        while(true) {
            if (x==0 && y==0) break;
            if (x==0 && y==1) {
                ans += "N";
                break;
            }
            if (x==0 && y==-1) {
                ans += "S";
                break;
            }
            if (x==1 && y==0) {
                ans += "E";
                break;
            }
            if (x==-1 && y==0) {
                ans += "W";
                break;
            }
            int x1=abs(x);
            int y1 = abs(y);
            if ((x1+y1)%2==0) {
                ok = false;
                break;
            } else {
                if (x1%2) {
                    if ((y1/2)%2) {
                        if ((abs(x+1)/2) % 2==0) {
                            ans += "W";
                        } else {
                            ans += "E";
                        }
                    } else {
                        if ((abs(x+1)/2) % 2 == 0) {
                            ans += "E";
                        } else {
                            ans += "W";
                        }
                    }
                } else {
                    if ((x1/2)%2) {
                        if ((abs(y+1)/2)%2 == 0) {
                            ans += "S";
                        } else {
                            ans += "N";
                        }
                    } else {
                        if ((abs(y+1)/2)%2==0) {
                            ans += "N";
                        } else {
                            ans += "S";
                        }
                    }
                }
            }
            if (ans.back() == 'W') {
                x=  (x+1)/2;
                y/=2;
            } else if (ans.back()== 'E') {
                x=(x-1)/2;
                y/=2;
            } else if (ans.back() == 'N') {
                x /= 2;
                y = (y-1)/2;
            } else {
                x /= 2;
                y = (y+1)/2;
            }
        }
        if (!ok) cout<<"Case #"<<cas<<": "<<"IMPOSSIBLE"<<endl;
        else cout<<"Case #"<<cas<<": "<<ans<<endl;
    }
    return 0;
}
