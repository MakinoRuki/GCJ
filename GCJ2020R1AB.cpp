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
int t;
ll n;
int main() {
	cin>>t;
	for (int cas = 1; cas <= t; ++cas) {
		cin>>n;
		vector<pair<int,int>> ans;
		int p = 0;
		while((1LL << p) <= n) p++;
		p--;
	//	cout<<"p="<<p<<endl;
		while(p > 0) {
			if (n-(1LL<<p) >= p) {
				ans.push_back(make_pair(p, 1));
				n -= (1LL<<p);
			} else {
				ans.push_back(make_pair(p, 0));
				n--;
			}
			p--;
		}
		ans.push_back(make_pair(0, 1));
		n--;
		sort(ans.begin(), ans.end());
		// for (int i = 0; i < ans.size(); ++i) {
		// 	cout<<"i="<<i<<" "<<ans[i].first<<" "<<ans[i].second<<endl;
		// }
		// cout<<"n="<<n<<endl;
		if (n) {
			int last = ans.back().first;
			for (int i = 1; i <= n; ++i) {
				ans.push_back(make_pair(last+i, 0));
			}
		}
		// for (int i = 0; i < ans.size(); ++i) {
		// 	cout<<"i="<<i<<" "<<ans[i].first<<" "<<ans[i].second<<endl;
		// }
		vector<pair<int, int>> ans2;
		ans2.clear();
		for (int i = 0; i < ans.size(); ++i) {
			if (i == 0) ans2.push_back(make_pair(0,0));
			else {
				int pr = ans2.back().first;
				int pc = ans2.back().second;
				int r = ans[i].first;
				if (ans[i].second) {
					if (pc == 0) {
						for (int j = 0; j <= r; ++j) {
							ans2.push_back(make_pair(r, j));
						}
					} else if (pc == pr) {
						for (int j = r; j >= 0; --j) {
							ans2.push_back(make_pair(r, j));
						}
					}
				} else {
					if (pc == 0) ans2.push_back(make_pair(r, 0));
					else ans2.push_back(make_pair(r, r));
				}
			}
		}
		cout<<"Case #"<<cas<<": "<<endl;
		for (int i = 0; i < ans2.size(); ++i) {
			cout<<ans2[i].first+1<<" "<<ans2[i].second+1<<endl;
		}
	}
	return 0;
}
