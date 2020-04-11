// 需要每次只看上次删除的位置周围的位置。类似bfs。

// TLE大数据
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <deque>
#define N 100005
using namespace std;
typedef long long ll;
int t, n;
int s[N];
bool v[N];
struct node {
	int val;
	node* pre;
	node* nxt;
	int x,y;
	node(int v, int x, int y) : val(v), x(x), y(y), pre(NULL), nxt(NULL) {}
};
node* rp[N];
node* cp[N];
node* rps[N];
node* cps[N];
int main() {
	cin>>t;
	for (int cas = 1; cas <= t; ++cas) {
		int r, c;
		cin>>r>>c;
		for (int i = 0; i < r; ++i) {
			for (int j = 0; j < c; ++j) {
				cin>>s[i*c+j];
			}
		}
	//	cout<<"1"<<endl;
		for (int i = 0; i < r; ++i) {
			rp[i] = NULL;
			node* pre = NULL;
			for (int j = 0; j < c; ++j) {
				node* cur = new node(s[i*c+j], i, j);
				rps[i*c+j] = cur;
				if (!pre) {
					rp[i] = cur;
				} else {
					cur->pre = pre;
					pre->nxt = cur;
				}
				pre = cur;
			}
		}
	//	cout<<"2"<<endl;
		for (int j = 0; j < c; ++j) {
			cp[j] = NULL;
			node* pre = NULL;
			for (int i = 0; i < r; ++i) {
				node* cur = new node(s[i*c+j], i, j);
				cps[i*c+j] = cur;
				if (!pre) {
					cp[i] = cur;
				} else {
					cur->pre = pre;
					pre->nxt = cur;
				}
				pre = cur;
			}
		}
	//	cout<<"3"<<endl;
		ll ans = 0LL;
		while(true) {
			bool found =false;
			for (int i = 0; i < r; ++i) {
				auto hp = rp[i];
				while(hp) {
					ans += hp->val;
					hp = hp->nxt;
				}
			}
			set<int> del;
			del.clear();
			for (int i = 0; i < r; ++i) {
				auto hp = rp[i];
				while(hp) {
					ll sum=0LL;
					ll cnt=0;
					int x = hp->x;
					int y = hp->y;
					auto chp = cps[x*c+y];
					if (hp->pre) {
						cnt++;
						sum += hp->pre->val;
					}
					if (hp->nxt) {
						cnt++;
						sum += hp->nxt->val;
					}
					if (chp->pre) {
						cnt++;
						sum += chp->pre->val;
					}
					if (chp->nxt) {
						cnt++;
						sum += chp->nxt->val;
					}
					if (cnt && hp->val * cnt < sum) {
						del.insert(x*c+y);
						found=true;
					}
					hp = hp->nxt;
				}
			}
		//	cout<<"ans="<<ans<<endl;
			if (!found) break;
			for (auto ptr : del) {
				int x = ptr/c;
				int y= ptr%c;
				auto rpt = rps[x*c+y];
				auto cpt = cps[x*c+y];
				if (rpt->pre) {
					rpt->pre->nxt= rpt->nxt;
					if (rpt->nxt) rpt->nxt->pre = rpt->pre;
				} else {
					rp[x] = rpt->nxt;
					if (rpt->nxt) rpt->nxt->pre = NULL;
				}
				if (cpt->pre) {
					cpt->pre->nxt= cpt->nxt;
					if (cpt->nxt) cpt->nxt->pre = cpt->pre;
				} else {
					cp[y] = cpt->nxt;
					if (cpt->nxt) cpt->nxt->pre= NULL;
				}
			}
		//	cout<<"ans="<<ans<<endl;
		}
		cout<<"Case #"<<cas<<": "<<ans<<endl;
	}
	return 0;
}


// 暴力AC小数据
/* #include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <deque>
#define N 100005
using namespace std;
typedef long long ll;
int t, n;
int s[N];
bool v[N];
int main() {
	cin>>t;
	for (int cas = 1; cas <= t; ++cas) {
		int r, c;
		cin>>r>>c;
		for (int i = 0; i < r; ++i) {
			for (int j = 0; j < c; ++j) {
				cin>>s[i*c+j];
			}
		}
		memset(v, false, sizeof(v));
		ll ans = 0LL;
		while(true) {
			bool found = false;
			for (int i = 0; i < r; ++i) {
				for (int j = 0; j < c; ++j) {
					if (!v[i*c+j]) ans += s[i*c+j];
				}
			}
			bool v2[N];
			memset(v2, false, sizeof(v2));
			for (int i = 0; i < r; ++i) {
				for (int j = 0; j < c; ++j) {
					if (!v[i*c+j]) {
						ll sum=0;
						ll cnt=0;
						int i2 = i-1;
						while(i2 >= 0 && v[i2*c+j]) i2--;
						if (i2 >= 0) { cnt++; sum += s[i2*c+j];}
						i2 = i+1;
						while(i2 < r && v[i2*c+j]) i2++;
						if (i2 < r) {cnt++; sum += s[i2*c+j];}
						int j2 = j-1;
						while(j2 >= 0 && v[i*c+j2]) j2--;
						if (j2 >= 0) {cnt++; sum += s[i*c+j2];}
						j2 = j+1;
						while(j2 < c && v[i*c+j2]) j2++;
						if (j2 < c) {cnt++; sum += s[i*c+j2];}
						if (cnt && s[i*c+j]*cnt < sum) { found=true; v2[i*c+j] = true;}
					}
				}
			}
			if (!found) break;
			for (int i = 0; i < r; ++i) {
				for (int j = 0; j < c; ++j) {
					if (v2[i*c+j]) v[i*c+j] = true;
				}
			}
		}
		cout<<"Case #"<<cas<<": "<<ans<<endl;
	}
	return 0;
} */
