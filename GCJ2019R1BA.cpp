#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <unordered_set>
#define N 100010
using namespace std;
int T;
int p, q;
vector<int> xe;
vector<int> xw;
vector<int> ys;
vector<int> ny;
int ansx[N];
int ansy[N];
//vector<string> ds;
int main() {
    cin>>T;
    for (int cas = 1; cas <= T; ++cas) {
       cin>>p>>q;
       int x, y;
       string d;
       unordered_set<int> xr;
       unordered_set<int> yr;
      xr.clear();
      yr.clear();
       xe.clear();
       xw.clear();
       ys.clear();
       ny.clear();
       for (int i = 0;i < p; ++i) {
           cin>>x>>y>>d;
           if (d == "W") {
            xr.insert(0);
            xw.push_back(x);
          }
           if (d == "E") {
            if (x+1<=q)xr.insert(x+1);
            xe.push_back(x);
          }
           if (d == "S") {
            yr.insert(0);
            ys.push_back(y);
          }
           if (d == "N") {
            if (y+1<=q)yr.insert(y+1);
            ny.push_back(y);
          }
       }
       vector<int> xx(xr.begin(), xr.end());
       vector<int> yy(yr.begin(), yr.end());
       sort(xx.begin(), xx.end());
       sort(yy.begin(), yy.end());
       memset(ansx, 0, sizeof(ansx));
       memset(ansy, 0, sizeof(ansy));
       for (int i = 0; i < xx.size(); ++i) {
        for (int j = 0; j < xe.size(); ++j) {
          if (xx[i] > xe[j]) ansx[xx[i]]++;
        }
        for (int j = 0; j<xw.size(); ++j) {
          if (xx[i] < xw[j]) ansx[xx[i]]++;
        }
       }
       for (int i = 0; i < yy.size(); ++i) {
        for (int j = 0; j < ys.size(); ++j) {
          if (yy[i] < ys[j]) ansy[yy[i]]++;
        }
        for (int j = 0; j < ny.size(); ++j) {
          if (yy[i] > ny[j]) ansy[yy[i]]++;
        }
       }
       int ax = -1;
       int ay = -1;
       int maxv = 0;
       for (int i = 0; i < xx.size(); ++i) {
        if (ansx[xx[i]] > maxv) {
          maxv = ansx[xx[i]];
          ax=xx[i];
          ay=0;
        } else if (ansx[xx[i]] == maxv) {
            if (xx[i] < ax) {
                ax=xx[i];
                ay=0;
            }
        }
        for (int j = 0; j < yy.size(); ++j) {
          int cnt = ansx[xx[i]]+ansy[yy[j]];
          if (cnt>maxv) {
            maxv = cnt;
            ax= xx[i];
            ay= yy[j];
          } else if (cnt ==maxv) {
              if (xx[i]<ax) {
                  ax=xx[i];
                  ay=yy[j];
              } else if(xx[i] == ax && yy[j]<ay) {
                  ax=xx[i];
                  ay=yy[j];
              }
          }
        }
       }
       for (int i= 0; i < yy.size(); ++i) {
        if (ansy[yy[i]] > maxv) {
          maxv = ansy[yy[i]];
          ax=0;
          ay=yy[i];
        } else if (ansy[yy[i]] == maxv) {
            if (0 < ax) {
                ax=0;
                ay=yy[i];
            } else if (0 == ax && yy[i]<ay) {
                ax=0;
                ay=yy[i];
            }
        }
       }
       cout<<"Case #"<<cas<<": "<<ax<<" "<<ay<<endl;
    }
    return 0;
}
