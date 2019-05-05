// For大数据：每个move把矩阵分成两块独立的nim游戏，因此结果可以亦或。所以算SG值。R^2*C^2状态，转移时候预处理一下可以达到R+C。所以是N^5。
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
int T;
int r,c;
int dp[1<<16][17][2];
int bk;
vector<string> mat;
int dfs(int st, int pos, int vh) {
    if (dp[st][pos][vh] >= 0) return dp[st][pos][vh];
    int x = pos/c;
    int y=pos%c;
    int o = 0;
    bool ok=true;
    if (vh) {
    	for (int j = y; j>=0; --j) {
    		if (mat[x][j] == '#') {
    			ok=false;
    			break;
    		} else {
    			int idx = x*c+j;
    			if ((1<<idx) & st) break;
    			o |= (1<<idx);
    		}
    	}
    	for (int j = y+1; j < c; ++j) {
    		if (mat[x][j] == '#') {
    			ok=false;
    			break;
    		} else {
    			int idx=x*c+j;
    			if ((1<<idx) & st) break;
    			o |= (1<<idx);
    		}
    	}
    } else {
    	for (int i = x; i >= 0; --i) {
    		if (mat[i][y] == '#') {
    			ok=false;
    			break;
    		} else {
    			int idx=i*c+y;
    			if ((1<<idx) & st) break;
    			o |= (1<<idx);
    		}
    	}
    	for (int i = x+1; i < r; ++i) {
    		if (mat[i][y] == '#') {
    			ok=false;
    			break;
    		} else {
    			int idx=i*c+y;
    			if ((1<<idx) & st) break;
    			o |= (1<<idx);
    		}
    	}
    }
    if (!ok) return dp[st][pos][vh]=0;
    int nst = st| o;
   // if (st==240 && pos==1 && vh==0) cout<<o<<" "<<nst<<endl;
    bool found=false;
    for (int i = 0; i < r;++i){
        for (int j=0;j<c;++j) {
            if (mat[i][j] != '#') {
                int ni = i*c+j;
                if ((1<<ni)&nst) continue;
                found = true;
                bool nxt=dfs(nst, ni, 0) | dfs(nst, ni, 1);
                if (nxt) return dp[st][pos][vh] = 0; 
            }
        }
    }
    return dp[st][pos][vh]=1;
}
int main() {
    cin>>T;
    for (int cas = 1; cas <= T; ++cas) {
        bk=0;
        cin>>r>>c;
        mat.clear();
        for (int i = 0; i < r; ++i) {
            string s;
            cin>>s;
            mat.push_back(s);
        }
        int st = 0;
        int ans=0;
        memset(dp, -1, sizeof(dp));
        for (int i=0;i<r;++i){
            for (int j=0;j<c;++j) {
                if (mat[i][j] == '#') {
                    int st=i*c+j;
                    bk |= (1<<st);
                }
            }
        }
        for (int i = 0; i < r;++i) {
            for (int j = 0; j< c; ++j) {
                if (mat[i][j] != '.') continue;
                for (int k =0;k<2;++k) {
                //	memset(dp, -1, sizeof(dp));
                    dfs(0, i*c+j, k);
                    if (dp[0][i*c+j][k]) ans++;
                }
            }
        }
    // //    cout<<"**"<<dp[240][1][0]<<" "<<dp[240][1][1]<<endl;
    //     for (int i = 0; i < (1<<4); ++i) {
    //     	for (int j = 0; j< 2;++j) {
    //     		for (int k=0;k< 2;++k) {
    //     			for (int t=0;t<2;++t) {
    //     			//	cout<<i<<" "<<j*c+k<<" "<<t<<" "<<dp[i][j*c+k][t]<<endl;
    //     			}
    //     		}
    //     	}
    //     }
        cout<<"Case #"<<cas<<": "<<ans<<endl;
    }
    return 0;
}
